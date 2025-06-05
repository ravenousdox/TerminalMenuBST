/** Link-based implementation of the ADT binary search tree.
@file EmployeeTree.cpp */

#include "EmployeeTree.h"

/******************************************************************************/
/* Method: addHelper      							                          */
/* Inputs: An employee pointer that serves at the root of a subtree, an       */
/*         a pointer to the employee you wish to add                          */
/* Outputs: The subtree with the new employee added                           */
/* Purpose: A recursive method that finds where to add an employee in sorted  */
/*          order, then adds that employee                                    */
/******************************************************************************/
EmployeeInfo* EmployeeTree::addHelper(EmployeeInfo* subTreePtr, EmployeeInfo* newEmployeeInfoPtr)
{
	if (subTreePtr == nullptr)															// An initially empty tree or empty subtree
		return newEmployeeInfoPtr;															// The employee being added is now the root of that empty subtree
	else if (subTreePtr->getID() > newEmployeeInfoPtr->getID())	                            // The employee being added belongs in the left subtree
	{
		EmployeeInfo* tempPtr = addHelper(subTreePtr->getLeftChildPtr(), newEmployeeInfoPtr);   // Moves to that subtree and attempts to add the employee there
		subTreePtr->setLeftChildPtr(tempPtr);                                           // The employee belongs as the left child (assigning root of empty subtree)
	}
	else 																				// EmployeeInfo being added belongs in the right subtree
	{
		EmployeeInfo* tempPtr = addHelper(subTreePtr->getRightChildPtr(), newEmployeeInfoPtr); 
		subTreePtr->setRightChildPtr(tempPtr);
	} // end if
	return subTreePtr;																	// Returns the subtree with the employee added
}

/******************************************************************************/
/* Method: findEmployee   							                          */
/* Inputs: An employee pointer that serves as the root of a subtree being     */
/*         seaarched, the ID of the employee you are trying to find           */
/* Outputs: The pointer the employee that was found OR nullptr if not found   */
/* Purpose: A helper method for the contains method. Used to retrieve an      */
/*          employee                                                          */
/******************************************************************************/
EmployeeInfo* EmployeeTree::findEmployee(EmployeeInfo* subTreePtr, int targetID) const
{
	if (subTreePtr == nullptr)	                                          // EmployeeInfo with ID not found
		return nullptr;
	else if (subTreePtr->getID() == targetID)                             // EmployeeInfo with matching ID found
		return subTreePtr;
	else if (subTreePtr->getID() > targetID)                              // ID will be found in left subtree
		return findEmployee(subTreePtr->getLeftChildPtr(), targetID);
	else
		return findEmployee(subTreePtr->getRightChildPtr(), targetID);    // ID will be found in right subtree
} 

/******************************************************************************/
/* Method: destroyTree    							                          */
/* Inputs: A pointer to an employee that serves as a subtree                  */
/* Outputs: None                                                              */
/* Purpose: A helper for the destructor. Deallocates each employee in the     */
/*          tree                                                              */
/******************************************************************************/
void EmployeeTree::destroyTree(EmployeeInfo* subTreePtr)
{
	if (subTreePtr != nullptr)								// While the employee being checked is not leaf
	{
		destroyTree(subTreePtr->getLeftChildPtr());         // Traverse in a post-order fashion, recursively
		destroyTree(subTreePtr->getRightChildPtr());        // searching until you have hit a leaf that can be removed
		delete subTreePtr;                                  // Deletes the leaf
		subTreePtr = nullptr;
	} // end if
} // end destroyTree

/******************************************************************************/
/* Method: inorderHelper		                           					  */
/* Inputs: A pointer to a function that takes an employee pointer as an       */
/*         argument, a pointer to an employee that serves as the root of a    */
/*         subtree to be traversed                                            */
/* Outputs: None                                                              */
/* Purpose: To maintain the wall between the client and data structure.       */
/******************************************************************************/
void EmployeeTree::inorderHelper(void visit(EmployeeInfo*), EmployeeInfo* subTreePtr) const
{
	if (subTreePtr != nullptr)									// While the employee being checked is not a leaf
	{
		inorderHelper(visit, subTreePtr->getLeftChildPtr());    // Traverse in an inorder fashion, recursively
		visit(subTreePtr);                                      // Visit that employee, passing it to the function
		inorderHelper(visit, subTreePtr->getRightChildPtr());
	} // end if
} // end inorderTraverse

