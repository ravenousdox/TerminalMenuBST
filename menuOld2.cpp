#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define byte WindowsByteHack // Avoid collision with std::byte

#include <windows.h>
#undef byte

#include <iostream>
#include <conio.h>
#include <string>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'

using namespace std;

int menu(string[], int);
COORD GetConsoleCursorPosition(HANDLE);

// Clears the screen based on OS
void clearScreen() {
    // Windows-specific clear
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

int menu(string choices[], int size) {
    bool selecting = true;
    char c;
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

    clearScreen();  // ✅ Clear screen before drawing new menu

    COORD initial = GetConsoleCursorPosition(hstdout);
    COORD current = initial;

    // Print all choices
    for (int i = 0; i < size; i++) {
        cout << choices[i] << endl;
    }

    COORD final = GetConsoleCursorPosition(hstdout);
    final.Y -= 1;

    SetConsoleCursorPosition(hstdout, initial);
    SetConsoleTextAttribute(hstdout, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    cout << choices[0];
    SetConsoleCursorPosition(hstdout, initial);

    while (selecting) {
        switch (c = _getch()) {
            case KEY_UP:
                if (current.Y != initial.Y) {
                    SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    cout << choices[current.Y - initial.Y];
                    current.Y--;
                    SetConsoleCursorPosition(hstdout, current);
                    SetConsoleTextAttribute(hstdout, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                    cout << choices[current.Y - initial.Y];
                    SetConsoleCursorPosition(hstdout, current);
                }
                break;
            case KEY_DOWN:
                if (current.Y != final.Y) {
                    SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    cout << choices[current.Y - initial.Y];
                    current.Y++;
                    SetConsoleCursorPosition(hstdout, current);
                    SetConsoleTextAttribute(hstdout, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                    cout << choices[current.Y - initial.Y];
                    SetConsoleCursorPosition(hstdout, current);
                }
                break;
            case KEY_ENTER:
                SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                SetConsoleCursorPosition(hstdout, final);
                cout << endl;
                selecting = false;
                break;
        }
    }

    return (current.Y - initial.Y);
}

COORD GetConsoleCursorPosition(HANDLE hstdout) {
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hstdout, &cbsi)) {
        return cbsi.dwCursorPosition;
    } else {
        COORD invalid = {0, 0};
        return invalid;
    }
}
