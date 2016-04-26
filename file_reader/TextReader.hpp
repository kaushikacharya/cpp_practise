#ifndef TextReader_HPP
#define TextReader_HPP

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace ds
{
    class TextReader
    {
    public:
        TextReader(const char* textFile);
        void operator()();
    public:
        std::vector<std::string>& strVec();
        static void tokenize(std::string& line,std::vector<std::string>& lineSplit);
    private:
        const char* textFile_;
        std::vector<std::string> strVec_;
    };

}

#endif