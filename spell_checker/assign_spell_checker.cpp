#include "Dictionary.hpp"
#include "SpellChecker.hpp"
#include <iostream>

//assignment: http://users.cis.fiu.edu/~weiss/cop3337_f99/assignments/assign8.html
int main(int argc, char* argv[])
{
	//http://www.cprogramming.com/tutorial/functors-function-objects-in-c++.html
	ds::Dictionary dict("D:\\C++ programming\\Mark Allen Weiss\\COP-3337\\dict.txt");
	dict();
	std::size_t words_n = dict.size();

	ds::SpellChecker spellCheck("D:\\C++ programming\\Mark Allen Weiss\\COP-3337\\ch3.txt", dict);
	spellCheck();

	return 0;
}