//Database class
#include "Database.h"
#include <iostream>
#include <fstream>
using namespace std;
const int NUM_RECORDS = 500;
Database::Database() {
  csv = "";
  config = "";
  data = "";
  overflow = "";
}
Database::~Database() {

}
void Database::createDatabase() {
  string fileName;
  cout << "Enter the name of a .csv file: ";
  cin >> fileName;
  config = fileName + ".config" + ".csv";
  data = fileName + ".data" + ".csv";
  overflow = fileName + ".overflow" + ".csv";
    string fileN = fileName + ".csv";
    ofstream myFile;
    myFile.open(config);
    for(int i = 0; i < 20; i ++)
        myFile << i << "," << i * i << endl;
    myFile.close();
    
    exit(0);

}
void Database::openDatabase() {
  string dbName;
  ifstream in;
  if (open == true)
    cout << "Please close the current database before opening." << endl;
  else {
    cout << "Enter the name of the database you want to open." << endl;
    cin >> dbName;
    in.open("");
  }
}
void Database::closeDatabase() {
  open = false;
  fstream fileC(config);
  fileC.close();
  fstream fileD(data);
  fileD.close();
  fstream fileO(overflow);
  fileO.close();
}
void Database::displayRecord() {
  //Find record

  //Display name (from config)
  //Display value (from data)
}
void Database::updateRecord() {
  int recRank;
  cout << "Enter the rank of the record you want to update: " << endl;
  cin >> recRank;
  //Find record


}
void Database::createReport() {
  ofstream outfile("report.txt");
  for (int i = 0; i < 10; i++)
  {

  }
}
void Database::addRecord() {

}
void Database::deleteRecord() {
  int rank;
  ifstream din;
  cout << "Enter the rank of the record to delete";
  cin >> rank;

}
bool Database::searchRecord(ifstream &din, const int location, int &rank,
string &name, string &city, string &state, int &zip, int &employees) {
  int low = 0;
  int high = NUM_RECORDS-1;
  int middleRank = 0;
  int middle;
  bool found = false;
  Record temp;
  while (!found && (high >= low)) {
    middle = (low + high)/2;
    getRecord(din, middle+1, middleRank, name, city, state, zip, employees);
    if (middleRank == location)
      found = true;
    else if (middleRank < location)
      low = middle+1;
    else
      high = middle-1;
  }
  return found;
}
void Database::getRecord(ifstream &din, const int location, int &rank,
string &name, string &city, string &state, int &zip, int &employees) {
  Record rec;
  if (location >= 1 && location <= NUM_RECORDS) {
    din.seekg(location*NUM_RECORDS, ios::beg);
    din >> rank >> name >> city >> state >> zip >> employees;
  }
  else
    cout << "Out of range" << endl;
}
