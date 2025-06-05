#ifndef MENU_H
#define MENU_H

#include <string>

void clearScreen();
int menu(std::string choices[], int size);
int GetConsoleCursorPosition(void* hConsoleOutput);

#endif