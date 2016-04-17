// http://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
// Mar 01, 2015

#include <iostream>
#include <map>
#include <string>

using namespace std;

// recursive
class Solution
{
public:
    void compute_permutation_from_string(string str)
    {
        map<char,unsigned int> map_char_count;
        for (int i = 0; i != str.size(); ++i)
        {
            char ch = str[i];
            map<char, unsigned int>::iterator it = map_char_count.find(ch);
            if (it == map_char_count.end())
            {
                map_char_count.insert(make_pair(ch,1));
            }
            else
            {
                ++(*it).second;
            }
        }

        compute_permutations("", map_char_count);
    }
private:
    void compute_permutations(string str, map<char,unsigned int> map_char_count)
    {
        // extend str
        if (map_char_count.empty())
        {
            cout << str << endl;
            return;
        }
        for (map<char,unsigned int>::iterator it = map_char_count.begin(); it != map_char_count.end(); ++it)
        {
            char ch = (*it).first;
            int count_ch = (*it).second;

            string str_updated = str + ch;

            map<char, unsigned int> map_char_count_updated = map_char_count;
            if (count_ch > 1)
            {
                --map_char_count_updated[ch];
            }
            else
            {
                map_char_count_updated.erase(ch);
            }
            compute_permutations(str_updated, map_char_count_updated);
        }
    }
};

int main(int argc, char* argv[])
{
    string str = "aabab";
    Solution sln;
    sln.compute_permutation_from_string(str);

    return 0;
}
