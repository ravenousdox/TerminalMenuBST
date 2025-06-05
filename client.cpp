/** client file
@file client.cpp */

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "win_helpers.h"     // handles Windows includes and byte workaround

#include <conio.h>           // _getch
#include <iostream>
#include <fstream>
#include <limits>
#include <string>

#include "EmployeeTree.h"
#include "menu.h"

using namespace std;

/* ----------- fwd declarations ------------------------------------------- */
void grabFile(ifstream& file);
void readLines(ifstream& file, EmployeeTree& tree);
void display(EmployeeInfo* ptr);
void pauseWithHighlight();

/* ----------- main -------------------------------------------------------- */
int main() {
    EmployeeTree roster;
    ifstream     file;
    int          selection;

    cout << "DISCLAIMERS:\n"
            "1) Enter valid arguments for the options\n"
            "2) Use Arrow Keys and Enter to navigate the menu\n\n";

    grabFile(file);
    readLines(file, roster);
    cout << '\n';

    string choices[] = {
        "Display Employee",
        "Search for an Employee",
        "Add an Employee",
        "Remove an Employee",
        "Exit"
    };
    const int menuCnt = sizeof choices / sizeof *choices;

    do {
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        selection = menu(choices, menuCnt);   // main menu
        system("cls");                        // clear BEFORE showing action

        switch (selection) {
            case 0: {                         // display roster
                roster.inorderTraverse(display);
                pauseWithHighlight();
                break;
            }
            case 1: {                         // search
                int id;
                cout << "Enter an employee ID to search for: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << '\n'
                     << (roster.contains(id)
                         ? "Employee matching ID found!\n"
                         : "Employee matching ID not found\n");

                pauseWithHighlight();
                break;
            }
            case 2: {                         // add
                int    id;
                string name;
                cout << "Enter the ID of the employee you are adding: ";
                cin >> id;
                cin.ignore();
                cout << "Enter the name of the employee you are adding: ";
                getline(cin, name);

                roster.addEmployee(id, name);
                cout << "\nEmployee added.\n";
                pauseWithHighlight();
                break;
            }
            case 3: {                         // remove
                int id;
                cout << "Enter the ID of the employee you are removing: ";
                cin >> id;
                cin.ignore();

                cout << '\n'
                     << (roster.removeEmployee(id)
                         ? "Removal successful!\n"
                         : "Employee not found\n");

                pauseWithHighlight();
                break;
            }
        }
    } while (selection != 4);                 // 4 == “Exit”

    return 0;
}

/* ----------- helpers ----------------------------------------------------- */
void grabFile(ifstream& file) {
    string name;
    cout << "Input the file to be read without the extension: ";
    cin  >> name;
    file.open(name + ".txt");

    while (!file) {
        cerr << "\nFile \"" << name << ".txt\" does not exist or cannot be found.\n";
        cout << "Re-enter the employee data file (without extension): ";
        cin  >> name;
        file.open(name + ".txt");
    }
}

void readLines(ifstream& file, EmployeeTree& tree) {
    string id, name;
    while (getline(file, id, ' ') && getline(file, name))
        if (!id.empty() && !name.empty())
            tree.addEmployee(stoi(id), name);
}

void display(EmployeeInfo* ptr) {
    cout << ptr->getID() << " | " << ptr->getName() << '\n';
}

/* ---- draws a highlighted “Return to Menu” line, waits for one Enter ----- */
void pauseWithHighlight() {
    cout << '\n';

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    /* remember where we start printing the option */
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h, &csbi);
    COORD here = csbi.dwCursorPosition;

    /* draw highlighted text */
    SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    cout << "Return to Menu";
    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    /* put cursor back on the highlight so user sees it */
    SetConsoleCursorPosition(h, here);

    /* wait for a single Enter (ASCII 13) */
    while (_getch() != 13) { /* do nothing */ }

    system("cls");   // clean slate before the main menu is redrawn
}
