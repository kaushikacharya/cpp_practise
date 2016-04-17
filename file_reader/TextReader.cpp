#include "TextReader.hpp"

namespace ds
{
    TextReader::TextReader(const char* textFile)
        : textFile_(textFile)
    {
    }

    void TextReader::operator()()
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

            vector<string> lineSplit;
            tokenize(line,lineSplit);

            //TBD: use memory allotment for strVec_

            for (vector<string>::iterator sIt = lineSplit.begin(); sIt != lineSplit.end(); ++sIt)
            {
                string str = *sIt;
                strVec_.push_back(str);
            }
        }

		textFileStream.close();
    }

    void TextReader::tokenize(std::string& line,std::vector<std::string>& lineSplit)
    {
		// check: isspace http://www.cs.swarthmore.edu/~newhall/unixhelp/C_chars.html
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


    std::vector<std::string>& TextReader::strVec()
    {
        return strVec_;
    }
}