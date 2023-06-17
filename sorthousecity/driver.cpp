#include "sorthousecity.h"
#include <string>
#include <iostream>
#include <vector>

#define CITY_SD "SD"
#define CITY_IR "IR"
#define CITY_LA "LA"

using namespace std;

// a print helper
void printvector(const string &prefix, const vector<string> &v)
{
    cout << prefix << " ";
    for (const string &m : v)
        cout << m << ' ';
    cout << "\n";
}

// a unit test helper
void test_sorting(const vector<string> &order,
                  const vector<string> &inv,
                  const vector<string> &expectedOut)
{

    printvector("Promotion Order:", order);
    printvector("House Inventory:", inv);

    vector<string> result_from_test =
        SortHouseCity::sortHouseInventory(inv, order);

    printvector("Expected:", expectedOut);
    printvector("Returned:", result_from_test);

    if (expectedOut != result_from_test)
        cout << "Test FAILED: Returned did not match expected" << endl;
    else
        cout << "Test Passed" << endl;
}

// test sorting inventory array with one element
void test_oneEleArr()
{
    cout << "Test sorting an array with one element ..." << endl;
    test_sorting(vector<string>{CITY_SD, CITY_IR, CITY_LA}, // order
                 vector<string>{CITY_LA},                   // inventory
                 vector<string>{CITY_LA});                  // expected sorted inventory
}

// test sorting inventory array with two elements
void test_twoEleArr()
{
    cout << "Test sorting an array with two elements ..." << endl;
    test_sorting(vector<string>{CITY_IR, CITY_SD, CITY_LA}, // order
                 vector<string>{CITY_LA, CITY_IR},          // inventory
                 vector<string>{CITY_IR, CITY_LA});         // expected sorted inventory
}

// test sorting inventory array with many elements
void test_multipleEleArr()
{
    cout << "Test sorting an array with many elements ..." << endl;
    test_sorting(vector<string>{CITY_SD, CITY_IR, CITY_LA}, // order
                 vector<string>{CITY_LA, CITY_IR, CITY_LA, CITY_SD, CITY_SD,
                                CITY_SD, CITY_IR, CITY_LA, CITY_IR, CITY_SD}, // inventory
                 vector<string>{CITY_SD, CITY_SD, CITY_SD, CITY_SD, CITY_IR,
                                CITY_IR, CITY_IR, CITY_LA, CITY_LA, CITY_LA}); // expected sorted inventory
}

int main()
{
    test_oneEleArr();
    cout << endl;
    test_twoEleArr();
    cout << endl;
    test_multipleEleArr();
}
