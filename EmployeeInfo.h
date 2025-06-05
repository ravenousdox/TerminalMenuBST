/** A class of nodes for a link-based binary tree.
@file EmployeeInfo.h */

#ifndef _EMPLOYEE_INFO
#define _EMPLOYEE_INFO

#include <string>

using namespace std;

class EmployeeInfo
{
	private:
		int id; 					// The ID of the employee
		string name;                // The name of the employee
		EmployeeInfo* leftChildPtr;     // An employee with an ID less than this employee
		EmployeeInfo* rightChildPtr;    // An employee with an ID greater than this employee
		
	public:

		EmployeeInfo();                           // Default constructor
		EmployeeInfo(int anID, string aName);     // Customized constructor given employee data 
		
		// Returns none
		void setName(string aName);
		void setID(int anID);
		void setLeftChildPtr(EmployeeInfo* leftPtr);
		void setRightChildPtr(EmployeeInfo* rightPtr);
		
		// Returns the ID of the employee
		int getID() const;
		
		// Returns the name of the employee
		string getName() const;
		
		// Returns the left child of the employee or nullptr
		EmployeeInfo* getLeftChildPtr() const;
		
		// Returns the right child of the employee or nullptr
		EmployeeInfo* getRightChildPtr() const;
		
		// Returns true if the employee has no children
		bool isLeaf() const;
		
}; // end EmployeeInfo

//#include "EmployeeInfo.cpp"
#endif 
