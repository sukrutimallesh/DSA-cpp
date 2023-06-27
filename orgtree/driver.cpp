#include "orgtree.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void asserts(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
        // If you do comment this out, ignore the
        // "All test cases passed!" printout
        exit(EXIT_FAILURE);
    }
}

//TODO
int main(int argc, char **argv) {
    /*
     * Construct the following organization chart for testing
     *                1
     *           /    \    \
     *           2    3    4
     *          / \  / \   \
     *          5 6  7 8   9
     *         /   \       \
     *         10  11      12
     */

    Employee *head = new Employee(1, vector<int>{2, 3, 4});
    Employee *e2 = head->getDirectReports().at(0);
    Employee *e3 = head->getDirectReports().at(1);
    Employee *e4 = head->getDirectReports().at(2);

    e2->addDirectReports(vector<int>{5, 6});
    e3->addDirectReports(vector<int>{7, 8});
    e4->addDirectReport(9);

    Employee *e5 = e2->getDirectReports().at(0);
    Employee *e6 = e2->getDirectReports().at(1);
    Employee *e9 = e4->getDirectReports().at(0);

    e5->addDirectReport(10);
    e6->addDirectReport(11);
    e9->addDirectReport(12);

    // Test an empty organization chart
    Employee* emptyHead = nullptr;
    bool emptyPresent = Orgtree::isEmployeePresentInOrg(emptyHead, 1);
    asserts(emptyPresent == false, "Empty chart should return false for isEmployeePresentInOrg");

    // Test a chart with only one employee
    Employee* singleEmployee = new Employee(1);
    bool singlePresent = Orgtree::isEmployeePresentInOrg(singleEmployee, 1);
    asserts(singlePresent, "ID 1 Present in single employee chart, your code returned false");

    // Construct a different organization chart
    /*
     * Organization Chart:
     *
     *             100
     *            /   \
     *          200    300
     *         /  \      \
     *       201   202    301
     *       /        \
     *     203        302
     *     /             \
     *   204             303
     *                   /   \
     *                 401    402
     */

    Employee* head1 = new Employee(100, vector<int>{200, 300});
    Employee* e200 = head1->getDirectReports().at(0);
    Employee* e300 = head1->getDirectReports().at(1);
    e200->addDirectReport(201);
    e200->addDirectReport(202);
    e300->addDirectReport(301);

    Employee* e201 = e200->getDirectReports().at(0);
    Employee* e202 = e200->getDirectReports().at(1);
    e201->addDirectReport(203);
    e202->addDirectReport(302);

    Employee* e203 = e201->getDirectReports().at(0);
    Employee* e302 = e202->getDirectReports().at(0);
    e203->addDirectReport(204);
    e302->addDirectReport(303);

    Employee* e303 = e302->getDirectReports().at(0);
    e303->addDirectReport(401);
    e303->addDirectReport(402);



    // Test isEmployeePresentInOrg function
    bool employeePresent = Orgtree::isEmployeePresentInOrg(head, 6);
    asserts(employeePresent, "ID 6 Present in tree, your code returned false");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, -2);
    asserts(employeePresent == false, "ID -2 Not present in tree");


    bool employeePresent1 = Orgtree::isEmployeePresentInOrg(head1, 201);
    asserts(employeePresent1, "ID 201 Present in tree, your code returned false");
    employeePresent1 = Orgtree::isEmployeePresentInOrg(head1, 401);
    asserts(employeePresent1, "ID 401 Present in tree, your code returned false");
    employeePresent1 = Orgtree::isEmployeePresentInOrg(head1, 999);
    asserts(employeePresent1 == false, "ID 999 Not present in tree");


    // Test findManagersOfEmployee function
    vector<int> manager_ids;
    employeePresent = Orgtree::findManagersOfEmployee(head, 11, manager_ids);
    asserts(employeePresent, "ID 11 Present in tree, your code returned false");
    vector<int> expected_manager_ids{ 6, 2, 1 };
    asserts(manager_ids == expected_manager_ids,
            "Your code should return (6, 2, 1) as managers of employee 11");
    manager_ids.clear();
    employeePresent = Orgtree::findManagersOfEmployee(head, -2, manager_ids);
    asserts(manager_ids.size() == 0, "ID -2 is not present in tree, its manager ids should be empty");


    vector<int> managerIds;
    employeePresent1 = Orgtree::findManagersOfEmployee(head1, 303, managerIds);
    asserts(employeePresent1, "ID 303 Present in tree, your code returned false");
    vector<int> expectedManagerIds{ 302, 202, 200, 100 };
    asserts(managerIds == expectedManagerIds, "Your code should return (302, 202, 200, 100) as managers of employee 303");
    managerIds.clear();
    employeePresent1 = Orgtree::findManagersOfEmployee(head1, 401, managerIds);
    asserts(employeePresent1, "ID 401 Present in tree, your code returned false");
    vector<int> expectedManagerIds2{ 303, 302, 202, 200, 100 };
    asserts(managerIds == expectedManagerIds2, "Your code should return (303, 302, 202, 200, 100) as managers of employee 401");
    managerIds.clear();
    employeePresent1 = Orgtree::findManagersOfEmployee(head1, -100, managerIds);
    asserts(managerIds.size() == 0, "ID -100 is not present in tree, its manager ids should be empty");


    // Test findEmployeeLevel function
    int employeeLevel = Orgtree::findEmployeeLevel(head, 4, 0);
    asserts(employeeLevel == 1, "Level of ID 4 returns " + to_string(employeeLevel) + ", expected 1");



    int employeeLevel1 = Orgtree::findEmployeeLevel(head1, 202, 0);
    asserts(employeeLevel1 == 2, "Level of ID 202 returns " + to_string(employeeLevel1) + ", expected 2");

    int employeeLevel2 = Orgtree::findEmployeeLevel(head1, 300, 0);
    asserts(employeeLevel2 == 1, "Level of ID 300 returns " + to_string(employeeLevel2) + ", expected 1");

    int employeeLevel3 = Orgtree::findEmployeeLevel(head1, 100, 0);
    asserts(employeeLevel3 == 0, "Level of ID 100 returns " + to_string(employeeLevel3) + ", expected 0");

    int employeeLevel4 = Orgtree::findEmployeeLevel(head1, 999, 0);
    asserts(employeeLevel4 == Employee::NOT_FOUND, "Level of ID 999 returns " + to_string(employeeLevel4) + ", expected NOT_FOUND");



    // Test findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // Assert / verify the returned Employee* has the expected Employee ID

    Employee* closestSharedManager = Orgtree::findClosestSharedManager(head, 5, 11);
    asserts(closestSharedManager != nullptr && closestSharedManager->getEmployeeID() == 2,
            "The closest shared manager of employees 5 and 11 should be ID 2");

    closestSharedManager = Orgtree::findClosestSharedManager(head, 6, 9);
    asserts(closestSharedManager != nullptr && closestSharedManager->getEmployeeID() == 1,
            "The closest shared manager of employees 6 and 9 should be ID 1");

    closestSharedManager = Orgtree::findClosestSharedManager(head, 7, 12);
    asserts(closestSharedManager != nullptr && closestSharedManager->getEmployeeID() == 1,
            "The closest shared manager of employees 7 and 12 should be ID 1");


    Employee* closestSharedManager1 = Orgtree::findClosestSharedManager(head1, 201, 302);
    asserts(closestSharedManager1 != nullptr && closestSharedManager1->getEmployeeID() == 200,
            "The closest shared manager of employees 201 and 302 should be ID 200");

    closestSharedManager1 = Orgtree::findClosestSharedManager(head1, 204, 401);
    asserts(closestSharedManager1 != nullptr && closestSharedManager1->getEmployeeID() == 200,
            "The closest shared manager of employees 204 and 401 should be ID 200");

    closestSharedManager1 = Orgtree::findClosestSharedManager(head1, 303, 301);
    asserts(closestSharedManager1 != nullptr && closestSharedManager1->getEmployeeID() == 100,
            "The closest shared manager of employees 303 and 301 should be ID 100");

    closestSharedManager1 = Orgtree::findClosestSharedManager(head1, 401, 402);
    asserts(closestSharedManager1 != nullptr && closestSharedManager1->getEmployeeID() == 303,
            "The closest shared manager of employees 401 and 402 should be ID 303");


    // Test findNumOfManagersBetween function
    int numManagers = Orgtree::findNumOfManagersBetween(head, 10, 11);
    asserts(numManagers == 3, "Managers between 10 and 11 returns " + to_string(numManagers) + ", expected 3");

    int numManagers1 = Orgtree::findNumOfManagersBetween(head1, 201, 302);
    asserts(numManagers1 == 2, "Managers between 201 and 302 returns " + to_string(numManagers1) + ", expected 2");

    int numManagers2 = Orgtree::findNumOfManagersBetween(head1, 203, 301);
    asserts(numManagers2 == 4, "Managers between 203 and 301 returns " + to_string(numManagers2) + ", expected 4");


    // Test deleteOrgtree function
    // VERY IMPORTANT: Related to valgrind memory leaking detection testing,
    // You MUST call your deleteOrgtree function at the end of this driver testing code
    // to delete all the allocated memory for the tree.

    Orgtree::deleteOrgtree(head);

    // Delete the remaining allocated memory
    Orgtree::deleteOrgtree(emptyHead);
    Orgtree::deleteOrgtree(singleEmployee);

    // Test deleteOrgtree function
    Orgtree::deleteOrgtree(head1);

    // Use the printed employee ID along the sequence of deletion to verify your implementation

    cout << endl << "All test cases passed!" << endl;

    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}
