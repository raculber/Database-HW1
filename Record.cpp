#include <iostream>
#include <fstream>
#include "Record.h"
using namespace std;
Record::Record() {
  rank = 0;
  zip = 0;
  employees = 0;
  name = "";
  city = "";
  state = "";
}
Record::~Record() {

}
void Record::printData() {
  cout << "Rank: "  << rank << " Name: " << name << " City: " << city
  << " State: " << state << " Zip: " << zip << " Employees: " << employees << endl;
}
void Record::read(fstream &in) {
  in >> rank >> name >> city >> state >> zip >> employees;
}
void Record::write(fstream &out) {
  out << setw(3) << setw(20) << setw(15) << setw(2) << setw(5) << setw(7) << endl;
}
void Record::setRank(int _rank) {
  rank = _rank;
}
void Record::setZip(int _zip) {
  zip = _zip;
}
void Record::setEmployees(int _employees) {
  employees = _employees;
}
void Record::setName(string _name) {
  name = _name;
}
void Record::setCity(string _city) {
  city = _city;
}
void Record::setState(string _state) {
  state = _state;
}
int Record::getRank() {
  return rank;
}
