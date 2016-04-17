// http://poj.org/problem?id=2418

#include <cstdio>
#include <map>
#include <string>

#define READ_FROM_FILE 0

class Hardwood
{
public:
    Hardwood();
    ~Hardwood();
public:
    void readInput(FILE* pFile);
    void writeOutput();
private:
    void updateMap(std::string treeSpecies);
private:
    unsigned int countTree_;
    std::map<std::string,unsigned int> treeSpeciesMap_;
};

Hardwood::Hardwood()
{
    countTree_ = 0;
}

Hardwood::~Hardwood()
{
}

void Hardwood::readInput(FILE *pFile)
{
    //std::string treeSpecies;
    char* treeSpecies = (char*)malloc(30);

    if (READ_FROM_FILE)
    {
        while(fgets(treeSpecies,30,pFile) != NULL)
        {
            // http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
			// http://stackoverflow.com/questions/1195675/convert-a-char-to-stdstring
			std::string str(strtok(treeSpecies,"\n"));
			updateMap(str);
            ++countTree_;
        }
    }
    else
    {
        while(gets(treeSpecies) != NULL)
        {
            updateMap(treeSpecies);
            ++countTree_;
        }
    }
}

void Hardwood::updateMap(std::string treeSpecies)
{
    std::map<std::string,unsigned int>::iterator it = treeSpeciesMap_.find(treeSpecies);
    if (it == treeSpeciesMap_.end())
    {
        treeSpeciesMap_[treeSpecies] = 1;
    }
    else
    {
        ++(*it).second;
    }
}

void Hardwood::writeOutput()
{
    for (std::map<std::string,unsigned int>::iterator it = treeSpeciesMap_.begin(); it != treeSpeciesMap_.end(); ++it)
    {
        float percentage = ((*it).second * 100.0)/countTree_;
        std::string str = (*it).first;
		// http://www.cplusplus.com/forum/general/33580/   // Can't use printf, have to use cout?
		// http://www.cplusplus.com/forum/beginner/47924/ // how to convert string to char* and vice versa
		printf("%s",str.c_str());
        printf(" %0.4f\n",percentage);
    }
}


int main(int argc, char* argv[])
{
    FILE *pFile;
    
    if (READ_FROM_FILE)
    {
       pFile = fopen("D:/cpp_practise/online_judge/poj/2418_hardwood_species.txt","r");
    }
    else
    {
        pFile = 0;
    }

    Hardwood hWood;
    hWood.readInput(pFile);
    hWood.writeOutput();

    return 0;
}