/******************************************************************************/
/* Method: removeFinder   	                           						  */
/* Inputs: A pointer to an employee that serves as a subtree, the ID of the   */ 
/*         employee being removed, a boolean that serves as a flag on whether */
/*         the removal was successful                                         */
/* Outputs: A pointer to the subtree with the employee removed OR nullptr if  */
/*          the employee was not found                                        */
/* Purpose: To find the employee to be removed and attempt to remove it       */
/******************************************************************************/
EmployeeInfo* EmployeeTree::removeFinder(EmployeeInfo* subTreePtr, int targetID, bool& success)
{
	if (subTreePtr == nullptr)															    // No employee matching ID found
	{
		success = false;																    // Removal was unsuccessful
		return nullptr;
	}
	else if (subTreePtr->getID() == targetID)                                               // EmployeeInfo matching ID found
	{
		subTreePtr = removeHelper(subTreePtr);                                              // Attempts to remove the employee
		success = true;                                                                     // Removal was successful
		return subTreePtr;                                                                  // Return the new tree
	}
	else if (subTreePtr->getID() > targetID)                                                // EmployeeInfo will be found in the left subtree
	{
		EmployeeInfo* tempPtr = removeFinder(subTreePtr->getLeftChildPtr(), targetID, success); // Attempts to search and remove the employee in the left subtree
		subTreePtr->setLeftChildPtr(tempPtr);                                               // Adds the updated left subtree with the employee removed
		return subTreePtr;                                                                  // Return the new tree
	}
	else                                                                                    // EmployeeInfo will be found in the right subtree
	{
		EmployeeInfo* tempPtr = removeFinder(subTreePtr->getRightChildPtr(), targetID, success);
		subTreePtr->setRightChildPtr(tempPtr);
		return subTreePtr;
	}
}

/******************************************************************************/
/* Method: removeHelper  	                         						  */
/* Inputs: A pointer the employee being removed                               */
/* Outputs: A pointer to the subtree with the employee removed                */
/* Purpose: To remove the employee found by removeFinder and return the       */
/*          updated subtree                                                   */
/******************************************************************************/
EmployeeInfo* EmployeeTree::removeHelper(EmployeeInfo* employeePtr)
{
	if (employeePtr->isLeaf())																			// EmployeeInfo being removed has no children (is leaf)
	{
		delete employeePtr;                                                                             // EmployeeInfo is deallocated
		employeePtr = nullptr;                                                                          
		return employeePtr;                                                                             // Leaf is now nullptr and returned
	}
	else if (employeePtr->getLeftChildPtr() != nullptr && employeePtr->getRightChildPtr() != nullptr)      // EmployeeInfo being removed has two children
	{
		bool secondToLeftmost = false;																		// A flag to signify whether this is the second to left most child
		EmployeeInfo* successorPtr = twoChildHelper(employeePtr->getRightChildPtr(), secondToLeftmost);	        // Get the leftmost or second to leftmost child
		
		if (secondToLeftmost)																				// Is important because it controls what you do with the potential right subtree of the leftmost child
		{
			employeePtr->setID(successorPtr->getLeftChildPtr()->getID());									// Overwrite the contents of the employee being removed with its inorder successor
			employeePtr->setName(successorPtr->getLeftChildPtr()->getName());								// In this case the employee being removed right child's left subtree which contains the second to leftmost node, will point to leftmost (inorder successor) right subtree
			successorPtr->setLeftChildPtr(removeHelper(successorPtr->getLeftChildPtr()));					// Replace the inorder successor's position with its right subtree (or nullptr)
			return employeePtr; 
		} 
		else																								// ELse the employee being removed is second to leftmost child
		{																									
			employeePtr->setID(successorPtr->getID());														
			employeePtr->setName(successorPtr->getName());
			employeePtr->setRightChildPtr(removeHelper(successorPtr));										// Replaces the inorder successor with its right subtree (or nullptr)
			return employeePtr;
		}
	}
	else																								// EmployeeInfo being removed has one child
	{
		EmployeeInfo* employeeToConnectPtr;																	// The child subtree that needs to be connected after employee is removed
		if (employeePtr->getLeftChildPtr() != nullptr)                                                  // If the left child is occupied
			employeeToConnectPtr = employeePtr->getLeftChildPtr();                                      // The left subtree replaces the employee being removed
		else                                                                                            // The right child is occupied     
			employeeToConnectPtr = employeePtr->getRightChildPtr();                                     // The right subtree replaces the employee being removed
		delete employeePtr;																				// The employee is removed
		employeePtr = nullptr;                                                                          // The employee is set to nullptr
		return employeeToConnectPtr;                                                                    // The child subtree is returned
	}
}

