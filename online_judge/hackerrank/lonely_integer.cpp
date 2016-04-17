#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cassert>

#define MAX_NUM 100
using namespace std;

/* Head ends here */
int lonelyinteger(vector < int > arr)
{
	vector<int> vecCount;
	vecCount.reserve(MAX_NUM+1);
	for (unsigned int i=0; i != (MAX_NUM+1); ++i)
	{
		vecCount.push_back(0);
	}

	int min_elem = numeric_limits<int>::max();
	int max_elem = numeric_limits<int>::min();

	for (vector<int>::iterator it = arr.begin(); it != arr.end(); ++it)
	{
		int elem = (*it);
		++vecCount[elem];
		
		if (elem < min_elem)
		{
			min_elem = elem;
		}
		if (max_elem < elem)
		{
			max_elem = elem;
		}
	}

	int lonely_elem;
	for (lonely_elem = min_elem; lonely_elem != (max_elem+1); ++lonely_elem)
	{
		if (vecCount[lonely_elem] == 1)
		{
			break;
		}
	}
	assert((lonely_elem < (max_elem+1)) && "lonely integer not found");

	return lonely_elem;
}
/* Tail starts here */
int main() {
    int res;
    
    int _a_size;
    cin >> _a_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<int> _a;
    int _a_item;
    for(int _a_i=0; _a_i<_a_size; _a_i++) {
        cin >> _a_item;
        _a.push_back(_a_item);
    }
    
    res = lonelyinteger(_a);
    cout << res;
    
    return 0;
}