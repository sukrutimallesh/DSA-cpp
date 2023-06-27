#include <iostream>
#include "orgtree.h"

/**
 * Check if an employee is present in an organization chart.
 *
 * @param  head the head / root Employee of the organization chart
 * @param  e_id the employee id being searched
 * @return      true or false
 *		returns false if head is nullptr
 * @see
 */
bool Orgtree::isEmployeePresentInOrg(Employee* head, int e_id) {

    // Base case 1: Empty organization chart
    // If the head is nullptr, there are no employees in the chart, so return false
    if (head == nullptr) {
        return false;
    }

    // Base case 2: Employee found
    // If the employee ID of the current head matches the given ID, return true
    if (head->getEmployeeID() == e_id) {
        return true;
    }

    // Recursive case:
    // Search for the employee in each subtree of the head

    // Iterate through each direct report of the head
    for (Employee* directReport : head->getDirectReports()) {
        // Recursively call the function on each direct report
        // If the employee is found in any of the child subtrees, return true

        if (isEmployeePresentInOrg(directReport, e_id)) {
            return true;  // employee found in one of the child subtrees
        }
    }

    // If the employee is not found in any subtree, return false
    return false;
}

/**
 * Find all managers of an employee.
 *
 * @param  head     the head / root Employee of the organization chart
 * @param  e_id     the employee id being searched
 * @param  managers a vector of ids of all managers in the ascending order
 *                  of their tree height
 *                  i.e., managers starting from direct manager node to the root node
 *                  If the org chart is empty, or e_id is the head, or
 *                  e_id is not in the chart, managers should be empty after the search.
 * @return          is employee found
 * @see
 */
bool Orgtree::findManagersOfEmployee(Employee* head, int e_id, vector<int> &managers) {

    // Recursive implementation to find the managers of an employee with the given ID

    // Base case 1: Empty organization chart
    // If the head is nullptr, there are no employees in the chart, so return false
    if (head == nullptr) {
        return false;
    }

    // Base case 2: Employee found
    // If the employee ID of the current head matches the given ID, return true

    if (head->getEmployeeID() == e_id) {
        return true;
    }

    // Search subtrees from the head, after all subtrees are searched,
    // if employee e_id is found:
    // the head should be inserted to the managers vector along
    // the backtracking process of recursive calls

    // Note:
    // do NOT add the employee's own e_id to the passed-in managers vector

    // Flag to keep track of whether the employee is found in any child subtree
    bool employeeFound = false;

    // Recursive case:
    // Search through the direct reports of the current head
    for (Employee* directReport : head->getDirectReports()) {
        // Recursively call the function on each direct report to search for the employee
        if (findManagersOfEmployee(directReport, e_id, managers)) {
            // If the employee is found in any of the child subtrees,
            // add the current head (manager) to the managers vector before returning

            // Check if the current head's ID is not equal to the employee's ID
            // to avoid adding the employee's own ID to the vector
            if (head->getEmployeeID() != e_id) {
                managers.push_back(head->getEmployeeID());
            }

            // Set the flag to true since the employee is found in a child subtree
            employeeFound = true;
            break;  // Stop searching further as the employee is already found
        }
    }

    // Return the value of the employeeFound flag
    // If the flag is true, it means that the employee with the given ID was found in one of the child subtrees,
    // and the managers (including the current head) have been added to the managers vector.
    // If the flag is false, it means that the employee was not found in any subtree.
    // In this case, the managers vector remains unchanged.
    return employeeFound;

}

/**
 * Find the level of an employee in an organization chart / tree.
 *
 * <p>
 * The head / root of the org chart has a level of 0, children of the head have
 * a level of head plus 1, and so on and so forth...
 *
 * <p>
 * Assumption: e_id is unique among all employee IDs
 *
 * @param  head      the head / root Employee of the organization chart
 * @param  e_id      the employee id being searched
 * @param  headLevel the level of the head employee of the organization
 * @return    level of the employee in the org chart
 *      returns Employee::NOT_FOUND if e_id is not present or head is nullptr
 * @see
 */
