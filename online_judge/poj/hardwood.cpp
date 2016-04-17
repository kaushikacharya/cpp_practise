#include <map>
#include <utility>
#include <string>
#include <cstdio>
#include <cstring>

int main()
{
	typedef std::map<std::string, int> myMap;

	myMap mapTree;

	char ipStr[30];

	int cntTree = 0;

	//gets(ipStr);

	while (gets(ipStr) != NULL)//(strlen(ipStr) != 0) //ipStr[0] != '\0'
	{
		++cntTree;

#if 0
		if (mapTree.find(ipStr) == mapTree.end())
		{
			mapTree[ipStr] = 1;
		}
		else
		{
			++mapTree[ipStr];  
		}
#else
		myMap::iterator lb = mapTree.lower_bound(ipStr);

		if ((lb != mapTree.end()) && (!mapTree.key_comp()(ipStr,lb->first))) //check whether key is present
		{
			++lb->second;
		}
		else
		{
			mapTree.insert(lb, myMap::value_type(ipStr,1));
		}
#endif
		//gets(ipStr);
	}

	for (myMap::iterator mapIt =  mapTree.begin(); mapIt != mapTree.end(); ++mapIt)
	{
		printf("%s %f\n", (mapIt->first).c_str(), (double(mapIt->second)/cntTree)*100);
	} 
}
