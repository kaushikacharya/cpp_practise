// http://poj.org/problem?id=2136
// http://www.daniweb.com/software-development/c/threads/73035/how-do-you-loop-fscanf-until-eof-in-c
// http://poj.org/userstatus?user_id=warusher
// http://poj.org/userstatus?user_id=Adeline
// http://poj.org/showmessage?message_id=156792

#include <cstdio>
#include <functional> // std::less
#include <map>
#include <vector>
#include <cctype> // isupper

#define READ_FROM_FILE 0
#define WRITE_INTO_FILE 0

class CapsChar
{
public:
    CapsChar(unsigned int nLine);
    ~CapsChar();
public:
    void readInput(FILE* pFile);
    void plot_histogram();
private:
	void initMap();
    void readLine(FILE* pFile);
    unsigned int nLine();
    void updateMap(char ch);
private:
    unsigned int nLine_;
    std::map<char,unsigned int> charMap_;
};

CapsChar::CapsChar(unsigned int nLine)
: nLine_(nLine)
{
	initMap();
}

CapsChar::~CapsChar()
{
}

void CapsChar::initMap()
{
	char ch = 'A';

	while (ch <= 'Z')
	{
		charMap_[ch] = 0;
		++ch;
	}
}

void CapsChar::readInput(FILE* pFile)
{
    unsigned int line_i = 0;
    unsigned int n_Line = (*this).nLine();

    while (line_i < n_Line)
    {
        readLine(pFile);
        ++line_i;
    }
}

void CapsChar::readLine(FILE* pFile)
{
    char ch;

    if (READ_FROM_FILE)
    {
        while( (fscanf(pFile,"%c",&ch) != EOF) && (ch != '\n') )
        {
            if (isupper(ch))
            {
                updateMap(ch);
            }
        }
    }
    else
    {
        while((scanf("%c",&ch) != EOF) && (ch != '\n'))
        {
            if (isupper(ch))
            {
                updateMap(ch);
            }
        }
    }
}

void CapsChar::plot_histogram()
{
    if (charMap_.empty())
    {
        return;
    }

    // first get the max frequency
    std::map<char,unsigned int>::iterator it = charMap_.begin();
    unsigned int max_frequency = (*it).second;

    while (it != charMap_.end())
    {
        if (max_frequency < (*it).second)
        {
            max_frequency = (*it).second;
        }
        ++it;
    }

    std::map<char,unsigned int>::iterator chIt;
    std::map<char,unsigned int>::reverse_iterator chRevIt;

    if (WRITE_INTO_FILE)
    {
        FILE* pFile = fopen("D:/cpp_practise/online_judge/poj/2136_output.txt","w");
        for (int freq = max_frequency; freq > 0; --freq)
        {
            chIt = charMap_.begin();
            unsigned int charFreq = (*chIt).second;

            // First get the last character which will get '*' in this row i.e. in this frequency.
            // Beyond that char, we won't even print space char
            for (chRevIt = charMap_.rbegin(); chRevIt != charMap_.rend(); ++chRevIt)
            {
                if (freq <= (*chRevIt).second)
                {
                    break;
                }
            }
            unsigned int maxCount = charMap_.size() - std::distance(charMap_.rbegin(),chRevIt);
            unsigned int countFreq = 0;

            for (chIt = charMap_.begin(); (chIt != charMap_.end()) & (countFreq != maxCount); ++chIt)
            {
                if (chIt != charMap_.begin())
                {
                    fprintf(pFile," "); // space with column of prev char
                }

                unsigned int charFreq = (*chIt).second;

                if (charFreq < freq)
                {
                    fprintf(pFile," ");
                } 
                else
                {
                    fprintf(pFile,"*");
                }
                
                ++countFreq;
            }
            fprintf(pFile,"\n");
        }

        for (chIt = charMap_.begin(); chIt != charMap_.end(); ++chIt)
        {
            if (chIt != charMap_.begin())
            {
                fprintf(pFile," "); // space with column of prev char
            }
            fprintf(pFile,"%c",(*chIt).first);
        }
        fprintf(pFile,"\n");
    }
    else
    {
        for (int freq = max_frequency; freq > 0; --freq)
        {
            chIt = charMap_.begin();
            unsigned int charFreq = (*chIt).second;

            // First get the last character which will get '*' in this row i.e. in this frequency.
            // Beyond that char, we won't even print space char
            for (chRevIt = charMap_.rbegin(); chRevIt != charMap_.rend(); ++chRevIt)
            {
                if (freq <= (*chRevIt).second)
                {
                    break;
                }
            }
            unsigned int maxCount = charMap_.size() - std::distance(charMap_.rbegin(),chRevIt);
            unsigned int countFreq = 0;

            for (chIt = charMap_.begin(); (chIt != charMap_.end()) & (countFreq != maxCount); ++chIt)
            {
                if (chIt != charMap_.begin())
                {
                    printf(" "); // space with column of prev char
                }

                unsigned int charFreq = (*chIt).second;

                if (charFreq < freq)
                {
                    printf(" ");
                } 
                else
                {
                    printf("*");
                }

                ++countFreq;
            }
            printf("\n");
        }

        for (chIt = charMap_.begin(); chIt != charMap_.end(); ++chIt)
        {
            if (chIt != charMap_.begin())
            {
                printf(" "); // space with column of prev char
            }
            printf("%c",(*chIt).first);
        }
        printf("\n");
    }
    
}

unsigned int CapsChar::nLine()
{
    return nLine_;
}

void CapsChar::updateMap(char ch)
{
    std::map<char,unsigned int>::iterator it = charMap_.find(ch);
    if (it == charMap_.end())
    {
        charMap_[ch] = 1;
    }
    else
    {
        ++(*it).second;
    }
}

int main(int argc, char* argv[])
{
    FILE* pFile;

    if (READ_FROM_FILE)
    {
        pFile = fopen("D:/cpp_practise/online_judge/poj/2136_vertical_histogram.txt","r");
    }
    else
    {
        pFile = 0;
    }

    CapsChar caps_char(4);
    caps_char.readInput(pFile);
    caps_char.plot_histogram();

    return 0;
}
