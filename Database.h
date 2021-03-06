//Template for Database class
#include <iostream>
#include <fstream>
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
        void sortFile();
        void deleteRecord();
        int searchRecord(ifstream &din, const string name, string &rank, string &city, string &state, string &zip, string &employees);
        void getRecord(ifstream &din, const int recordNum, string &rank,
        string &name, string &city, string &state, string &zip, string &employees);
        void writeRecord(ofstream &dout, const int recordNum, string &name,
        string &rank, string &city, string &state, string &zip, string &employees);
        bool isOpen();
      private:
        bool open;
        string csv, config, data, overflow;
        int numRecords;
        int numOverflow;
        int numDeleted;
};
