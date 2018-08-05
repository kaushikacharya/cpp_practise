// https://www.hackerrank.com/challenges/short-palindrome/problem
// July 19, 2018

#include <bits/stdc++.h>

using namespace std;

int compute_tuple_count_for_character_pair(vector<int> vec_outer_char_positions, vector<int> vec_inner_char_positions, int module_div, bool verbose=false)
{
    int palindrome_tuple_char_pair_count = 0;

    // Notation: For the tuple positions abcd, inner chars are the one at positions b and c; outer chars are at positions a and d
    // Algorithm:
    //  We compute the count in 4 steps:
    //          1st step: count for last character position in the tuple
    //          2nd step: count for last 2 character positions in the tuple
    //          3rd step: count for last 3 character positions in the tuple
    //          4th step: count for entire 4 character positions in the tuple

    //      For this we populate outer_vec in 1st and 4th step
    //              and inner_vec in 2nd and 3rd step

    // Here we handled both cases: a) inner and outer char different b) both same
    // Alternate solution could have been where we write separate functions for both cases.
    vector<int> outer_vec(vec_outer_char_positions.size(), 1);
    vector<int> inner_vec(vec_inner_char_positions.size(), 0);

    if (verbose)
    {
        cout << "count as last character of tuple: ";
        for (vector<int>::iterator it = outer_vec.begin(); it != outer_vec.end(); ++it)
        {
            cout << " " << *it;
        }
        cout << endl;
    }

    // Compute the count of last two characters of palindrome at each position of inner_vec
    // e.g. string s="ghghgg" and palindrome target: ghhg
    // h as position 3 in s can form last two characters of palindrome i.e. hg in 2 ways.
    int outer_i = vec_outer_char_positions.size()-1;
    int inner_i = vec_inner_char_positions.size()-1;

    int cur_count = 0;
    bool flag_tuple_feasible = false;
    // We will iterate backwards and assign/update inner_vec so that finally inner_vec will have the count of possible last characters of palindrome modulo module_div
    // Hence iterate till inner_vec is assigned
    while (inner_i >= 0)
    {
        if (outer_i < 0)
        {
            // No more instances of outer char left. For the rest of the inner char assign cur_count
            inner_vec[inner_i] = cur_count;
            --inner_i;
        }
        else if (vec_outer_char_positions[outer_i] < vec_inner_char_positions[inner_i])
        {
            // No more outer char is available on the right of current inner char
            // This ensures that multiple inner chars without any outer char in between them get the same value
            // e.g. ghhghgg: Here inner_vec[1], inner_vec[2] get the same value
            inner_vec[inner_i] = cur_count;
            --inner_i;
        }
        else if (vec_inner_char_positions[inner_i] < vec_outer_char_positions[outer_i])
        {
            flag_tuple_feasible = true;
            cur_count = (cur_count + outer_vec[outer_i]) % module_div;
            inner_vec[inner_i] = cur_count;
            --outer_i;
        }
        else
        {
            // case: Both inner and outer chars are same
            --inner_i;
        }
    }

    if (verbose)
    {
        cout << "count as last 2 characters of tuple: ";
        for (vector<int>::iterator it = inner_vec.begin(); it != inner_vec.end(); ++it)
        {
            cout << " " << *it;
        }
        cout << endl;
    }

    if (!flag_tuple_feasible)
    {
        return palindrome_tuple_char_pair_count;
    }

    // Now compute for the last three characters of the palindrome
    cur_count = 0;
    inner_i = vec_inner_char_positions.size()-1;

    while (inner_i >= 0)
    {
        int old_val = inner_vec[inner_i];
        inner_vec[inner_i] = cur_count;
        cur_count = (cur_count + old_val) % module_div;
        --inner_i;
    }

    if (verbose)
    {
        cout << "count as last 3 characters of tuple: ";
        for (vector<int>::iterator it = inner_vec.begin(); it != inner_vec.end(); ++it)
        {
            cout << " " << *it;
        }
        cout << endl;
    }

    // Now compute for the entire palindrome i.e. four character tuple
    cur_count = 0;
    // initialize outer_vec to zeros
    for (vector<int>::iterator it=outer_vec.begin(); it != outer_vec.end(); ++it)
    {
        *it = 0;
    }
    inner_i = vec_inner_char_positions.size()-1;
    outer_i = vec_outer_char_positions.size()-1;
    // Iterate till outer_vec gets assigned for this level
    while (outer_i >= 0)
    {
        if (inner_i < 0)
        {
            // No more instances of inner char left. For the rest of the outer char assign cur_count
            outer_vec[outer_i] = cur_count;
            --outer_i;
        }
        else if (vec_inner_char_positions[inner_i] < vec_outer_char_positions[outer_i])
        {
            outer_vec[outer_i] = cur_count;
            --outer_i;
        }
        else if (vec_outer_char_positions[outer_i] < vec_inner_char_positions[inner_i])
        {
            cur_count = (cur_count + inner_vec[inner_i]) % module_div;
            outer_vec[outer_i] = cur_count;
            --inner_i;
        }
        else
        {
            // case: Both inner and outer chars are same
            --outer_i;
        }
    }

    if (verbose)
    {
        cout << "count as last 4 characters i.e. entire of tuple: ";
        for (vector<int>::iterator it = outer_vec.begin(); it != outer_vec.end(); ++it)
        {
            cout << " " << *it;
        }
        cout << endl;
    }

    // Now sum up all the possible palindrome 4 tuples starting from each position of outer_vec
    for (vector<int>::iterator it = outer_vec.begin(); it != outer_vec.end(); ++it)
    {
        palindrome_tuple_char_pair_count = (palindrome_tuple_char_pair_count + *it) % module_div;
    }

    return palindrome_tuple_char_pair_count;
}

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
    bool verbose = false;
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
    // Iterate over each pair of characters in the string. Here pair is in terms of the distinct characters present in the string
    for (unordered_map<char, vector<int>>::iterator outIt = char_positions_map.begin(); outIt != char_positions_map.end(); ++outIt)
    {
        char outer_char = (*outIt).first;
        vector<int> vec_outer_char_positions = (*outIt).second;

        if (vec_outer_char_positions.size() < 2)
        {
            // Not possible to generate tuple due to lack of instances
            continue;
        }

        for (unordered_map<char, vector<int>>::iterator inIt = char_positions_map.begin(); inIt != char_positions_map.end(); ++inIt)
        {
            char inner_char = (*inIt).first;
            vector<int> vec_inner_char_positions = (*inIt).second;

            if (inner_char == outer_char)
            {
                if (vec_outer_char_positions.size() < 4)
                {
                   // Not possible to generate tuple due to lack of instances
                    continue;
                }
            }
            else if (vec_inner_char_positions.size() < 2)
            {
                // Not possible to generate tuple due to lack of instances
                continue;
            }

            int palindrome_tuple_char_pair_count = compute_tuple_count_for_character_pair(vec_outer_char_positions, vec_inner_char_positions, module_div, verbose);
            if (verbose)
            {
                cout << "outer char: " << outer_char << " : inner char: " << inner_char << " :: tuple pair count: " << palindrome_tuple_char_pair_count << "\n" << endl;
            }

            palindrome_tuple_count = (palindrome_tuple_count + palindrome_tuple_char_pair_count) % module_div;
        }
    }

    // -------- 2nd approach: This resulted in Time out error for few test cases ----------
    if (false)
    {
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
    }

    // --------- 1st approach: This gave "Abort Called" error -----------
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

3rd submission:
    Used dynamic programming. Took hint from eric2013(Eric Welch) in discussion thread.
    Time complexity: O(n)
    Space complexity: O(n)

2nd submission:
    status: Timeout
    Time complexity: O(n^2)
    Space complexity: O(n)

1st submission:
    status: "Abort Called"
    Time complexity: O(n^2)
    Space complexity: O(n^2)
*/
