#ifndef SORTHOUSE_H
#define SORTHOUSE_H

#include <vector>
#include <string>

using namespace std;

class SortHouseCity
{

public:
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
    static vector<string> sortHouseInventory(vector<string> houseCities,
                                             vector<string> promotionOrder);
};

#endif