int Orgtree::findEmployeeLevel(Employee* head, int e_id, int headLevel) {
    // Recursive implementation to find the level of an employee with the given ID

    // Base case 1: Empty organization chart
    if (head == nullptr) {
        return Employee::NOT_FOUND;  // Employee not found, return NOT_FOUND constant
    }

    // Base case 2: Employee found
    if (head->getEmployeeID() == e_id) {
        return headLevel;  // Return the level of the employee
    }

    // Recursive case:
    // Search for the employee in each subtree of the head
    for (Employee* directReport : head->getDirectReports()) {
        // Recursively call the function on each direct report, incrementing the level by 1

        int employeeLevel = findEmployeeLevel(directReport, e_id, headLevel + 1);
        if (employeeLevel != Employee::NOT_FOUND) {
            return employeeLevel;  // Return the level of the employee if found in one of the child subtrees
        }
    }

    // If the employee is not found in any subtree, return NOT_FOUND constant
    return Employee::NOT_FOUND;
}

/**
 * Find the closest shared manager of two employees e1 and e2.
 *
 * <p>
 * There are two possible organizational relationships between two employees in the org chart:
 * case 1: e1 or e2 is a manager of the other employee;
 * case 2: e1 or e2 is not a manager of the other employee, they have at least one shared manager
 *
 * Employee 1 is a manager of employee 2 if employee 1 is an ancestor of employee 2 in the organization chart
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched
 * @return   closest shared manager in the org chart between employee e1 and employee e2
   *           if head is nullptr, returns nullptr
   *           if neither e1 or e2 is present, returns nullptr
   *           if e1 is present and e2 is not, returns e1
   *           if e2 is present and e1 is not, returns e2
   *           if e1 and e2 both are present, returns their shared manager
   *              if e1 is a manager (ancestor) of e2, returns e1
   *              else if e2 is a manager (ancestor) of e1, returns e2
   *              else returns the shared manager of e1 and e2
 * @see
 */
Employee* Orgtree::findClosestSharedManager(Employee* head, int e1_id, int e2_id) {

    // base case 1: empty organization chart
    if (head == nullptr) {
        return nullptr;  // If the head is nullptr, there are no employees in the chart, so return nullptr
    }

    // base case 2: either e1_id or e2_id is the same as the head / root
    if (head->getEmployeeID() == e1_id || head->getEmployeeID() == e2_id) {
        return head;  // Return the head / root if either e1_id or e2_id matches its employee ID
    }

    // Recursively traverse through direct reports of the head to find
    // where e1 and e2 are

    /*
       For each recursive call (starting from the root), you need to handle three possible scenarios:
       1) if e1 is found in one subtree, and e2 is found from another subtree;
          the head at that recursive step would be the closest shared manager of e1 and e2.

          you can use the returned pointer (being NOT NULL) from findClosestSharedManager
          to see if e1 or e2 is found from a subtree (one of the base cases).

       2) if either e1 or e2 is first found in one subtree (following one subtree),
          but the other employee is NOT found from any other subtree, then the found
          employee must either be the manager of the other employee, or the other employee
          is NOT in the org chart; in either case, the first found employee should be
          returned as the shared manager.

       3) if neither e1 or e2 is found in the org chart, return nullptr
    */

    // Initialize e1_manager and e2_manager pointer to nullptr
    Employee* e1_manager = nullptr, *e2_manager = nullptr;

    // Iterate through each direct report of the current head
    for (Employee* directReport : head->getDirectReports()) {
        // Recursively call findClosestSharedManager on each direct report
        Employee* sharedManager = findClosestSharedManager(directReport, e1_id, e2_id);

        // If a shared manager is found from the recursive call
        if (sharedManager != nullptr) {
            // Check if the shared manager is the same as e1_id
            if (sharedManager->getEmployeeID() == e1_id) {
                e1_manager = sharedManager; // Update e1_manager to the shared manager
            }

            // Check if the shared manager is the same as e2_id
            else if (sharedManager->getEmployeeID() == e2_id) {
                e2_manager = sharedManager; // Update e2_manager to the shared manager
            }

            // If e1 and e2 are found in different subtrees (different shared managers),
            // return the shared manager as the closest shared manager of e1 and e2
            else {
                return sharedManager;
            }
        }

        // Check if both e1_manager and e2_manager have been found
        if (e1_manager && e2_manager) {
            return head;  // Return the current head as the closest shared manager
        }
    }

    // Check if e1_manager has been found
    if (e1_manager) {
        return e1_manager;  // Return e1_manager as the closest shared manager (e2 is not found)
    }

    // Check if e2_manager has been found
    if (e2_manager) {
        return e2_manager;  // Return e2_manager as the closest shared manager (e1 is not found)
    }

    return nullptr;  // Neither e1 nor e2 is found, return nullptr
}