/******************************************************************************/
/* Method: twoChildHelper        	                                          */
/* Inputs: A pointer to the subtree you are finding the leftmost              */
/*         employee (or second leftmost) of                                   */
/* Outputs: A pointer to the leftmost (or second leftmost) employee of a      */ 
/*          subtree                                                           */
/* Purpose: To find the inorder successor in the case an employee being       */
/*          removed has two children OR second to leftmost employee           */
/******************************************************************************/
EmployeeInfo* EmployeeTree::twoChildHelper(EmployeeInfo* employeePtr, bool& secondToLeftmost)
{
	if (employeePtr->getLeftChildPtr() == nullptr)										// If the leftmost child is the left child of the employee being removed
		return employeePtr;											    				// The employee being removed is the second leftmost child
	else if (employeePtr->getLeftChildPtr()->getLeftChildPtr() == nullptr)  			// Else the employee being checked is not nullptr, check if it is second to leftmost child
	{
		secondToLeftmost = true;														// If it is, signal that it is the second to leftmost child
		return employeePtr;																// Return the second to leftmost child
	} 
	else															    				//Else this is not the second to leftmost child, so move to the next one
	   	return twoChildHelper(employeePtr->getLeftChildPtr(), secondToLeftmost);        // Move to the next left child
}

// Default constructor
// The tree is empty
EmployeeTree::EmployeeTree() : rootPtr(nullptr) 
{
}

// Constructor given employee data
// The root of the tree is an employee with the data passed
EmployeeTree::EmployeeTree(int id, string name)
{
	rootPtr = new EmployeeInfo(id, name);	// Creates an employee and assigns it as the root of the tree
}

// Destructor
EmployeeTree::~EmployeeTree()
{
	destroyTree(rootPtr);    // Calls a helper that deallocates each employee in the tree using post-order traversal
}

/******************************************************************************/
/* Method: clear          				                                      */
/* Inputs: None                                                               */
/* Outputs: None                                                              */
/* Purpose: To clear the tree of all employees                                */
/******************************************************************************/
void EmployeeTree::clear()
{
	destroyTree(rootPtr);
}

/******************************************************************************/
/* Method: addEmployee    				                                      */
/* Inputs: The id and name of the employee being added                        */
/* Outputs: A boolean on whether the addition was successful                  */
/* Purpose: To add an employee to the tree in a sorted fashion                */
/******************************************************************************/
bool EmployeeTree::addEmployee(int id, string name) 
{	
	bool success = false;
	
	if (!contains(id)) {									  // If employee matching the ID does not already exist in the tree...
		EmployeeInfo* newEmployeeInfoPtr = new EmployeeInfo(id, name);    // Creates an employee with the data given 
		rootPtr = addHelper(rootPtr, newEmployeeInfoPtr);         // Passes the employee to an addHelper and updates the tree
		success = true;
	}
	
	return success;
}

/******************************************************************************/
/* Method: removeEmployee 							                          */
/* Inputs: The id of the employee being removed                               */
/* Outputs: A boolean on whether the removal was successful                   */
/* Purpose: To brutally remove an employee from the tree                      */
/******************************************************************************/
bool EmployeeTree::removeEmployee(int targetID)
{
	bool success = false;                                // Initially false
	rootPtr = removeFinder(rootPtr, targetID, success);  // Passes the ID to a helper and updates the tree
	return success;                                      // Returns whether the removal was a success
}

/******************************************************************************/
/* Method: contains	      							                          */
/* Inputs: The ID of the employee being searched for                          */
/* Outputs: A boolean on whether the employee with that ID was found          */
/* Purpose: To find whether an employee matching the ID is in the tree        */
/******************************************************************************/
bool EmployeeTree::contains(int targetID) const
{
	return (findEmployee(rootPtr, targetID) != nullptr);     // Passes the ID to a helper. If no employee is returned then they are not in the tree
}

/******************************************************************************/
/* Method: inorderTraverse	      							                  */
/* Inputs: A pointer to a function that takes an employee pointer as an       */
/*         argument                                                           */
/* Outputs: None                                                              */
/* Purpose: To traverse a tree in sorted order and perform an action on each  */
/*          employee (that does not change the employee)                      */
/******************************************************************************/
void EmployeeTree::inorderTraverse(void visit(EmployeeInfo*)) const
{
	inorderHelper(visit, rootPtr);     //Passes the pointer to the function to a helper along with the root of the tree
} // end inorderTraverse

