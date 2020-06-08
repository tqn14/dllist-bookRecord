#include <iostream>
#include <fstream>
#include <string>
#include <vector>
  
#ifndef RECORD_H
#define RECORD_H

using namespace std;
class Record {
    public:
 
        Record() {};
        Record(string title, string authorName, string isbn, string publYear,string edtNum) {
            this->title=title;
            this->authorName = authorName;
            this->isbn = isbn;
            this->publYear = publYear;
            this->edtNum = edtNum;
        }
         string getTitle() {return title;}
         string getAuthor() {return authorName;}
         string getIsbn() {return isbn;}
         string getPublYear() {return publYear;}
         string getEdtNum() {return edtNum;}
 
    private:
         string title;
         string authorName;
         string isbn;
         string publYear;
         string edtNum;
         vector<Record> r;
};
void operator>>(ifstream &fin, vector<Record> &rc){
    if (!fin.is_open()) {
        throw runtime_error("could not open file");
    }
    string ttl, author, isbn_, pubyear, edtnum;
    string space;
    while(!fin.eof()) {
        getline(fin,ttl);
        getline(fin,author);
        getline(fin,isbn_);
        getline(fin,pubyear);
        getline(fin, edtnum);
        getline(fin,space);
        if (!fin.fail()) {
            Record temp_rc(ttl, author, isbn_, pubyear, edtnum);
            rc.push_back(temp_rc); 
        }
    }
} //run time 
void operator<< (ostream &os, Record &rc) {
    os << rc.getTitle() <<endl; 
    os << rc.getAuthor() <<endl;
    os << rc.getIsbn() <<endl;
    os << rc.getPublYear() <<endl;
    os << rc.getEdtNum() <<endl;
    os << endl;

} //rt 
bool operator<(Record& r1, Record& r2) { 
    if(r1.getTitle() == r2.getTitle()) {
        if ((r1.getAuthor() == r2.getAuthor()) && (r1.getIsbn() == r2.getIsbn())) {
            return true;
        }
    }
        else {
          return false;
        }
}

#endif 