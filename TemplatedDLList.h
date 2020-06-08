#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>
#include <vector>


using namespace std; 

template<typename T> class DLList;
template<typename T> class DLListNode {
    private: 
        T obj; 
        DLListNode<T> *prev, *next; 
        friend class DLList<T>;
    public: 
        DLListNode (T e = T(), DLListNode<T> *p = nullptr, DLListNode<T> *n = nullptr)
          : obj(e) , prev(p) , next(n) {}
        T getObj() const {return obj;}
        DLListNode<T> *getNext() const {return next;}
        DLListNode<T> *getPrev() const {return prev;}
}; 

template<typename T> class DLList { 
    private: 
        DLListNode<T> header, trailer;
    public:
        DLList() : header(T()), trailer(T()) // default constructor
        {header.next = &trailer; trailer.prev = &header; }
        DLList(const DLList<T>& dll); // copy constructor
        DLList(DLList<T>&& dll); // move constructor
        ~DLList(); // destructor
        DLList<T>& operator=(const DLList<T>& dll); // copy assignment operator
        DLList<T>& operator=(DLList<T>&& dll); // move assignment operator
        // return the pointer to the first node
        DLListNode<T> *first_node() const { return header.next; } 
        // return the pointer to the trailer
        const DLListNode<T> *after_last_node() const { return &trailer; }
        // return if the list is empty
        bool is_empty() const { return header.next == &trailer; }
        T first() const; // return the first object
        T last() const; // return the last object
        void insert_first(T obj); // insert to the first node
        T remove_first(); // remove the first node
        void insert_last(T obj); // insert to the last node
        T remove_last(); // remove the last node
        void insert_after(DLListNode<T> &p, T obj);
        void insert_before(DLListNode<T> &p, T obj);
        T remove_after(DLListNode<T> &p);
        T remove_before(DLListNode<T> &p);
};

template<typename T> ostream& operator<<(ostream& out, const DLList<T>& dll) {
    DLListNode<T> *tmp = dll.first_node(); 
    while(tmp!=dll.after_last_node()) {
        T obj = tmp->getObj(); 
        out << obj;
        out << endl; 
        tmp = tmp->getNext();
    }
  /* Complete this function */
  return out;
}; 

struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};
//copy constructor
template<typename T>
DLList<T>::DLList(const DLList<T>& dll)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;
  if (!dll.is_empty()) { 
    DLListNode<T> *tmp = dll.first_node(); 
    while(tmp != dll.after_last_node()) {
      insert_last(tmp->getObj());
      tmp = tmp->getNext(); 
    } 
  }
}
//move constructor
template<typename T> 
DLList<T>::DLList(DLList<T>&& dll)
{
  //copy dll header and trailer 
  //make dll empty 
  header = dll.header; 
  dll.header.next = nullptr; 
  trailer = dll.trailer; 
  dll.trailer.prev = nullptr; 
}
//copy assignment operator
template<typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& dll)
{
  if (this != &dll) {   
    DLListNode<T> *prev_node, *node = header.next; 
    while(node!=&trailer) {
      prev_node = node; 
      node = node->getNext(); 
      delete prev_node;  
    }
    header.next = &trailer; 
    trailer.prev = &header; 
    if (!dll.is_empty()) {
      node = dll.first_node(); 
      while (node != dll.after_last_node()) {
        insert_last(node->getObj()); 
        node = node->getNext(); 
      }
    }
  }
  return *this;
}

// move assignment operator
template<typename T> 
DLList<T>& DLList<T>::operator=(DLList<T>&& dll)
{
  //deallocate space;
  //shallow copy dll elements
  //made dll header and trailer nullptr 
  if (this != &dll) {   
    DLListNode<T> *prev_node, *node = header.next; 
    while(node!=&trailer) {
      prev_node = node; 
      node = node->getNext(); 
      delete prev_node;  
    }
    header = dll.header; 
    dll.header.next = nullptr; 
    trailer = dll.trailer; 
    dll.trailer.prev = nullptr; 
  }
  return *this;
}

