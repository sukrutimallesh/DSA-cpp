#include "sorthousecity.h"

/**
 * @brief sort house inventory
 *
 * @param houseCities       input house city array
 * @param promotionOrder    city promotion order
 * @return vector<string>   sorted house city array according to the city promotion order
 *
 * Time complexity has to be linear:
 *    O(N), N is the size/length of the input house city array
 * Auxiliary space complexity has to be constant: O(1)
 *    hint: sorting can be done by mutating the input house city array.
 */

vector<string> SortHouseCity::sortHouseInventory(vector<string> houseCities,
                                                 vector<string> promotionOrder)
{
    // Constants to represent the indices of the promotion order
    const int FIRST_PROMOTION_INDEX = 0; // Index of the first promotion order
    const int SECOND_PROMOTION_INDEX = 1; // Index of the second promotion order

    // Declare and initialize the index variable to keep track of the current position for the cities matching the promotion order
    int index = 0;

    // Variable to store the length of the houseCities vector
    int houseCitiesSize = houseCities.size();

    // First pass: Move cities matching the first promotion order to the front
    for (int i = 0; i < houseCitiesSize; i++)
    {
        // Check if the current city matches the first promotion order
        if (promotionOrder[FIRST_PROMOTION_INDEX] == houseCities[i])
        {
            // Swap the current city with the city at the current index
            string temp = houseCities[index];
            houseCities[index] = houseCities[i];
            houseCities[i] = temp;

            // Increment the index to move to the next position for the next city
            index++;
        }
    }

    // Second pass: Move cities matching the second promotion order after the first set
    for (int i = 0; i < houseCitiesSize; i++)
    {
        // Check if the current city matches the second promotion order
        if (promotionOrder[SECOND_PROMOTION_INDEX] == houseCities[i])
        {
            // Swap the current city with the city at the current index
            string temp = houseCities[index];
            houseCities[index] = houseCities[i];
            houseCities[i] = temp;

            // Increment the index to move to the next position for the next city
            index++;
        }
    }
    
    // Return the sorted houseCities array
    return houseCities;

}