/**
 * Calculate the number of managers between employee e1 and employee e2.
 *
 * <p>
 * The number of managers between employee e1 and employee e2 can be calculated by:
 *  number of edges between employee 1 and closest shared manager +
 *  number of edges between employee 2 and closest shared manager - 1
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched
 * @return   number of managers between employee e1 and employee e2
 *           returns Employee::NOT_FOUND if either e1 or e2 is not present in the chart or head is nullptr
 * @see
 */
int Orgtree::findNumOfManagersBetween(Employee* head, int e1_id, int e2_id) {

    // Indirectly uses recursion through the functions it calls (isEmployeePresentInOrg, findClosestSharedManager, and findEmployeeLevel).
    // These functions use recursion internally to traverse the organization hierarchy and perform the required operations


    // Continue only if both employee nodes e1_id and e2_id are in the org chart tree
    // otherwise, return Employee::NOT_FOUND
    if (!isEmployeePresentInOrg(head, e1_id) || !isEmployeePresentInOrg(head, e2_id)) {
        return Employee::NOT_FOUND;
    }

    // The number of managers between employee e1 and employee e2 can be calculated by:
    // number of edges between e1_id and closest shared manager +
    // number of edges between e2_id and closest shared manager - 1

    // Find the lowest common manager of e1 and e2
    Employee* sharedManager = findClosestSharedManager(head, e1_id, e2_id);

    // Calculate the number of managers between e1 and e2
    // Start by calculating the level of e1_id relative to the shared manager
    // Add the level of e2_id relative to the shared manager
    // Subtract 1 to exclude the shared manager itself from the count

    int numManagers = findEmployeeLevel(sharedManager, e1_id, 0) +
                      findEmployeeLevel(sharedManager, e2_id, 0) - 1;

    return numManagers; // Return the number of managers between e1 and e2 (excluding the shared manager)

}

/** Recursively delete a tree
 *  The proper implementation of this function is also needed for
 *  passing the valgrind memory leaking test.
 *
 * <p>
 * Traversing from the head / root node, recursively deallocate
 * the memory of the descendants from the leaf node level.
 *
 * DO NOT worry about removing them from the vector directReports
 *
 * Use post order traversal:
 * Delete / deallocate the children recursively
 * Delete / deallocate the current node after deleting its children
 *     Before deleting the current node, print its employee ID and a new line
 *     This part will be autograded as well as manually inspected for grading
 *
 * For example, with the following org chart, the post order traversal
 * order would be 5 6 2 7 8 3 1, and the nodes should be deleted in that order
 *             1
 *           /    \
 *           2    3
 *          / \  / \
 *          5 6  7 8
 *
 * @param  head  the head / root Employee of the organization chart
 * @return   None
 *
 * @see
 */
void Orgtree::deleteOrgtree(Employee* head) {
    // Recursive implementation to delete the entire organization tree

    // Base case: empty tree or organization chart
    if (head == nullptr) {
        return;  // No employees to delete, so return
    }

    // Delete children recursively
    // Traverse through each direct report of the current head node
    for (Employee* directReport : head->getDirectReports()) {
        deleteOrgtree(directReport);  // Recursively delete all child subtrees
    }

    // Print the employee ID of the current node before deleting
    cout << "Deleting employee with ID: " << head->getEmployeeID() << endl;

    // Delete the current node after deleting its children
    delete head;
}
