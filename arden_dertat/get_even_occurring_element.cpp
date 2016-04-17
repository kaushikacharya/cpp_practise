#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <cassert>
//problem statement: http://www.ardendertat.com/2011/11/29/programming-interview-questions-18-find-even-occurring-element/

int even_occurring_element_impl0(std::vector<int>& inputVec);
int even_occurring_element_impl1(std::vector<int>& inputVec);

int main(int argc, char* argv[])
{
	std::size_t test_case = 0;
	int output;

	switch (test_case)
	{
	case 0:
		int arr[] = {2,3,2,5,4,5,5};
		std::vector<int> inputVec(arr, arr + sizeof(arr)/sizeof(arr[0]) );
		//output = even_occurring_element_impl0(inputVec);
        output = even_occurring_element_impl1(inputVec);
		break;
	}

	std::cout << "even occurring element: " << output << std::endl;
	return 0;
}

// xor based implementation
int even_occurring_element_impl0(std::vector<int>& inputVec)
{
	std::set<int> mySet;
	int xor_inputVec = 0;
	int xor_set = 0;

	for (std::vector<int>::iterator it = inputVec.begin(); it != inputVec.end(); ++it)
	{
		mySet.insert(*it);
		xor_inputVec = xor_inputVec ^ (*it);
	}
	for (std::set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it)
	{
		xor_set = xor_set^(*it);
	}

	return xor_inputVec^xor_set;
}

/**
Hash Table based implementation
*/
int even_occurring_element_impl1(std::vector<int>& inputVec)
{
	typedef std::tr1::unordered_map<int,std::size_t> UnOrderedMap;
	UnOrderedMap myHashMap;

	for (std::vector<int>::iterator it = inputVec.begin(); it != inputVec.end(); ++it)
	{
		UnOrderedMap::iterator hashIt = myHashMap.find(*it);
		if (hashIt == myHashMap.end())
		{
			myHashMap.insert(std::make_pair<int,std::size_t>(*it,1));
		}
		else
		{
            //both of the lines are valid
			++hashIt->second;
			//myHashMap[*it] = myHashMap[*it] + 1;
		}
	}

    //Now find the element having even occurrence
    UnOrderedMap::iterator it;
    for(it = myHashMap.begin(); it != myHashMap.end(); ++it)
    {
        if (it->second % 2 == 0)
        {
            break;
        }
    }

    assert((it != myHashMap.end()) && "No even occuring element");
    return (*it).first;
}

/**
http://stackoverflow.com/questions/1646266/difference-between-hash-map-and-unordered-map
http://www.cplusplus.com/reference/unordered_map/unordered_map/
*/