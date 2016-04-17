#include "SpellChecker.hpp"
#include "Stem.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
 
namespace ds
{
	SpellChecker::SpellChecker(const char* textFile, const Dictionary& dict)
		: textFile_(textFile)
		, dict_(dict)
	{
	}

	void SpellChecker::operator()()
	{
		using namespace std;

		std::ifstream textFileStream;
		textFileStream.open(textFile_);
		assert(textFileStream.is_open() && "invalid input text file");

		std::size_t countLine = 0;
		while(!textFileStream.eof())
		{
			++countLine;
			std::string line;
			std::getline(textFileStream,line);
			
			vector<string>lineSplit;
			tokenize(line, lineSplit);

			for (vector<string>::iterator sIt = lineSplit.begin(); sIt != lineSplit.end(); ++sIt)
			{
				string str = *sIt;
				removeExtraCharFromWord(str);
				Dictionary::convertToLowerCase(str);

				if (!isWordInDictionary(str))
				{
					strLineMap::iterator it = misSpeltWordsDetail_.find(str);

					if (it != misSpeltWordsDetail_.end())
					{
						std::vector<std::size_t>& lineVec = (*it).second;
						lineVec.push_back(countLine);
						//Alternate: we could store only unique line nos. In that case,
						//we just check last value of lineVec with countLine
					}
					else
					{
						//first instance of current mis-spelt word
						//TBD: modification to orginal assignment: check word stem
						Stem str_stem(str);
						str_stem();

						if (!isWordInDictionary(str_stem.stem()))
						{
							std::vector<std::size_t> lineVec;
							lineVec.push_back(countLine);
							misSpeltWordsDetail_.insert(std::make_pair(str,lineVec));
						}
					}
				}
			}

			int gh = 0;
		}

		textFileStream.close();

		//Now print info of mis-spelt words
		printMisSpeltWordWithLineNumbers();
	}

	void SpellChecker::tokenize(std::string& line,std::vector<std::string>& lineSplit)
	{
		if (line == "")
		{
			return;
		}
		std::string::size_type start = 0;
		std::string::size_type end = 0;
		while(end < line.npos)
		{
			start = line.find_first_not_of(' ',end);
			end   = line.find_first_of(' ',start);
			if (start == end)
			{
				break;
			}
			lineSplit.push_back(line.substr(start,(end-start)));
		}
	}

	void SpellChecker::removeExtraCharFromWord(std::string& str)
	{
		if ( (!isalpha(str[str.length()-1])) && 
			( (str[str.length()-1] == '.') ||
			(str[str.length()-1] == ',') || (str[str.length()-1] == '?') ||
			(str[str.length()-1] == ':') || (str[str.length()-1] == ';') )  )
		{
			str = str.substr(0,str.length()-1);
		}
	}

	bool SpellChecker::isWordInDictionary(std::string& str)
	{
		const std::set<std::string>& dictWords = dict_.dictWords();
		return dictWords.find(str) != dictWords.end();
	}

	void SpellChecker::printMisSpeltWordWithLineNumbers()
	{
		for (strLineMap::iterator it = misSpeltWordsDetail_.begin(); it != misSpeltWordsDetail_.end(); ++it)
		{
			std::string str = (*it).first;
			std::vector<std::size_t> lineVec = (*it).second;

			std::cout << str << " : ";
			for (std::vector<std::size_t>::iterator lineIt = lineVec.begin(); lineIt != lineVec.end(); ++lineIt)
			{
				std::cout << (*lineIt) << " ";
			}
			std::cout << std::endl;

		}
	}
}