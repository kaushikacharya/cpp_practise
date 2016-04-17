#include <iostream>
#include <vector>
#include <cctype>
//problem source: http://www.ardendertat.com/2011/11/17/programming-interview-questions-16-anagram-strings/
//http://www.cplusplus.com/reference/cctype/isalpha/

void countCharOccurenceFunc(std::string& str, std::vector<int>& countVec);

int main( int argc, char* argv[] )
{
	std::size_t test_case = 1;
	std::string str1,str2;
	std::vector<int> countVec1,countVec2;
	countVec1.assign(26,0);
	countVec2.assign(26,0);

	switch (test_case)
	{
	case 0:
		str1 = "Eleven plus two";
		str2 = "Twelve plus one";
		break;
    case 1:
        // non-Anagrams
        str1 = "Armand de Richelieu";
        str2 = "Ardue main d'Hercule";
        break;
	}

	countCharOccurenceFunc(str1, countVec1);
	countCharOccurenceFunc(str2, countVec2);

	bool flagAnagram(true);
	for (std::size_t i = 0; i < 26; ++i)
	{
		if (countVec1[i] != countVec2[i])
		{
			flagAnagram = false;
			break;
		}
	}

	std::cout << "anagram strings? " << flagAnagram << std::endl;

	return 0;
}

void countCharOccurenceFunc(std::string& str, std::vector<int>& countVec)
{
	for (std::size_t i = 0; i < str.size(); ++i)
	{
		if ( std::isalpha(str[i]) )
		{
			std::size_t pos;
			if ( std::islower(str[i]) )
			{
				pos = str[i] - 'a';
			}
			else
			{
				pos = str[i] - 'A';
			}
			++countVec[pos];
		}
	}
}