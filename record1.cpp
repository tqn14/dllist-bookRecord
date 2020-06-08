#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm> 
#include "record.h"
  
using namespace std;
using namespace std::chrono;


int main() {
    ifstream file_ptr("book.txt");
    vector<Record> book_list;
    auto start = high_resolution_clock::now();
    file_ptr >> book_list;
    auto stop = high_resolution_clock::now(); 
    ostream os(cout.rdbuf());
    os << book_list[0]; 
    for (int i =0; i <book_list.size(); i++) {
        os << book_list[i];
        os << endl;
    }
    // auto duration = duration_cast<microseconds>(stop-start);
    // os << "Time it takes to read the file:" << duration.count() << endl; 
    cout << (book_list[0] < book_list[0]) <<endl; 
   return 0;
}
 