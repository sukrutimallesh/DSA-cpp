#ifndef PROMOTEDHOUSECITYSTACK_H
#define PROMOTEDHOUSECITYSTACK_H

#include <ctype.h>  // character manipualtion, e.g. tolower()
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class PromotedCity {

private:
    string city;
    int promotedPrice;

public:
    PromotedCity() {
        this -> city = "";
        this -> promotedPrice = -1;
    }

    PromotedCity(string c, int p) {
        this -> city = c;
        this -> promotedPrice = p;
    }

    inline string getCity() {
        return city;
    }

    inline int getPromotedPrice() {
        return promotedPrice;
    }
};

/**
 * @brief Structure to hold the highest and lowest promoted cities together.
 *
 * The PriceRange structure represents a range of prices for promoted cities. It consists of two PromotedCity objects:
 *   - 'highest': The PromotedCity object with the highest price in the range.
 *   - 'lowest': The PromotedCity object with the lowest price in the range.
 *
 * By using this structure, we can store and track the highest and lowest promoted cities within a specific price range.
 * This allows for efficient retrieval of the highest and lowest priced cities from the overall collection of promoted cities.
 */

struct PriceRange {
    PromotedCity highest; // The PromotedCity object with the highest price in the range
    PromotedCity lowest; // The PromotedCity object with the lowest price in the range
};

class PromotedHouseCityStack {

private:
    vector<PromotedCity> promotedCities;  // To store the promoted cities object containing both city and price
    vector<PriceRange> priceRanges;       // To store and track the highest and lowest priced cities over time

public:
    /**
     * @brief push operation, pushing the latest promoted city onto the stack
              Both time and auxiliary space complexity need to be O(1)
     * @param city
     * @param price
     */
    void push(string city, int price);

    /**
     * @brief pop operation, popping the latest promoted city off the stack
              Both time and auxiliary space complexity need to be O(1)
     * @param
     * @return PromotedCity
     *         should throw a logic_error exception with an error message
     *         “Promoted city stack is empty” if the PromotedHouseCityStack is empty
     */
    PromotedCity pop();

    /**
     * @brief peek operation, peeking the latest promoted city at the top of the stack (without popping)
              Both time and auxiliary space complexity need to be O(1)
     * @param
     * @return PromotedCity
     *         should throw a logic_error exception with an error message
     *         “Promoted city stack is empty” if the PromotedHouseCityStack is empty
     */
    PromotedCity peek();

    /**
     * @brief getHighestPricedPromotedCity,
     *        getting the highest priced city among the past promoted citys
              Both time and auxiliary space complexity need to be O(1)
     * @param
     * @return PromotedCity
     *         should throw a logic_error exception with an error message
     *         “Promoted city stack is empty” if the PromotedHouseCityStack is empty
     */
    PromotedCity getHighestPricedPromotedCity();

    /**
     * @brief getLowestPricedPromotedCity,
     *        getting the lowest priced city among the past promoted citys
              Both time and auxiliary space complexity need to be O(1)
     * @param
     * @return PromotedCity
     *         should throw a logic_error exception with an error message
     *         “Promoted city stack is empty” if the PromotedHouseCityStack is empty
     */
    PromotedCity getLowestPricedPromotedCity();

};

#endif