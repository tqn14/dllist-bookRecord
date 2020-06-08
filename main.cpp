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
    for (int i=0; i<v.size(); ++i) {
        cout<<"List: "<<i<<"\n"<<v[i];
        cout<<endl<<endl;
    }
}

void insert(vector<DLList<Record>> &v, vector<Record> &book) {
    for (int i = 0; i <book.size(); i++) {
        int num = book[i].getTitle().at(0) - 65; 
        v[num].insert_last(book[i]); 
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
    cout << "AFTER INSERT *******" << endl; 
    cout << br[7]; 
    
 
}