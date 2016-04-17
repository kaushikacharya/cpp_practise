#include "Dictionary.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>

namespace ds
{
	Dictionary::Dictionary(const char* dictFile)
		: dictFile_(dictFile)
	{
	}

	void Dictionary::operator ()()
	{
		std::ifstream dictFileStream;

		dictFileStream.open(dictFile_);
		assert(dictFileStream.is_open() && "invalid input dictionary file");

		while(!dictFileStream.eof())
		{
			std::string line;
			std::getline(dictFileStream,line);
			convertToLowerCase(line);
			dictWords_.insert(line);
		}

		dictFileStream.close();
	}

	void Dictionary::convertToLowerCase(std::string& str)
	{
		std::transform(str.begin(),str.end(),str.begin(),tolower);
	}

	std::size_t Dictionary::size()
	{
		return dictWords_.size();
	}

	const std::set<std::string>& Dictionary::dictWords() const
	{
		return dictWords_;
	}
}