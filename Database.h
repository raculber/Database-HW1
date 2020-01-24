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
        bool searchRecord(ifstream &din, const string name, int &rank, string &city, string &state, int &zip, int &employees);
        void getRecord(ifstream &din, const int recordNum, int &rank,
        string &name, string &city, string &state, int &zip, int &employees);
      private:
        bool open = false;
        string csv, config, data, overflow;
        int numRecords = 500;
        int numOverflow = 0;
};
