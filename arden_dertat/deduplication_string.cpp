#include <bitset>
#include <cctype>
#include <string>
#include <iostream>
//problem statement: http://www.ardendertat.com/2012/01/06/programming-interview-questions-25-remove-duplicate-characters-in-string/

//assumption: we are considering case-insensitive
void de_duplication(const std::string& inputStr, std::string& outputStr);

int main( int argc, char* argv[] )
{
    std::size_t test_case = 0;
    std::string inputStr;
    std::string outputStr;

    switch (test_case)
    {
    case 0:
        inputStr = "tree traversal";
        break;
    }

    de_duplication(inputStr,outputStr);
    std::cout << "deduplicated string: " << outputStr << std::endl;
    
    return 0;
}

void de_duplication(const std::string& inputStr, std::string& outputStr)
{
    std::bitset<26> bSet;
#if 0
    //This shows that iterator of string goes till before the null character 
    std::string::const_iterator it = inputStr.end()-1;
    char ch = *it;
#endif

     for (std::string::const_iterator it = inputStr.begin(); it != inputStr.end(); ++it)
     {
         char ch = *it;
 
         if (std::isalpha(ch))
         {
             std::size_t pos;
             if ( std::islower(ch) )
             {
                 pos = ch - 'a';
             }
             else
             {
                 pos = ch - 'A';
             }

             if (!bSet[pos])
             {
                 outputStr.push_back(ch);
                 bSet[pos] = true;
             }
         }
         else
         {
             outputStr.push_back(ch);
         }
     }
}

/** Learnings:
Note: understand the difference in approach for ASCII vs Unicode

http://stackoverflow.com/questions/1463284/hashset-vs-treeset
*/