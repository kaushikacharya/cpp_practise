/**
* Problem: Unobstructed Buildings
* URL: https://binarysearch.com/problems/Unobstructed-Buildings
* Date: Jan 03, 2021
*
*/

#include <unobstructed_buildings.hpp>

vector<int> solve(vector<int>& heights) {
    vector<int> unobstructedIndexVec;
    // reserve capacity
    unobstructedIndexVec.reserve(heights.size());

    // iterate from back and keep value of max height building till now
    int max_height = INT_MIN;
    unsigned int unobstructedCount = 0;

    for (int i=heights.size()-1; i >= 0; --i){
        if (heights[i] > max_height){
           unobstructedIndexVec.push_back(i);
           max_height = heights[i];
           ++unobstructedCount;
        }
    }

    reverse(unobstructedIndexVec.begin(), unobstructedIndexVec.end());
    // Keep only the first unobstructedCount elements
    unobstructedIndexVec.resize(unobstructedCount);

    return unobstructedIndexVec;
}

