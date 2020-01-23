//Database class
#include "Database.h"
#include <iostream>
#include <fstream>
using namespace std;
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
  config = fileName + ".config";
  data = fileName + ".data";
  overflow = fileName + ".overflow";
  csv = fileName + ".csv";
  ofstream dout;
  ifstream din;
  dout.open(config, ios::out);
  din.open(csv, ios::in);
  string firstLine;
  getline(din,firstLine);
  dout << numRecords << " " << firstLine;
  dout.close();
  dout.open(data, ios::out);
  while (!din.eof())
  {
    string line;
    getline(din, line);
    dout << endl;
    dout << line;
  }
  dout.close();
  din.close();
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
  string name;
  cout << "Enter the name of the company record you wish to update: " << endl;
  cin >> name;
  string city, state;
  int rank, zip, employees;
  //Find record
  ifstream din;
  din.open(data);
  if (searchRecord(din, name, rank, city, state, zip, employees))
  {
    cout << name << rank << city << state << zip << employees;
  }

}
void Database::createReport() {
  ofstream outfile("report.txt");
  for (int i = 0; i < 10; i++)
  {

  }
}
void Database::addRecord() {
  string addName;
  cout << "Enter the name of the company record to add" << endl;
  cin >> addName;
}
void Database::deleteRecord() {
  string name;
  cout << "Enter the name of the company record to delete" << endl;
  cin >> name;
}
bool Database::searchRecord(ifstream &din, const string name, int &rank,
string &city, string &state, int &zip, int &employees) {
  int low = 0;
  int high = numRecords;
  string middleName;
  int middle;
  bool found = false;
  while (!found && (high >= low)) {
    middle = (low + high)/2;
    getRecord(din, middle+1, rank, middleName, city, state, zip, employees);
    cout << middleName;
    if (middleName == name)
      found = true;
    else if (middleName < name)
      low = middle+1;
    else
      high = middle-1;
  }
  return found;
}
void Database::getRecord(ifstream &din, const int location, int &rank,
string &name, string &city, string &state, int &zip, int &employees) {
  if (location >= 1 && location <= numRecords) {
    din.seekg(location*numRecords, ios::beg);
    din >> rank >> name >> city >> state >> zip >> employees;
  }
  else
    cout << "Out of range" << endl;
}