// destructor
template<typename T>
DLList<T>::~DLList()
{
  DLListNode<T> *prev_node, *node = header.next; 
  while(node!=&trailer) {
    prev_node = node; 
    node = node->getNext(); 
    delete prev_node; 
  }
  header.next = &trailer; 
  trailer.prev = &header; 
}
// insert a new object as the first one
template<typename T>
void DLList<T>::insert_first(T obj)
{ 
  DLListNode<T> *newNode = new DLListNode<T>(obj, &header, header.next); 
  header.next->prev = newNode; 
  header.next = newNode;
}
// insert a new object as the last one
template<typename T>
void DLList<T>::insert_last(T obj)
{
  DLListNode<T> *newNode = new DLListNode<T>(obj, trailer.prev,&trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
  /* Complete this function */
}

// remove the first node from the list
template<typename T>
T DLList<T>::remove_first()
{ 
  if(is_empty()) {
    throw EmptyDLList("Empty list"); 
  }
  DLListNode<T> *tmp = header.next; 
  tmp->next->prev = &header; 
  header.next = tmp->getNext();
  T obj = tmp->getObj(); 
  delete tmp; 
  return obj; 
  /* Complete this function */
}

// remove the last node from the list
template<typename T>
T DLList<T>::remove_last()
{
  DLListNode<T> *tmp = trailer.prev; 
  tmp->prev->next = &trailer; 
  trailer.prev = tmp->getPrev();
  T obj = tmp->getObj(); 
  delete tmp;
  return obj;
  /* Complete this function */
}

// return the first object (do not remove)
template<typename T>
T DLList<T>::first() const
{ 
  if(is_empty()) {
    throw EmptyDLList("List is empty");   
  } 
  return header.next->getObj(); 
  /* Complete this function */
}

// return the last object (do not remove)
template<typename T>
T DLList<T>::last() const
{
  if(is_empty()) {
    throw EmptyDLList("List is empty"); 
  } 
  return trailer.prev->getObj();
  /* Complete this function */
}

// insert a new node after the node p
template<typename T>void DLList<T>::insert_after(DLListNode<T> &p, T obj)
{
  if (&p == nullptr) {
    throw std::invalid_argument("P not found");
  }
  if(p.next == &trailer) {
    insert_last(obj);
  } else { 
    DLListNode<T> *newNode = new DLListNode<T>(obj, nullptr, nullptr); 
    newNode->next = p.next;
    p.next = newNode;
    newNode->prev = p.next->prev;
    if(newNode->next != nullptr) {
      newNode->next->prev = newNode; 
    }
  }
  /* Complete this function */
}

// insert a new node before the node p
template<typename T>void DLList<T>::insert_before(DLListNode<T> &p, T obj)
{ if (&p == nullptr) {
    throw std::invalid_argument("P not found");
  }
  if(p.prev == &header) {
    insert_first(obj); 
  } else {
    DLListNode<T> *newNode = new DLListNode<T>(obj,nullptr,nullptr); 
    newNode->next =p.prev->next; 
    newNode->prev = p.prev;
    p.prev=newNode; 
    if (newNode->prev != nullptr) {
      p.prev->next = newNode; 
    } else {
      header.next = newNode;
    }
  }
  /* Complete this function */
}

// remove the node after the node 
template<typename T>T DLList<T>::remove_after(DLListNode<T> &p)
{
  if(p.next == &trailer) {
    return 0;
  } else {
    DLListNode<T> *tmp = p.next; 
    p.next = tmp->next;
    tmp->next->prev = tmp->prev; 
    T obj = tmp->getObj(); 
    delete tmp; 
    return obj; 
  }
  /* Complete this function */
}

// remove the node before the node p
template<typename T>T DLList<T>::remove_before(DLListNode<T> &p)
{
  if(p.prev == &header) {
    return 0; 
  } else {
    DLListNode<T> *tmp = p.prev; 
    p.prev = tmp->prev;
    tmp->prev->next = tmp->next; 
    T obj = tmp->getObj(); 
    delete tmp; 
    return obj;
  }
  /* Complete this function */
}
//template<typename T>T searchRecord(vector<DLListNode<T>> &p, T obj); 
#endif
