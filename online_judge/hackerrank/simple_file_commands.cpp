// https://www.hackerrank.com/contests/world-codesprint-11/challenges/simple-file-commands
// Jan 24, 2018

#include <bits/stdc++.h>

using namespace std;

template<typename T>
class FileCommand
{
public:
    FileCommand(){}
public:
    void processCommand(string cmd)
    {
        // 1. split the command
        vector<string> vecToken = splitCommand(cmd);
        cout << "size(vecToken): " << vecToken.size() << endl;
        assert((vecToken.size() > 1) && "incomplete command");
        // 2. identify (a) command type (b) filename (c) file copy number (if not mentioned then its 0)
        // 3. Based on command type do process

        if (vecToken[0] == "crt")
        {
            string filename = vecToken[1];
            T copy_index = create_file(vecToken[1]);
            cout << "+ " << vecToken[1];
            if (copy_index > 0)
            {
                cout << "(" << copy_index << ")";
            }
            cout << endl;
        }
        else if(vecToken[0] == "del")
        {
            delete_file(vecToken[1]);
            cout << "- " << vecToken[1] << endl;
        }
        else if(vecToken[0] == "rnm")
        {
            delete_file(vecToken[1]);
            T copy_index = create_file(vecToken[2]);
            cout << "r " << vecToken[1] << " -> " << vecToken[2];
            if (copy_index > 0)
            {
                cout << "(" << copy_index << ")";
            }
            cout << endl;
        }
        else
        {
            assert(false && "incorrect command");
        }
    }

    void processCreate(string filename)
    {
        // cout << "entered processCreate with filename: " << filename << endl;
        T copy_index = create_file(filename);
        cout << "+ " << filename;
        if (copy_index > 0)
        {
            cout << "(" << copy_index << ")";
        }
        cout << endl;
    }

    void processDelete(string filename)
    {
        delete_file(filename);
        cout << "- " << filename << endl;
    }

    void processRename(string filename1, string filename2)
    {
        delete_file(filename1);
        T copy_index = create_file(filename2);
        cout << "r " << filename1 << " -> " << filename2;
        if (copy_index > 0)
        {
            cout << "(" << copy_index << ")";
        }
        cout << endl;
    }

    vector<string> splitCommand(string cmd)
    {
        string str = cmd;
        string delimiter = " ";
        vector<string> vecToken;
        T pos = 0;
        string token;
        cout << "str(before while loop): " << str << endl;
        while((pos = str.find(delimiter)) != string::npos)
        {
            cout << "inside while loop" << endl;
            token = str.substr(0,pos);
            vecToken.push_back(token);
            str.erase(0, pos+delimiter.length());
            cout << "str after erasing: " << str << endl;
        }
        vecToken.push_back(str);

        for (auto it = vecToken.begin(); it != vecToken.end(); ++it)
        {
            cout << *it << endl;
        }

        return vecToken;
    }

private:
    // extract the file copy number
    pair<string,T> extract_filename_copy_index(string filename)
    {
        T copy_index = 0;
        T pos = filename.find("(");
        string base_filename = filename.substr(0,pos);
        if (pos != string::npos)
        {
            filename.erase(0, pos+1);
            pos = filename.find(")");
            assert((pos != string::npos) && "invalid parentheses");
            // copy_index = stoi(filename.substr(0,pos));
            copy_index = atoi(filename.substr(0,pos).c_str());
        }
        return make_pair(base_filename,copy_index);
    }

    T create_file(string filename)
    {
        // returns: copy_index: This is the file copy number which is used to create the new file.
        //          In case we the file copy indices from [0,...,k], (k+1)th copy is created.
        //          Else we have to look for the smallest number from 0 onwards which is not used by current existing files for the base filename as "filename"
        typename unordered_map<string,T>::iterator it = filenameToIndexMap_.find(filename);
        T index;

        if (it == filenameToIndexMap_.end())
        {
            index = filenameToIndexMap_.size();
            filenameToIndexMap_[filename] = index; // ??? why it creates trouble if on RHS we write filenameToIndexMap_.size()
                                                   //     Reason: We should not rely on the order of the evaluation of the left and the right operands.
            vecMap_.push_back(map<T,T>());
        }
        else
        {
            index = (*it).second;
        }

        T copy_index = 0;
        if (vecMap_[index].empty())
        {
            // case 1: current base filename is created for the first time
            // case 2: all previous instances of current base filename has been deleted
            vecMap_[index].insert(make_pair(0,1));
        }
        else
        {
            auto mapIt = vecMap_[index].begin();
            if (mapIt->first == 0)
            {
                // case 1: it starts with 0, just increase the length will do
                copy_index = mapIt->second;
                // Check if we need to merge with next range i.e. next element of map
                if (vecMap_[index].size() == 1)
                {
                    ++mapIt->second; // increasing the length
                }
                else
                {
                    T range_begin = mapIt->first;
                    T range_len = mapIt->second;

                    advance(mapIt, 1);
                    if ((mapIt->first - (range_begin+range_len)) == 1)
                    {
                        range_len += 1 + mapIt->second;
                        // delete the 2nd range
                        vecMap_[index].erase(mapIt);
                        // update the length of 1st range
                        mapIt = vecMap_[index].begin();
                        mapIt->second = range_len;
                    }
                    else
                    {
                        mapIt = vecMap_[index].begin();
                        ++mapIt->second; // increasing the length
                    }
                }
            }
            else if (mapIt->first == 1)
            {
                // case 2: slot for copy index 0 is empty but the range is from 1 onwards
                copy_index = 0;
                T len_range = mapIt->second;
                vecMap_[index].erase(mapIt);
                vecMap_[index].insert(make_pair(0,len_range+1));
            }
            else
            {
                // case 3: as atleast slot 0,1 are empty hence we have to create a new element for the map
                copy_index = 0;
                vecMap_[index].insert(make_pair(0,1));
            }
        }

        // For debugging purpose
        bool isDebug = false;
        if (isDebug)
        {
            if (vecMap_[index].empty())
            {
                cout << "\tempty map for filename: " << filename << endl;
            }
            else
            {
                cout << "\tNumber of elements in map: " << vecMap_[index].size() << endl;
                auto mapIt = vecMap_[index].begin();
                cout << "\tFirst element: [" << mapIt->first << "," << mapIt->second << ")" << endl;
            }
        }

        return copy_index;
    }

