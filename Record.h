#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
//Template for Record class
class Record {
  public:
    Record();
    ~Record();
    void read(fstream &in);
    void write(fstream &out);
    void setRank(int _rank);
    void setZip(int _zip);
    void setEmployees(int _employees);
    void setName(string _name);
    void setCity(string _city);
    void setState(string _state);
    void print();
    int getRank();
  private:
    int rank, zip, employees;
    string name, city, state;
};
