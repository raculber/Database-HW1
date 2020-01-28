//Database class
#include "Database.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;
const int RECORD_SIZE = 84;
Database::Database() {
  csv = "";
  config = "";
  data = "";
  overflow = "";
    numOverflow = 0;
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
  dout.open(overflow);
  dout.close();
  string name, rank, city, state, zip, employees;
  string substr;
  string junk;
  din.open(csv);
  dout.open (data);
  getline(din, junk);
  while (getline(din, name, ',')) {
  getline(din, rank, ',');
  getline(din, city, ',');
  getline(din, state, ',');
  getline(din, zip, ',');
  getline(din, employees, '\n');
  dout << setw(40) << name << ","
       << setw(3) << rank << ","
       << setw(20) << city << ","
       << setw(2) << state << ","
       << setw(5) << zip << ","
       << setw(7) << employees << "\n";
   numRecords++;
  }
  din.close();
  dout.close();
  dout.open(config);
  dout << numRecords << "," << numOverflow << endl;
  dout << junk;
  dout.close();
}

void Database::openDatabase() {
  string dbName;
  ifstream in;
  if (open == true)
    cout << "Please close the current database before opening." << endl;
  else {
    cout << "Enter the name of the database you want to open." << endl;
    cin >> dbName;
    csv = dbName + ".csv";
    config = dbName + ".config";
    data = dbName + ".data";
    overflow = dbName + ".overflow";
    open = true;
  }
}
void Database::closeDatabase() {
  open = false;
  csv = "";
  config = "";
  data = "";
  overflow = "";
}
void Database::displayRecord() {
  string name;
  cout << "Enter the name of the company record you wish to display: " << endl;
  cin.ignore();
  getline(cin, name);
  string city, state, rank, zip, employees;
  ifstream din;
  din.open(data);
  ifstream configIn;
  configIn.open(config);
  //Find record
  int loc = searchRecord(din, name, rank, city, state, zip, employees);
  if (loc != -1) {
    int start;
    string junk;
    string line;
    getline(configIn, junk);
    //Display name (from config)
    getline(configIn, line);
    cout << right << line << endl;
    //Display value (from data)
    //Get rid of excess zeros to make prettier
    loc = name.find_first_not_of(" ");
    name = name.substr(loc, 40);
    loc = rank.find_first_not_of(" ");
    rank = rank.substr(loc, 3);
    loc = city.find_first_not_of(" ");
    city = city.substr(loc, 20);
    loc = employees.find_first_not_of(" ");
    employees = employees.substr(loc, 7);
    cout << name << "," << rank << "," << city << "," <<
    state << "," << zip << "," << employees << endl;
  }
  else {
    cout << "Error: Company not found" << endl;
  }
}
void Database::updateRecord() {
  string name;
  cout << "Enter the name of the company record you wish to update: " << endl;
  cin.ignore();
  getline(cin, name);
  cout << name << endl;
  string city, state, rank, zip, employees;
  //Find record
  ifstream din;
  din.open(data);
  int loc = searchRecord(din, name, rank, city, state, zip, employees);
  if (loc != -1)
  {
    string line;
    getRecord(din, loc, rank, name, city, state, zip, employees);
    din.seekg(loc*RECORD_SIZE,ios::beg);
    getline(din, line);
    cout << line << endl;
    din.close();
    int choice = 0;
    while (choice < 1 || choice > 5) {
      cout << "Enter the field you wish to update: " << endl;
      cout << "1: Rank" << endl;
      cout << "2: City" << endl;
      cout << "3: State" << endl;
      cout << "4: ZIP" << endl;
      cout << "5: Employees" << endl;
      cin >> choice;
    }
    string newVal;
    ofstream dout;
    dout.open(data, ios::in);
    dout.seekp(loc*RECORD_SIZE, ios::beg);
    if (choice == 1) {
      cout << "Enter the new rank value: " << endl;
      cin >> newVal;
      dout << setw(40) << name << "," << setw(3) << newVal << "," <<
      setw(20) << city << "," << setw(2) << state << "," << setw(5) <<
      zip << "," << setw(7) << employees << "\n";
    }
    else if (choice == 2) {
      cout << "Enter the new city value: " << endl;
      cin >> newVal;
      dout << setw(40) << name << "," << setw(3) << rank << "," <<
      setw(20) << newVal << "," << setw(2) << state << "," << setw(5) <<
      zip << "," << setw(7) << employees << "\n";
    }
    else if (choice == 3) {
      cout << "Enter the new state value: " << endl;
      cin >> newVal;
      dout << setw(40) << name << "," << setw(3) << rank << "," <<
      setw(20) << city << "," << setw(2) << newVal << "," << setw(5) <<
      zip << "," << setw(7) << employees << "\n";
    }
    else if (choice == 4) {
      cout << "Enter the new ZIP value: " << endl;
      cin >> newVal;
      dout << setw(40) << name << "," << setw(3) << rank << "," <<
      setw(20) << city << "," << setw(2) << state << "," << setw(5) <<
      newVal << "," << setw(7) << employees << "\n";
    }
    else {
      cout << "Enter the new employees value: " << endl;
      cin >> newVal;
      dout << setw(40) << name << "," << setw(3) << rank << "," <<
      setw(20) << city << "," << setw(2) << state << "," << setw(5) <<
      zip << "," << setw(7) << newVal << "\n";
    }
    dout.close();
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
    string nameTemp, cityTemp, stateTemp;
    int rankTemp, zipTemp, empTemp;
    //Change to get line
    cout << "Enter the name:  ";
    cin >> nameTemp;
    cout << "Enter the rank:  ";
    cin >> rankTemp;
    //Change to get line
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
        numRecords += numOverflow;
        numOverflow = 0;
        //mergeRecord: insertion sort
        fstream dataFile, overflowFile;
        dataFile.open(data, fstream::app);
        overflowFile.open(overflow);
        string line;
        while(!overflowFile.eof())
        {
            getline(overflowFile, line, ',');
            if(!overflowFile.eof())
                dataFile << line << ", ";
            else
                dataFile << line;
        }
        dataFile.close();
        overflowFile.close();
        overflowFile.open(overflow, ofstream::out | ofstream::trunc);
        overflowFile.close();
        dataFile.open(config);
        dataFile << numRecords << " " << numOverflow;

        //sort the data file


        dataFile.close();
    }
    cout << "NumOverflow:  " << numOverflow << endl;
    cout << "New record added.\n\n";
}
void Database::deleteRecord() {
  string name;
  cout << "Enter the name of the company record to delete" << endl;
  cin >> name;
  ifstream din;
  din.open(data);
  string rank, city, state, zip, employees;
  int result = searchRecord(din, name, rank, city, state, zip, employees);
  din.close();
  ofstream dout;
  if (result != -1) {
    ofstream dout;
    dout.open(data, ios::in);
    dout.seekp(result*RECORD_SIZE, ios::beg);
    string one = "-1";
    dout << setw(40) << name << "," << setw(3) << one << "," <<
    setw(20) << one << "," << setw(2) << one << "," << setw(5) <<
    one << "," << setw(7) << one << "\n";
    dout.close();
  }
  else {
    bool foundOverflow = false;
    int loc;
    din.open(overflow);
    string tempName, rank, city, state, zip, employees;
    int i = 0;
    while(i < numOverflow && !foundOverflow) {
      getRecord(din, i, rank, tempName, city, state, zip, employees);
      loc = tempName.find_first_not_of(" ");
      tempName = tempName.substr(40-loc,40);
      if (tempName == name) {
        foundOverflow = true;
      }
      i++;
    }
    if (!foundOverflow) {
      cout << "Error: Record not found" << endl;
    }
    else {
      ofstream dout;
      dout.open(overflow, ios::in);
      dout.seekp(i*RECORD_SIZE, ios::beg);
      string one = "-1";
      dout << setw(40) << name << "," << setw(3) << one << "," <<
      setw(20) << one << "," << setw(2) << one << "," << setw(5) <<
      one << "," << setw(7) << one << "\n";
      dout.close();
    }
  }
}
int Database::searchRecord(ifstream &din, const string name, string &rank,
string &city, string &state, string &zip, string &employees) {
  int low = 0;
  int high = numRecords-1;
  string middleName;
  int middle;
  int loc;
  bool found = false;
  while (!found && (low <= high)) {
    middle = (low + high)/2;
    getRecord(din, middle, rank, middleName, city, state, zip, employees);
    loc = middleName.find_first_not_of(" ");
    middleName = middleName.substr(loc, 40);
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
  if ((recordNum >= 0) && (recordNum <= numRecords-1)) {
    din.seekg(recordNum*RECORD_SIZE, ios::beg);
    getline(din, name, ',');
    getline(din, rank, ',');
    getline(din, city, ',');
    getline(din, state, ',');
    getline(din, zip, ',');
    getline(din, employees, '\n');
  }
  else
    cout << "Out of range" << endl;
}
