#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include "Record.h"
#include "TemplatedDLList.h"

using namespace std; 

void display(vector<DLList<Record>> &v) {
    for (auto a : v) { 
        cout << a; 
        cout << endl; 
    }
}

void insert(vector<DLList<Record>> &v, vector<Record> &book) {
    for (int i = 0; i <book.size(); i++) {
        int num = toupper(book[i].getTitle().at(0)) - 65; 
        v[num].insert_last(book[i]); 
    } 
}
void search(vector<DLList<Record>> &v) {
    vector<Record> title; 
    string ttl; 
    cout << "Enter the name to search: "; 
    getline(cin, ttl); 
    ttl[0] = (toupper(ttl[0]));
    int num = ttl[0] - 65; 
    DLListNode<Record>* tmp = v[num].first_node();
    for_each(ttl.begin(), ttl.end(), [](char &ttl){
	        ttl = ::tolower(ttl);
        });
    while(tmp!=v[num].after_last_node()) {
        string obj = tmp->getObj().getTitle();  
        for_each(obj.begin(), obj.end(), [](char &obj){
	        obj = ::tolower(obj);
        });
        if (obj.compare(ttl) == 1)  {
            title.push_back(tmp->getObj());
        }
        tmp = tmp->getNext();
    }
    if (title.size() == 0) {
        cout << "There is no record of this title. Please add this title to the database." << endl; 
        string author, isbn, year, edt; 
        cout << "Please enter the author of the book: "; 
        getline(cin, author); 
        cout << "Please enter its isbn : "; 
        getline(cin, isbn); 
        cout << "Please enter publication year: "; 
        getline(cin, year); 
        cout << "Please enter edition number: "; 
        getline(cin, edt); 
        
        Record temp_rc(ttl, author, isbn, year, edt);
        title.push_back(temp_rc); 
        insert(v, title); 
        cout << "\nThe database is now updated\n"<< endl; 
        display(v); 
        search(v);
        
    } else if (title.size() == 1) {
        cout << "Here it is: " << endl << endl; 
        cout << title[0]; 
    } else {
        cout << "There are multiple records of the same name" << endl << endl; 
        for (auto a : title) {
            cout << a; 
            cout << endl; 
        }
        char edt; 
        cout << "\nPlease enter edition number (1 or 2, etc.): "; 
        cin >> edt; 
        for (auto a : title) {
            if (a.getEdtNum().at(0) == edt) {
                cout << endl;
                cout << a; 
                cout << endl; 
            }
        }
    }
}

int main() {
    vector<Record> rc; 
    vector<DLList<Record>> br(26); 
    ifstream in("book.txt");
    in >> rc; 
    ostream os(cout.rdbuf());
    
    sort(rc.begin(), rc.end(),[ ]( Record& lhs, Record& rhs) {
        return lhs.getTitle() < rhs.getTitle() ;
    }); 
    
   
    
    
    // string title, authorName,  isbn, publYear, edtNum;
    // Record tmp = Record(title, authorName, isbn, publYear, edtNum); 
    // tmp = rc[0]; 
    // ostream os(cout.rdbuf());
    //os << (rc[0].getTitle().at(0) -65);
    insert(br,rc);
    // for (int i = 0; i < rc.size(); i++) {
    //     os << rc[i] << endl; 
    // }
    // cout << "AFTER INSERT *******" << endl; 
    //cout << br[7]; 
    
    search(br); 
    return 0;
 
}