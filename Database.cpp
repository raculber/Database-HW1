//Database class
#include "Database.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
const int RECORD_SIZE = 72;
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
  dout << numRecords << "," << numOverflow << firstLine;
  dout.close();
  dout.open(data, ios::out);
  string name, city, state;
  int rank, zip, employees;
  int i = 0;
  string toks[6];
  while (!din.eof())
  {
    string substr;
    getline(din, substr, ',');
    toks[i] = substr;
    if (i == 0)
      dout << setw(35) << toks[i] << " ";
    else if (i == 1)
      dout << setw(3) << toks[i] << " ";
    else if (i == 2)
      dout << setw(20) << toks[i] << " ";
    else if (i == 3)
      dout << setw(2) << toks[i] << " ";
    else if (i == 4)
      dout << setw(5) << toks[i] << " ";
    else
      dout << setw(7) << toks[i] << " ";
    i++;
    if (i > 5)
      i = 0;
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
  string city, state, rank, zip, employees;
  //Find record
  ifstream din;
  din.open(data);
  int loc = searchRecord(din, name, rank, city, state, zip, employees);
  if (loc != -1)
  {
    cout << name << rank << city << state << zip << employees << endl;
  }
  else {
    cout << "Error: company not found" <<  endl;
  }

}
void Database::createReport() {
  ofstream dout;
  dout.open("report.txt");
  ifstream din;
  din.open(data);
  for (int i = 1; i <= 10; i++)
  {
    string line;
    getline(din, line);
    dout << i << ": " << line;
    dout << endl;
  }
}
void Database::addRecord() {
  /*string addName, addCity, addState;
  int addRank, addZip, addEmployees;
  cout << "Enter the name, rank, city, state, zip, and number of employees " <<
  "of the company record to add: " << endl;
  cin >> addName >> addRank >> addCity >> addState >> addZip >> addEmployees;
  numOverflow++;
  ofstream dout;
  dout.open(overflow);
  dout << setw(10) << addName << addRank << addCity << addState << addZip << addEmployees;
  //Overflow file has more than four records
  if (numOverflow > 4) {
    //Merge overflow file with data file
   }
   */
    string nameTemp, cityTemp, stateTemp;
    int rankTemp, zipTemp, empTemp;
    cout << "Enter the name:  ";
    cin >> nameTemp;
    cout << "Enter the rank:  ";
    cin >> rankTemp;
    cout << "Enter the city:  ";
    cin >> cityTemp;
    cout << "Enter the state:  ";
    cin >> stateTemp;
    cout << "Enter the zip code:  ";
    cin >> zipTemp;
    cout << "Enter the number of employees:  ";
    cin >> empTemp;
    //if numberOverflow < 3
    //add record to overflow
    if(numOverflow >= 0 && numOverflow < 4){
        numOverflow ++;
        ofstream myFile;
        myFile.open(overflow, fstream::app);
        myFile << nameTemp << ", " << rankTemp << ", " << cityTemp << ", " << stateTemp << ", " << zipTemp << ", " << empTemp << endl;
        myFile.close();
        myFile.open(config);
        myFile << numRecords << ", " << numOverflow;
    }
    //numberOverflow >= 3
    //merge the data, change numberOverflow to 0, add record to overflow
    if(numOverflow >= 4) {
        //mergeRecord: insertion sort
        fstream dataFile, overflowFile;
        dataFile.open(data, fstream::app);
        overflowFile.open(overflow);
        string line;
        while(!overflowFile.eof())
        {
            getline(overflowFile, line, ',');
            dataFile << line;
        }
        dataFile.close();
        overflowFile.close();
        overflowFile.open(overflow, ofstream::out | ofstream::trunc);
        overflowFile.close();
        numRecords += numOverflow;
        numOverflow = 0;
        dataFile.open(config);
        dataFile << numRecords << " " << numOverflow;

        //sort the data file


        dataFile.close();
    }
    cout << "numOverflow: " << numOverflow << endl;
    cout << "New record added.\n\n";
}
void Database::deleteRecord() {
  string name;
  cout << "Enter the name of the company record to delete" << endl;
  cin >> name;
}
int Database::searchRecord(ifstream &din, const string name, string &rank,
string &city, string &state, string &zip, string &employees) {
  int low = 0;
  int high = numRecords-1;
  string middleName;
  int middle;
  bool found = false;
  while (!found && (high >= low)) {
    middle = (low + high)/2;
    getRecord(din, middle+1, rank, middleName, city, state, zip, employees);
    if (middleName == name)
      found = true;
    else if (middleName < name)
      low = middle+1;
    else
      high = middle-1;
  }
  if (found == true)
    return middle;
  else
    return -1;
}
void Database::getRecord(ifstream &din, const int recordNum, string &rank,
string &name, string &city, string &state, string &zip, string &employees) {
  if (recordNum >= 1 && recordNum < numRecords) {
    din.seekg(recordNum*RECORD_SIZE, ios::beg);
    din >> name >> rank >> city >> state >> zip >> employees;
  }
  else
    cout << "Out of range" << endl;
}
