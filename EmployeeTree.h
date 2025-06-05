/** Link-based implementation of the ADT binary search tree.
@file EmployeeTree.h */

#ifndef _EMPLOYEE_TREE
#define _EMPLOYEE_TREE

#include "EmployeeInfo.h"
#include <iostream>

class EmployeeTree {
	private:
		EmployeeInfo* rootPtr;    // The root node of the binary search tree
		
	protected:

	    // Returns the updated subtree with the new employee added
		EmployeeInfo* addHelper(EmployeeInfo* subTreePtr, EmployeeInfo* newEmployeeInfoPtr);	
		
		// Returns the employee matching the ID OR nullptr if not found
		EmployeeInfo* findEmployee(EmployeeInfo* subTreePtr, int targetID) const;			
		
		// Returns none
		void destroyTree(EmployeeInfo* subTreePtr);										
		
		// Returns none
		void inorderHelper(void visit(EmployeeInfo*), EmployeeInfo* subTreePtr) const;	
		
		// Returns a pointer to the updated subtree with the employee removed OR nullptr if not found
		EmployeeInfo* removeFinder(EmployeeInfo* subTreePtr, int targetID, bool& success);	
		
		// Returns a pointer to the updated subtree with the employee removed
		EmployeeInfo* removeHelper(EmployeeInfo* employeePtr);						
		
		// Returns the inorder successor of an employee or its parent (the employee with the smallest ID greater than the one being removed)
		EmployeeInfo* twoChildHelper(EmployeeInfo* employeePtr, bool& secondToLeftmost);
		
	public:
		EmployeeTree();							// Default constructor
		EmployeeTree(int id, string name);      // Customized constructor given employee data
		virtual ~EmployeeTree();                // Customized destructor
		
		// Returns none
		void clear();

		// Returns true if addition was successful, false otherwise
		bool addEmployee(int id, string name);
		
		// Returns true if removal was successful, false otherwise
		bool removeEmployee(int targetID);
		
		// Returns true if employee matching ID was found in tree, false otherwise
		bool contains(int targetID) const;
	
	    // Returns none
		void inorderTraverse(void visit(EmployeeInfo*)) const;				
		
}; // end EmployeeTree

//#include "EmployeeTree.cpp"
#endif 
