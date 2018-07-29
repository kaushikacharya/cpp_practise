// https://www.hackerrank.com/challenges/short-palindrome/problem
// July 19, 2018

#include <bits/stdc++.h>

using namespace std;

// Complete the shortPalindrome function below.
int shortPalindrome(string s) {
    // cout << "string length: " << s.size() << endl;
    if (s.size() < 4)
    {
        // string length too short to create palindromic tuple
        return 0;
    }

    // https://stackoverflow.com/questions/17122496/wrong-output-by-power-function-c (Mats Petersson's answer)
    // Without round its coming 1 less than expected in some compilers.
    int module_div = round(pow(10, 9)) + 7;
    // cout << "module_div: " << module_div << endl;

    // Populate map of character positions
    unordered_map<char, vector<int>> char_positions_map;
    for (unsigned int i=0; i < s.size(); ++i)
    {
        char ch = s[i];
        unordered_map<char, vector<int>>::iterator it = char_positions_map.find(ch);

        if (it == char_positions_map.end())
        {
            // first instance of the character in the string s
            vector<int> vec = {i};
            char_positions_map.insert(make_pair(ch, vec));
        }
        else
        {
            (*it).second.push_back(i);
        }
    }
    // cout << "char_positions_map.size(): " << char_positions_map.size() << endl;

    int palindrome_tuple_count = 0;
    // Iterate over each distinct character 'a','b',.....
    for (unordered_map<char, vector<int>>::iterator it = char_positions_map.begin(); it != char_positions_map.end(); ++it)
    {
        char current_char = (*it).first;
        vector<int> vec_char_positions = (*it).second;

        // In this iteration for character ch, we compute palindrome tuples where Sa = Sd = current_char
        if (vec_char_positions.size() < 2)
        {
            // at least two instance of char ch should be present to create the palindrome tuple
            continue;
        }

        // Create a vector where each element stores the char count map between consecutive positions of the character current_char in string s
        vector<unordered_map<char,int> > char_count_map_vec(vec_char_positions.size()-1);
        for (unsigned int i=0; i < (vec_char_positions.size()-1); ++i)
        {
            unordered_map<char,int> char_count_map;
            for (unsigned int j=(vec_char_positions[i]+1); j < vec_char_positions[i+1]; ++j)
            {
                char ch = s[j];
                unordered_map<char,int>::iterator it = char_count_map.find(ch);
                if (it == char_count_map.end())
                {
                    char_count_map.insert(make_pair(ch,1));
                }
                else
                {
                    ++((*it).second);
                }
            }
            char_count_map_vec[i] = char_count_map;
        }

        // Now use this stored char count map vector to compute palindrome tuples
        // In 1st iteration, we will compute Sa=1st instance of current_char with Sd as 2nd, 3rd and so on instances of current_char
        // In 2nd iteration, Sa=2nd instance of current char with Sd as 3rd, 4th and so on instance of current_char
        // And so on for rest of the iterations
        // Note: Here 1st, 2nd etc in comment is wrt 1-indexing

        unordered_map<char,int> char_count_map;
        for (unsigned int i=0; i < char_count_map_vec.size(); ++i)
        {
            for (unsigned int j=i; j<char_count_map_vec.size(); ++j)
            {
                if (j == i)
                {
                    char_count_map = char_count_map_vec[i];
                }
                else
                {
                    // Increment char_count_map with the characters in vec_char_positions[j]+1, ... vec_char_positions[j+1]-1
                    for (unordered_map<char,int>::iterator cit=char_count_map_vec[j].begin(); cit != char_count_map_vec[j].end(); ++cit)
                    {
                        char ch = (*cit).first;
                        unordered_map<char,int>::iterator ccit = char_count_map.find(ch);

                        if (ccit == char_count_map.end())
                        {
                            char_count_map.insert(make_pair(ch, (*cit).second));
                        }
                        else
                        {
                            (*ccit).second += (*cit).second;
                        }
                    }

                    // Since char_count_map_vec only includes the character count map between consecutive positions of current_char in string s,
                    // we need to also include current_char in vec_char_positions[j]
                    unordered_map<char,int>::iterator ccit = char_count_map.find(current_char);
                    if (ccit == char_count_map.end())
                    {
                        char_count_map.insert(make_pair(current_char, 1));
                    }
                    else
                    {
                        (*ccit).second += 1;
                    }
                }

                // compute tuple count with Sa=vec_char_positions[i], Sd=vec_char_positions[j+1] and all possible Sb,Sc in between
                long int count_internal_tuple_combination = 0;
                for (unordered_map<char,int>::iterator ccit = char_count_map.begin(); ccit != char_count_map.end(); ++ccit)
                {
                    // char ch = (*ccit).first;
                    long int char_count = (*ccit).second;
                    count_internal_tuple_combination += ((char_count-1)*char_count/2) % module_div;
                }
                palindrome_tuple_count = (palindrome_tuple_count + count_internal_tuple_combination) % module_div;
            }
        }
    }

    // --------- Older approach: This gave "Abort Called" error -----------
    if (false)
    {
       // Create the upper diagonal matrix of character count
        // matrix[i,j] - dict with characters as key and value as count of corresponding characters in s[i,...,j]
        vector<vector<unordered_map<char,int> > > char_count_matrix(s.size());
        // To save space, we are saving upper triangular potion of the matrix
        // That means char_count_matrix[i] starts with s[i]
        // In other words [i,j]'th element of complete matrix corresponds to [i,j-i]'th element of upper triangular portion of the matrix

        for (unsigned int i=0; i < s.size(); ++i)
        {
            vector<unordered_map<char,int> > char_count_vec;
            unordered_map<char,int> char_count_map;
            for (unsigned int j=i; j < s.size(); ++j)
            {
                char ch = s[j];
                unordered_map<char,int>::iterator it = char_count_map.find(ch);
                if (it == char_count_map.end())
                {
                    char_count_map.insert(make_pair(ch,1));
                }
                else
                {
                    ++((*it).second);
                }
                char_count_vec.push_back(char_count_map);
            }
            char_count_matrix[i] = char_count_vec;
        }
        // cout << "char_count_matrix.size(): " << char_count_matrix.size() << endl;
        // cout << "long int max: " << numeric_limits<long int>::max() << endl;

        // Now compute the count of palindromes satisfying the given condition
        int palindrome_tuple_count = 0;
        int module_div = round(pow(10, 9)) + 7;

        for (unordered_map<char, vector<int>>::iterator it = char_positions_map.begin(); it != char_positions_map.end(); ++it)
        {
            // char ch = (*it).first;
            vector<int> vec_char_positions = (*it).second;

            for (unsigned int i=0; i != (vec_char_positions.size()-1); ++i)
            {
                int pos_i = vec_char_positions[i];
                for (unsigned int j=(i+1); j != vec_char_positions.size(); ++j)
                {
                    int pos_j = vec_char_positions[j];
                    if ((pos_j - pos_i) < 3)
                    {
                        // palindrome tuple not possible
                        continue;
                    }
                    // Now count the number of combinations possible of the 2nd,3rd element pairs of palindrome tuple
                    // pos_j-1-(pos_i+1) is explained where char_count_matrix is defined.
                    unordered_map<char,int> char_count_map = char_count_matrix[pos_i+1][pos_j-1-(pos_i+1)];
                    long int count_internal_tuple_combination = 0;
                    for (unordered_map<char,int>::iterator ccit = char_count_map.begin(); ccit != char_count_map.end(); ++ccit)
                    {
                        // char ch = (*ccit).first;
                        long int char_count = (*ccit).second;
                        count_internal_tuple_combination += ((char_count-1)*char_count/2) % module_div;
                    }
                    palindrome_tuple_count = (palindrome_tuple_count + count_internal_tuple_combination) % module_div;
                }
            }
        }
    }


    return palindrome_tuple_count;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    int result = shortPalindrome(s);

    fout << result << "\n";
    // cout << result << "\n";

    fout.close();

    return 0;
}

/**
Status: Timeout for few test cases.
Time complexity: O(n^2)
Space complexity: O(n). Previous submission(inside False scope) was O(n^2). Probably that's why it was throwing "Abort Called" by online judge.
*/
