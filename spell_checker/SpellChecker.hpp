#ifndef Spell_Checker_HPP
#define Spell_Checker_HPP

#include "Dictionary.hpp"
#include <fstream>
#include <map>
#include <string>
#include <vector>

namespace ds
{
	class SpellChecker
	{
	public:
		SpellChecker(const char* textFile, const Dictionary& dict);
		void operator()();
	private:
		void tokenize(std::string& line,std::vector<std::string>& lineSplit);
		void removeExtraCharFromWord(std::string& str);
		bool isWordInDictionary(std::string& str);
		void printMisSpeltWordWithLineNumbers();
	private:
		typedef std::map<std::string,std::vector<std::size_t> > strLineMap;
	private:
		const char* textFile_;
		const Dictionary& dict_;
		strLineMap misSpeltWordsDetail_;
	};
}

#endif