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
    if (choice == 1)
        db.createDatabase();
    else if (choice == 2)
        db.openDatabase();
    else if (choice == 3)
        db.closeDatabase();
    else if (choice == 4)
        db.displayRecord();
    else if (choice == 5)
        db.updateRecord();
    else if (choice == 6)
        db.createReport();
    else if (choice == 7)
        db.addRecord();
    else if (choice == 8) {
        string name;
        cout << "Enter the name of the company record to delete" << endl;
        cin >> name;
        db.deleteRecord(name);
    }
    else if (choice == 9 && db.isOpen()) {
            cout << "Please close the Database before exiting" << endl;
            choice = -1;
    }
    else if (choice == 9 && !db.isOpen())
      return 0;
    }
}
