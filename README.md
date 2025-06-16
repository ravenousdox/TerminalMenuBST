# Employee Management BST

This project is a console-based employee management system built around a Binary Search Tree (BST). It was originally created for a data structures course and later expanded with a custom menu interface for a smoother user experience.

## Features

- **Binary Search Tree storage**: employee records are kept in a BST for efficient insertion, removal and search.
- **Interactive console menu**: navigate with arrow keys and `Enter` thanks to Windows API console control.
- **Employee operations**:
  - display the full roster in order
  - search by ID
  - add new employees
  - remove employees
- **File loading**: read an input text file containing `ID name` pairs to populate the tree on start up (see `employeeData.txt`).

## Building

The program relies on Windows console functions, so it must be compiled on Windows. A simple `g++` invocation is shown below:

```bash
g++ client.cpp EmployeeTree.cpp EmployeeInfo.cpp menu.cpp -o client.exe
```

Any C++17 (or later) compiler that supports Windows headers should work. Running `client.exe` launches the interactive menu.

## File Overview

- `EmployeeInfo.*` – defines the `EmployeeInfo` nodes stored in the tree.
- `EmployeeTree.*` – implements all BST logic (insert, remove, traversal).
- `menu.*` – draws the arrow-key driven menu using the Windows console API.
- `client.cpp` – program entry point and user interaction flow.
- `clientNoMenu.cpp` – alternate client without the dynamic menu.
- `win_helpers.h` – wraps `windows.h` to avoid name collisions.

## Sample Data

The repository includes a small data file (`employeeData.txt`) used by default:

```
6702 James B W Bevis
1255 Romney Wordsworth
1071 Revis Jacara
2390 Clegg Forbes
1558 Kalin Tros
7406 Archibald Beechcroft
7562 Penthor Mul
3004 Bartlet Finchley
4922 Latham Bine
8483 Jeff Myrtlebank
```

## Acknowledgements

This application grew out of coursework for COSC 2436 (Data Structures) and showcases using fundamental data structures to build a minimal console application without external UI libraries.