    void delete_file(string filename, bool verbose=false)
    {
        pair<string,T> p = extract_filename_copy_index(filename);
        string baseFilename = p.first;
        T copy_index = p.second;

        typename unordered_map<string,T>::iterator it = filenameToIndexMap_.find(baseFilename);
        T index = (*it).second;
        // upper_bound will give the next element
        auto mapIt = vecMap_[index].upper_bound(copy_index);
        --mapIt;

        // case 1: copy_index == mapIt->first i.e. first value of the range
        // case 2: copy_index refers to value in between the range. The range needs to be split.
        // case 3: copy_index refers to the last element of the range. Update mapIt->second i.e. length of the range.
        T len_range = mapIt->second;
        if (mapIt->first == copy_index)
        {
            vecMap_[index].erase(mapIt);
            if (len_range > 1)
            {
                vecMap_[index].insert(make_pair(copy_index+1,len_range-1));
            }
        }
        else if (copy_index < (mapIt->first+len_range-1))
        {
            if (verbose)
            {
                cout << "\tsplitting the first range" << endl;
            }
            T range_begin = mapIt->first;
            vecMap_[index].erase(mapIt);
            // Now insert the two splits
            vecMap_[index].insert(make_pair(range_begin,copy_index-range_begin));
            vecMap_[index].insert(make_pair(copy_index+1,len_range-1-(copy_index-range_begin)));
        }
        else
        {
            --mapIt->second;
        }

        // For debugging purpose
        bool isDebug = false;
        if (isDebug)
        {
            if (vecMap_[index].empty())
            {
                cout << "\tempty map for filename: " << baseFilename << endl;
            }
            else
            {
                cout << "\tNumber of elements in map: " << vecMap_[index].size() << endl;
                auto mapIt = vecMap_[index].begin();
                cout << "\tFirst element: [" << mapIt->first << "," << mapIt->second << ")" << endl;
            }
        }
    }
private:
    // vecMap_[i]: i represents the index for filename as mapped in filenameToIndexMap_
    //             value of vecMap_[i] represents the map of copies of the filename
    //             copies are stored in the form of (start_index,n) i.e. [start_index,...,start_index+n)
    vector<map<T,T> > vecMap_;
    unordered_map<string,T> filenameToIndexMap_;
};

int main() {
    /*
    string command = "crt phonebook";
    FileCommand<int> file_command;
    vector<string> vecToken = file_command.splitCommand(command);
    for (auto it = vecToken.begin(); it != vecToken.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "size(vecToken): " << vecToken.size() << endl;
    */

    /*
    FileCommand<int> file_command;
    file_command.processCreate("phonebook");
    file_command.processCreate("phonebook");
    file_command.processDelete("phonebook(1)");
    file_command.processRename("phonebook","todo");
    */

    int q;
    cin >> q;
    FileCommand<int> file_command;
    // Process each command
    for(int a0 = 0; a0 < q; a0++){
        // Read the first string denoting the command type
        string command;
        cin >> command;
        // Write additional code to read the command's file name(s) and process the command
        // Print the output string appropriate to the command
        if (command == "crt")
        {
            string filename;
            cin >> filename;
            file_command.processCreate(filename);
        }
        else if (command == "del")
        {
            string filename;
            cin >> filename;
            file_command.processDelete(filename);
        }
        else if (command == "rnm")
        {
            string filename1;
            string filename2;
            cin >> filename1;
            cin >> filename2;
            file_command.processRename(filename1, filename2);
        }
        else
        {
            assert(false && "incorrect command");
        }

    }

    return 0;
}

/**
References:
    https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    https://stackoverflow.com/questions/22084783/function-stoi-not-declared
    https://stackoverflow.com/questions/5882872/reading-a-full-line-of-input (Advices to use getline())

    Explanation for the issue in create_file() is explained by Vlad from Moscow in
    https://stackoverflow.com/questions/44600167/shocked-by-the-strange-behavior-of-unordered-map

Observation:
    After reading cin >> q (where q is int)(??maybe type doesn't matter),
    getline() will read empty string first and then start reading the lines.
*/
