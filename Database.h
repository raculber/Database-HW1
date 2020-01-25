//Template for Database class
#include <iostream>
#include <fstream>
#include "Record.h"
using namespace std;
class Database {
    public:
        Database();
        ~Database();
        void createDatabase();
        void openDatabase();
        void closeDatabase();
        void displayRecord();
        void updateRecord();
        void createReport();
        void addRecord();
        void deleteRecord();
        bool searchRecord(ifstream &din, const string name, string &rank, string &city, string &state, string &zip, string &employees);
        void getRecord(ifstream &din, const int recordNum, string &rank,
        string &name, string &city, string &state, string &zip, string &employees);
      private:
        bool open = false;
        string csv, config, data, overflow;
        int numRecords = 500;
        int numOverflow = 0;
};
