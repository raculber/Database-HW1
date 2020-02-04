//Database class
#include "Database.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <stdio.h>

using namespace std;
const int RECORD_SIZE = 83;
Database::Database() {
  csv = "";
  config = "";
  data = "";
  overflow = "";
  numOverflow = 0;
  numRecords = 0;
  numDeleted = 0;
  open = false;
    numDeleted = 0;
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
  dout.open(overflow.c_str(), ios::out);
  dout.close();
  string name, rank, city, state, zip, employees;
  string substr;
  string junk;
  din.open(csv.c_str());
  dout.open (data.c_str());
  getline(din, junk);
  while (getline(din, name, ',')) {
  //Truncate inputs over max size
  if (name.size() > 40)
    name = name.substr(0,40);
  getline(din, rank, ',');
  if (rank.size() > 3)
    rank = rank.substr(0,3);
  getline(din, city, ',');
  if (city.size() > 20)
    city = city.substr(0,20);
  getline(din, state, ',');
  if (state.size() > 2)
    state = state.substr(0,2);
  getline(din, zip, ',');
  if (zip.size() > 5)
    zip = zip.substr(0,5);
  getline(din, employees, '\n');
  if (employees.size() > 7)
    employees = employees.substr(0,7);
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
  dout.open(config.c_str());
  dout << numRecords << "," << numOverflow << endl;
  dout << junk;
  dout.close();
  open = false;
}

void Database::openDatabase() {
  string dbName;
  ifstream configIn;
  ifstream csvIn;
  ifstream dataIn;
  ifstream overflowIn;
  if (open == true)
    cout << "Please close the current database before opening." << endl;
  else {
    cout << "Enter the name of the database you want to open." << endl;
    cin >> dbName;
    csv = dbName + ".csv";
    config = dbName + ".config";
    data = dbName + ".data";
    overflow = dbName + ".overflow";
    configIn.open(config.c_str(), ios::in);
    dataIn.open(data.c_str(), ios::in);
    overflowIn.open(overflow.c_str(), ios::in);
    csvIn.open(csv.c_str(), ios::in);
    if (configIn.fail() || dataIn.fail() || overflowIn.fail() || csvIn.fail()) {
      cout << "Error: Files failed to open" << endl;
      csv = "";
      config = "";
      data = "";
      overflow = "";
    }
    else {
      string word;
      open = true;
      getline(configIn, word, ',');
      //numRecords = stoi(word.c_str());
      istringstream(word.c_str()) >> numRecords;
      getline(configIn, word, '\n');
      //numOverflow = stoi(word.c_str());
      istringstream(word.c_str()) >> numOverflow;
    }
    configIn.close();
    dataIn.close();
    csvIn.close();
    overflowIn.close();
  }
}
void Database::closeDatabase() {
  if (open == true) {
    open = false;
    ifstream configIn;
    ifstream csvIn;
    ifstream dataIn;
    ifstream overflowIn;
    csvIn.close();
    configIn.close();
    dataIn.close();
    overflowIn.close();
    csv = "";
    config = "";
    data = "";
    overflow = "";
  }
}
void Database::displayRecord() {
  if (!open)
    cout << "Please open a Database before continuing" << endl;
  else {
    string name;
    cout << "Enter the name of the company record you wish to display: " << endl;
    cin.ignore();
    getline(cin, name);
    if (name.size() > 40)
      name = name.substr(0,40);
    string city, state, rank, zip, employees;
    ifstream din;
    din.open(data.c_str());
    ifstream configIn;
    configIn.open(config.c_str());
    //Find record
    int loc = searchRecord(din, name, rank, city, state, zip, employees);
    din.close();
    //Check if record was "deleted"
    if (state == "-1")
      cout << "Error: Record not found" << endl;
    else if (loc != -1) {
      //int start;
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
      bool foundOverflow = false;
      int loc;
      string tempName, rank, city, state, zip, employees;
      int i = 0;
      din.open(overflow.c_str());
      while(i < numOverflow && !foundOverflow) {
        getRecord(din, i, rank, tempName, city, state, zip, employees);
        loc = tempName.find_first_not_of(" ");
        tempName = tempName.substr(loc,40);
        if (tempName == name) {
          foundOverflow = true;
        }
        i++;
      }
      din.close();
      if (!foundOverflow) {
        cout << "Error: Record not found" << endl;
      }
      else {
        if (state == "-1")
          cout << "Error: Record not found" << endl;
        else {
          //int start;
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
      }
    }
    configIn.close();
  }
}
void Database::updateRecord() {
  if (!open)
    cout << "Please open a Database before continuing" << endl;
  else {
    string name;
    cout << "Enter the name of the company record you wish to update: " << endl;
    cin.ignore();
    getline(cin, name);
    if (name.size() > 40)
      name = name.substr(0,40);
    string city, state, rank, zip, employees;
    //Find record
    ifstream din;
    din.open(data.c_str());
    int loc = searchRecord(din, name, rank, city, state, zip, employees);
    if (loc != -1)
    {
      string line;
      getRecord(din, loc, rank, name, city, state, zip, employees);
      //Check if record was "deleted"
      if (state == "-1")
        cout << "Error: Record not found" << endl;
      else {
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
        dout.open(data.c_str(), ios::in);
        dout.seekp(loc*RECORD_SIZE, ios::beg);
        if (choice == 1) {
          cout << "Enter the new rank value: " << endl;
          cin >> newVal;
          if (newVal.size() > 3) {
            newVal = newVal.substr(0,3);
          }
          dout << setw(40) << name << "," << setw(3) << newVal << "," <<
          setw(20) << city << "," << setw(2) << state << "," << setw(5) <<
          zip << "," << setw(7) << employees << "\n";
        }
        else if (choice == 2) {
          cout << "Enter the new city value: " << endl;
          cin.ignore();
          getline(cin, newVal);
          if (newVal.size() > 20)
            newVal = newVal.substr(0,20);
          dout << setw(40) << name << "," << setw(3) << rank << "," <<
          setw(20) << newVal << "," << setw(2) << state << "," << setw(5) <<
          zip << "," << setw(7) << employees << "\n";
        }
        else if (choice == 3) {
          cout << "Enter the new state value: " << endl;
          cin >> newVal;
          if (newVal.size() > 2)
            newVal = newVal.substr(0,2);
          dout << setw(40) << name << "," << setw(3) << rank << "," <<
          setw(20) << city << "," << setw(2) << newVal << "," << setw(5) <<
          zip << "," << setw(7) << employees << "\n";
        }
        else if (choice == 4) {
          cout << "Enter the new ZIP value: " << endl;
          cin >> newVal;
          if (newVal.size() > 5)
            newVal = newVal.substr(0,5);
          dout << setw(40) << name << "," << setw(3) << rank << "," <<
          setw(20) << city << "," << setw(2) << state << "," << setw(5) <<
          newVal << "," << setw(7) << employees << "\n";
        }
        else {
          cout << "Enter the new employees value: " << endl;
          cin >> newVal;
          if (newVal.size() > 7)
            newVal = newVal.substr(0,7);
          dout << setw(40) << name << "," << setw(3) << rank << "," <<
          setw(20) << city << "," << setw(2) << state << "," << setw(5) <<
          zip << "," << setw(7) << newVal << "\n";
        }
        dout.close();
      }
    }
    else {
      bool foundOverflow = false;
      int loc;
      string tempName, rank, city, state, zip, employees;
      int i = 0;
      din.close();
      din.open(overflow.c_str());
      while(i < numOverflow && !foundOverflow) {
        getRecord(din, i, rank, tempName, city, state, zip, employees);
        loc = tempName.find_first_not_of(" ");
        tempName = tempName.substr(loc,40);
        if (tempName == name) {
          foundOverflow = true;
        }
        else
          i++;
      }
      din.close();
      if (!foundOverflow) {
        cout << "Error: Record not found" << endl;
      }
      else {
        if (state == "-1")
          cout << "Error: Record not found" << endl;
        else {
          din.open(overflow.c_str());
          string line;
          din.seekg(i*RECORD_SIZE,ios::beg);
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
          dout.open(overflow.c_str(), ios::in);
          dout.seekp(i*RECORD_SIZE, ios::beg);
          if (choice == 1) {
            cout << "Enter the new rank value: " << endl;
            cin >> newVal;
            if (newVal.size() > 3)
              newVal = newVal.substr(0,3);
            dout << setw(40) << name << "," << setw(3) << newVal << "," <<
            setw(20) << city << "," << setw(2) << state << "," << setw(5) <<
            zip << "," << setw(7) << employees << "\n";
          }
          else if (choice == 2) {
            cout << "Enter the new city value: " << endl;
            cin.ignore();
            getline(cin, newVal);
            if (newVal.size() > 20)
              newVal = newVal.substr(0,20);
            dout << setw(40) << name << "," << setw(3) << rank << "," <<
            setw(20) << newVal << "," << setw(2) << state << "," << setw(5) <<
            zip << "," << setw(7) << employees << "\n";
          }
          else if (choice == 3) {
            cout << "Enter the new state value: " << endl;
            cin >> newVal;
            if (newVal.size() > 2)
              newVal = newVal.substr(0,2);
            dout << setw(40) << name << "," << setw(3) << rank << "," <<
            setw(20) << city << "," << setw(2) << newVal << "," << setw(5) <<
            zip << "," << setw(7) << employees << "\n";
          }
          else if (choice == 4) {
            cout << "Enter the new ZIP value: " << endl;
            cin >> newVal;
            if (newVal.size() > 5)
              newVal = newVal.substr(0,5);
            dout << setw(40) << name << "," << setw(3) << rank << "," <<
            setw(20) << city << "," << setw(2) << state << "," << setw(5) <<
            newVal << "," << setw(7) << employees << "\n";
          }
          else {
            cout << "Enter the new employees value: " << endl;
            cin >> newVal;
            if (newVal.size() > 7)
              newVal = newVal.substr(0,7);
            dout << setw(40) << name << "," << setw(3) << rank << "," <<
            setw(20) << city << "," << setw(2) << state << "," << setw(5) <<
            zip << "," << setw(7) << newVal << "\n";
          }
          dout.close();
        }
      }
    }
  }
}
void Database::createReport() {
  if (!open)
    cout << "Please open a Database before continuing" << endl;
  else {
    ofstream dout;
    string report = "report.txt";
    dout.open(report.c_str());
    ifstream din;
    din.open(data.c_str());
    for (int i = 1; i <= 10; i++)
    {
      string line;
      getline(din, line);
      dout << i << ": " << line;
      dout << endl;
    }
  }
}
void Database::addRecord() {
    if (!open)
      cout << "Please open a Database before continuing" << endl;
    else {
      string nameTemp, cityTemp, stateTemp, rankTemp, zipTemp, empTemp;
      cin.ignore();
      cout << "Enter the name:  ";
      getline(cin, nameTemp);
      cout << "Enter the rank:  ";
      getline(cin, rankTemp);
      cout << "Enter the city:  ";
      getline(cin, cityTemp);
      cout << "Enter the state:  ";
      getline(cin, stateTemp);
      cout << "Enter the zip code:  ";
      getline(cin, zipTemp);
      cout << "Enter the number of employees:  ";
      getline(cin, empTemp);
      if (nameTemp.size() > 40)
        nameTemp  = nameTemp.substr(0,40);
      if (rankTemp.size() > 3)
        rankTemp = rankTemp.substr(0,3);
      if (cityTemp.size() > 20)
        cityTemp = cityTemp.substr(0,20);
      if (stateTemp.size() > 2)
        stateTemp = stateTemp.substr(0,2);
      if (zipTemp.size() > 5)
        zipTemp = zipTemp.substr(0,5);
      if (empTemp.size() > 7)
        empTemp = empTemp.substr(0,7);
      ofstream myFile;
      myFile.open(overflow.c_str(), fstream::app);
      myFile << setw(40) << nameTemp << ","
              << setw(3) << rankTemp << ","
              << setw(20) << cityTemp << ","
              << setw(2) << stateTemp << ","
              << setw(5) << zipTemp << ","
      << setw(7) << empTemp << endl;
      myFile.close();
      numOverflow ++;
      myFile.open(config.c_str());
      myFile << numRecords << "," << numOverflow << endl;
      myFile << "NAME,RANK,CITY,STATE,ZIP,EMPLOYEES" << endl;
      myFile.close();

      if(numOverflow >= 5){
          fstream dataFile, overflowFile;
          if(numDeleted >= 0){
              fstream tempFile;
              dataFile.open(data.c_str());
              string tempCSV = "temp.csv";
              tempFile.open(tempCSV.c_str(), fstream::out);
              string name, rank, city, state, zip, employees;
              while(getline(dataFile, name, ',')){
                  if(name.size() > 40)
                      name = name.substr(0, 40);
                  getline(dataFile, rank, ',');
                  getline(dataFile, city, ',');
                  getline(dataFile, state, ',');
                  getline(dataFile, zip, ',');
                  getline(dataFile, employees, '\n');
                  rank.erase(remove_if(rank.begin(), rank.end(), ::isspace), rank.end());
                  if(rank == "-1") { }
                  else {
                      if (rank.size() > 3)
                        rank = rank.substr(0,3);
                      if (city.size() > 20)
                        city = city.substr(0,20);
                      if (state.size() > 2)
                        state = state.substr(0,2);
                      if (zip.size() > 5)
                        zip = zip.substr(0,5);
                      if (employees.size() > 7)
                        employees = employees.substr(0,7);
                      tempFile << setw(40) << name << ","
                           << setw(3) << rank << ","
                           << setw(20) << city << ","
                           << setw(2) << state << ","
                           << setw(5) << zip << ","
                      << setw(7) << employees << "\n";
                  }
              }
              dataFile.close();
              char fname[data.size() + 1];
              strcpy(fname, data.c_str());
              if(remove(fname) != 0){
                  cout << "\n\n\nTHE CODER HAS NO CLUE WHAY'S WRONG SO SHE'S JUST GONNA QUIT" << endl << endl << endl;
                  exit(0);
              }
              else{
                  char tempn[] = "temp.csv";
                  if(rename(tempn, fname) == 0) {}
                      //cout << "File renaming succeed. " << endl;
                  else {
                      perror("Error renaming file");
                      exit(0);
                  }
              }

          }
          dataFile.open(data.c_str(), fstream::out | fstream::app);
          overflowFile.open(overflow.c_str());
          string line;
          while(!overflowFile.eof()) {
              getline(overflowFile, line, ',');
              if(!overflowFile.eof())
                  dataFile << line << ",";
              else
                  dataFile << line;
          }
          dataFile.close();
          overflowFile.close();
          overflowFile.open(config.c_str());
          numRecords = numRecords - numDeleted + numOverflow;
          numOverflow = 0;
          overflowFile << numRecords << "," << numOverflow << "\n";
          overflowFile << "NAME,RANK,CITY,STATE,ZIP,EMPLOYEES" << endl;
          overflowFile.close();
          overflowFile.open(overflow.c_str(), ofstream::out | ofstream::trunc);
          overflowFile.close();

          sortFile();
      }
      cout << "New record added.\n\n";
  }
}

void Database::sortFile() {
    string name, rank, city, state, zip, emp;
    string minN, minR, minC, minS, minZ, minE;
    string junk;
    fstream dataFile, tempSorted;
    dataFile.open(data.c_str(), fstream::in);
    string tempcsv = "tempSorted.csv";
    tempSorted.open(tempcsv.c_str(), fstream::out | fstream::app);
    string prevMin = "";
    int a = 0;

    while(a < numRecords){
        minN = "~";
        while(getline(dataFile, name, ',') && name != "") {
            int loc = name.find_first_not_of(" ");
            name = name.substr(loc, 40);
            getline(dataFile, rank, ',');
            getline(dataFile, city, ',');
            getline(dataFile, state, ',');
            getline(dataFile, zip, ',');
            getline(dataFile, emp, '\n');
            if(name < minN && name > prevMin && state != "-1"){
                minN = name;
                minR = rank;
                minC = city;
                minS = state;
                minZ = zip;
                minE = emp;
            }
        }
        string tempN = minN;
        minN.erase(remove(minN.begin(), minN.end(), ' '), minN.end());
        if(minN == "~"){
            break;
        }
        tempSorted << setw(40) << tempN << ","
            << setw(3) << minR << ","
            << setw(20) << minC << ","
            << setw(2) << minS << ","
            << setw(5) << minZ << ","
            << setw(7) << minE << "\n";
        prevMin = minN;
        dataFile.close();
        dataFile.open(data.c_str(), fstream::in);
        a++;
    }
    dataFile.close();
    tempSorted.close();
    if(remove(data.c_str()) != 0){
        perror("Error deleting files");
    }
    else{
        if(rename(tempcsv.c_str(), data.c_str()) == 0) {}
        else {
            perror("Error renaming file");
            exit(0);
        }
    }


}


void Database::deleteRecord(string name) {
  if (!open)
    cout << "Please open a Database before continuing" << endl;
  else {
    if (name.size() > 40)
      name = name.substr(0,40);
    ifstream din;
    din.open(data.c_str());
    string rank, city, state, zip, employees;
    int result = searchRecord(din, name, rank, city, state, zip, employees);
    din.close();
    ofstream dout;
    if (result != -1) {
      //Check if record was "deleted"
      if (state == "-1")
        cout << "Error: Record not found" << endl;
      else {
        ofstream dout;
        dout.open(data.c_str(), ios::in);
        dout.seekp(result*RECORD_SIZE, ios::beg);
        string one = "-1";
        dout << setw(40) << name << "," << setw(3) << one << "," <<
        setw(20) << one << "," << setw(2) << one << "," << setw(5) <<
        one << "," << setw(7) << one << "\n";
        dout.close();
        numDeleted++;
      }
    }
    else {
      bool foundOverflow = false;
      int loc;
      din.open(overflow.c_str());
      string tempName, rank, city, state, zip, employees;
      int i = 0;
      while(i < numOverflow && !foundOverflow) {
        getRecord(din, i, rank, tempName, city, state, zip, employees);
        loc = tempName.find_first_not_of(" ");
        tempName = tempName.substr(loc,40);
        if (tempName == name) {
          foundOverflow = true;
        }
        else
          i++;
      }
      din.close();
      if (!foundOverflow) {
        cout << "Error: Record not found" << endl;
      }
      else {
        if (state == "-1")
          cout << "Error: Record not found" << endl;
        else {
          ofstream dout;
          dout.open(overflow.c_str(), ios::in);
          dout.seekp(i*RECORD_SIZE, ios::beg);
          string one = "-1";
          dout << setw(40) << name << "," << setw(3) << one << "," <<
          setw(20) << one << "," << setw(2) << one << "," << setw(5) <<
          one << "," << setw(7) << one << "\n";
          dout.close();
          numDeleted++;
        }
      }
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
bool Database::isOpen() {
  return open;
}
