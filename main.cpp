#include <iostream>
#include "Database.h"
using namespace std;
int main() {
  int choice = 0;
  Database db;
  while (choice != 9) {
    cout << "Operations: " << endl;
    cout << "1) Create new database" << endl;
    cout << "2) Open database" << endl;
    cout << "3) Close database" << endl;
    cout << "4) Display record" << endl;
    cout << "5) Update record" << endl;
    cout << "6) Create report" << endl;
    cout << "7) Add record" << endl;
    cout << "8) Delete record" << endl;
    cout << "9) Quit" << endl;
    cin >> choice;
    switch(choice) {
      case 1:
        db.createDatabase();
      case 2:
        db.openDatabase();
      case 3:
        db.closeDatabase();
      case 4:
        db.displayRecord();
      case 5:
        db.updateRecord();
      case 6:
        db.createReport();
      case 7:
        db.addRecord();
      case 8:
        db.deleteRecord();
      case 9:
        return 0;
    }
  }
}
