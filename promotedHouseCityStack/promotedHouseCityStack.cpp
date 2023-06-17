/** Single Programmer Affidavit

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.

Name: Sukruti Mallesh
Red ID: 828540265
*/

#include "promotedHouseCityStack.h"
#include <stdexcept> // header for logic_error exception class

/**
   * @brief push operation, pushing the latest promoted city onto the stack
            Both time and auxiliary space complexity need to be O(1)
   * @param city
   * @param price
   */
void PromotedHouseCityStack::push(string city, int price) {

    // Create a PromotedCity object with the provided city and price
    PromotedCity promotedCity(city, price);

    // Add the PromotedCity object to the end of the promotedCities vector
    promotedCities.push_back(promotedCity);

    // If the priceRanges vector is empty, create a new PriceRange and add it to the vector
    if (priceRanges.empty()) {
        PriceRange range;
        range.highest = promotedCity;
        range.lowest = promotedCity;
        priceRanges.push_back(range);
    } else {
        // Get the current highest and lowest prices from the back of the vector PriceRange
        PriceRange currentRange = priceRanges.back();

        // Create a new PriceRange with the updated highest and lowest prices
        PriceRange newRange;
        newRange.highest = (promotedCity.getPromotedPrice() > currentRange.highest.getPromotedPrice()) ? promotedCity : currentRange.highest;
        newRange.lowest = (promotedCity.getPromotedPrice() < currentRange.lowest.getPromotedPrice()) ? promotedCity : currentRange.lowest;

        // Push/Add the new PriceRange into the priceRanges vector from the back
        priceRanges.push_back(newRange);
    }
}


/**
   * @brief pop operation, popping the latest promoted city off the stack
            Both time and auxiliary space complexity need to be O(1)
   * @param
   * @return The topmost PromotedCity object that was removed from the stack
   * @throws logic_error If either the promotedCities vector or the priceRanges vector is empty
   */
PromotedCity PromotedHouseCityStack::pop() {

    // If either the promotedCities vector or the priceRanges vector is empty, indicating that there are no promoted cities
    // in the stack, a logic_error is thrown, and as a result, there is no PromotedCity object to remove and return.
    if (promotedCities.empty() || priceRanges.empty()) {
        throw logic_error("Promoted house city stack is empty");
    }

    // Get the last promoted city from the back of promotedCities vector
    PromotedCity promotedCity = promotedCities.back();

    // Remove the last PromotedCity object from the vector
    promotedCities.pop_back();

    // Remove the corresponding PriceRange from the priceRanges vector
    priceRanges.pop_back();

    // Return the removed PromotedCity object
    return promotedCity;

}

/**
   * @brief peek operation, peeking the latest promoted city at the top
            of the stack (without popping)
            Both time and auxiliary space complexity need to be O(1)
   * @param
   * @return The topmost PromotedCity object
   * @throws logic_error If either the promotedCities vector or the priceRanges vector is empty
   */
PromotedCity PromotedHouseCityStack::peek() {

    // If either the promotedCities vector or the priceRanges vector is empty, indicating that there are no promoted cities
    // in the stack, a logic_error is thrown, and as a result, there is no PromotedCity object to return.
    if (promotedCities.empty() || priceRanges.empty()) {
        throw logic_error("Promoted house city stack is empty");
    }

    // Return the last PromotedCity object in the vector without removing it
    return promotedCities.back();

}

/**
   * @brief getHighestPricedPromotedCity,
   *        getting the highest priced house city among the past promoted citys
            Both time and auxiliary space complexity need to be O(1)
   * @param
   * @return The PromotedCity object with the highest price
   * @throws logic_error If either the promotedCities vector or the priceRanges vector is empty
   */
PromotedCity PromotedHouseCityStack::getHighestPricedPromotedCity() {

    // If either the promotedCities vector or the priceRanges vector is empty, indicating that there are no promoted cities
    // in the stack, a logic_error is thrown, and as a result, there is no PromotedCity object with the highest price to return.
    if (promotedCities.empty() || priceRanges.empty()) {
        throw logic_error("Promoted house city stack is empty");
    }

    // Return the PromotedCity object with the highest price from the last PriceRange in the vector
    return priceRanges.back().highest;

}

/**
   * @brief getLowestPricedPromotedCity,
   *        getting the lowest priced house city among the past promoted citys
            Both time and auxiliary space complexity need to be O(1)
   * @param
   * @return The PromotedCity object with the lowest price
   * @throws logic_error If either the promotedCities vector or the priceRanges vector is empty
   */
PromotedCity PromotedHouseCityStack::getLowestPricedPromotedCity() {

    // If either the promotedCities vector or the priceRanges vector is empty, indicating that there are no promoted cities
    // in the stack, a logic_error is thrown, and as a result, there is no PromotedCity object with the lowest price to return.
    if (promotedCities.empty() || priceRanges.empty()) {
        throw logic_error("Promoted house city stack is empty");
    }

    // Return the PromotedCity object with the lowest price from the last PriceRange in the vector
    return priceRanges.back().lowest;

}