/**
 * Driver file for CS 210 Program 2
 * @author
 * @date Jun 2023
 *
 * Runs the student code and provides 1 test case.
 * This case may not test everything and it is
 * always recommended that you implement your own
 * tests.
 * Driver files will not necessarily be
 * provided for all projects.
 */


#include <stdlib.h>
#include <iostream>

#include "promotedHouseCityStack.h"

#define CITY_SD "SD"
#define CITY_LA "LA"
#define CITY_IR "IR"
#define CITY_SJ "SJ"
#define CITY_SF "SF"
#define CITY_SB "SB"

using namespace std;

bool equalsIgnoreCase(const string& a, const string& b) {
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

void testHighestLowestPeek(string highestPricedHouseCity,
                           int highestPrice,
                           string lowestPricedHouseCity,
                           int lowestPrice,
                           string peekCity,
                           int peekCityPrice,
                           PromotedHouseCityStack stack) {

    if (equalsIgnoreCase(stack.getHighestPricedPromotedCity().getCity(), highestPricedHouseCity)) {
        cout << "Stack highest priced model matches" << endl;
    } else {
        cout << "FAILED: Stack highest priced model does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (stack.getHighestPricedPromotedCity().getPromotedPrice() == highestPrice) {
        cout << "Stack highest priced model's price matches" << endl;
    } else {
        cout << "FAILED: Stack highest priced model's price does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (equalsIgnoreCase(stack.getLowestPricedPromotedCity().getCity(), lowestPricedHouseCity)) {
        cout << "Stack lowest priced model matches" << endl;
    } else {
        cout << "FAILED: Stack lowest priced model does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (stack.getLowestPricedPromotedCity().getPromotedPrice() == lowestPrice) {
        cout << "Stack lowest priced model's price matches" << endl;
    } else {
        cout << "FAILED: Stack lowest priced model's price does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (equalsIgnoreCase(stack.peek().getCity(), peekCity)) {
        cout << "Stack peek matches" << endl;
    } else {
        cout << "FAILED: Stack peek does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (stack.peek().getPromotedPrice() == peekCityPrice) {
        cout << "Stack peek price matches" << endl;
    } else {
        cout << "FAILED: Stack peek price does NOT match" << endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {

    PromotedHouseCityStack stack;

    cout << "Pushing " << CITY_IR << " at 35,000" << endl;
    stack.push(CITY_IR, 35000);
    testHighestLowestPeek(CITY_IR, 35000,
                          CITY_IR, 35000,
                          CITY_IR, 35000, stack);

    cout << endl << "Pushing " << CITY_LA << " at 64,000" << endl;
    stack.push(CITY_LA, 64000);
    testHighestLowestPeek(CITY_LA, 64000,
                          CITY_IR, 35000,
                          CITY_LA, 64000, stack);

    cout << endl << "Pushing " << CITY_SD << " at 38,000" << endl;
    stack.push(CITY_SD, 38000);
    testHighestLowestPeek(CITY_LA, 64000,
                          CITY_IR, 35000,
                          CITY_SD, 38000, stack);

    cout << endl << "Popping from stack" << endl;
    PromotedCity popped = stack.pop();

    if (equalsIgnoreCase(popped.getCity(), CITY_SD)) {
        cout << "Popped city matches" << endl;
    } else {
        cout << "FAILED: Popped city does NOT match!" << endl;
        exit(EXIT_FAILURE);
    }

    if (popped.getPromotedPrice() == 38000) {
        cout << "Popped price matches" << endl;
    } else {
        cout << "Popped price does NOT match" << endl;
        exit(EXIT_FAILURE);
    }

    testHighestLowestPeek(CITY_LA, 64000,
                          CITY_IR, 35000,
                          CITY_LA, 64000, stack);

    cout << endl << "SUCCESS! All tests passed!" << endl;

    exit(EXIT_SUCCESS);
}
