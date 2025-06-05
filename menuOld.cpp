#include <iostream>		//I/O operations
#include <windows.h>
#include <conio.h>		//Console I/O
#include <string>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'

using namespace std;

int menu(string [], int);
COORD GetConsoleCursorPosition(HANDLE);

int menu(string choices[], int size) {
	bool selecting = true;
	char c;
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD initial = GetConsoleCursorPosition(hstdout);																			//Grabs initial position... should be 0, row_num
	COORD current = GetConsoleCursorPosition(hstdout);																			//Current position same as initial position at beginning
	for (int i = 0; i < size; i++)
		cout << choices[i] << endl;																								//Displays entire array
	COORD final = GetConsoleCursorPosition(hstdout);																			//Grabs final position... should be 0, row_num + array_size + 1.. 1 cuz endl																											
	final.Y -= 1;																												//Corrects 1 due to endl
	SetConsoleCursorPosition(hstdout, initial);																					//Goes back to initial position
	SetConsoleTextAttribute(hstdout, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);										//Highlight
	cout << choices[0];																											//Overwrite first array element
	SetConsoleCursorPosition(hstdout, initial);																					//Goes back to initial position
	
	while(selecting) {
		switch(c = _getch()) {
			case KEY_UP:
				if (current.Y != initial.Y) {																							//If current array row is not upper bounds
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
				if (current.Y != final.Y) {																								//If current array row is not lower bounds
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
    }
    else {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}
