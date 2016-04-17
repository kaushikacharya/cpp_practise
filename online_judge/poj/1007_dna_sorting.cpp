// http://poj.org/problem?id=1007
// http://www.mkyong.com/c/how-to-handle-unknow-size-user-input-in-c/
// http://www.cplusplus.com/reference/cstdio/gets/
// http://stackoverflow.com/questions/279854/how-do-i-sort-a-vector-of-pairs-based-on-the-second-element-of-the-pair

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm> // std::sort
#include <functional> // std::less

#define READ_FROM_FILE 0

template<class T1, class T2, class Pred = std::less<T2> >
struct sort_pair_second
{
    bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right)
    {
        Pred p;
        return p(left.second, right.second);
    }
};

class Inversion
{
public:
    Inversion(std::vector<char> str,unsigned int len);
    ~Inversion();
public:
    unsigned int inversionCount();
private:
    unsigned int count_and_sort(unsigned int i, unsigned int j);
    unsigned int split_count_and_sort(unsigned int i, unsigned int mid_index, unsigned int j);
private:
    std::vector<char> str_;
    unsigned int len_;
    unsigned int inversionCount_;
};

Inversion::Inversion(std::vector<char> str,unsigned int len)
    : str_(str)
    , len_(len)
{
    inversionCount_ = 0;
    inversionCount_ = count_and_sort(0,len-1);
}

Inversion::~Inversion()
{
}

unsigned int Inversion::inversionCount()
{
    return inversionCount_;
}

unsigned int Inversion::count_and_sort(unsigned int i, unsigned int j)
{
    if (i == j)
    {
        return 0;
    }

    unsigned int mid_index = (i+j)/2;
    unsigned int x = count_and_sort(i,mid_index);
    unsigned int y = count_and_sort(mid_index+1,j);
    unsigned int z = split_count_and_sort(i,mid_index,j);

    return x+y+z;
}

unsigned int Inversion::split_count_and_sort(unsigned int i, unsigned int mid_index, unsigned int j)
{
    // str_[i,...,mid_index] is already sorted
    // str_[mid_index+1,...,j] is already sorted
    unsigned int p = i;
    unsigned int q = mid_index+1;
    unsigned int str_size = j-i+1;

    std::vector<char> str;
    str.reserve(str_size);

    unsigned int inv_count = 0;
    unsigned int count = 0;

    while (count < str_size)
    {
        if ((p <= mid_index) && (q <= j))
        {
            if (str_[q] < str_[p])
            {
				str.push_back(str_[q]);
                ++q;
                inv_count += mid_index - p + 1;
            }
            else
            {
				str.push_back(str_[p]);
                ++p;
            }
        }
        else if (mid_index < p)
        {
			str.push_back(str_[q]);
            ++q;
        }
        else
        {
			str.push_back(str_[p]);
            ++p;
        }

        ++count;
    }

    if (inv_count > 0)
    {
        count = 0;
        while (count < str_size)
        {
            str_[i+count] = str[count];
            ++count;
        }
    }

    return inv_count;
}

// ----------------------------
class DnaSort
{
public:
    DnaSort(unsigned int lenSeq,unsigned int nSeq);
    ~DnaSort();
public:
    void readListSeq(FILE* pFile);
    void sortSeq(bool print_flag=false);
private:
    void readSeq(unsigned int lenSeq, std::vector<char>& seq, FILE* pFile);
private:
    unsigned int lenSeq_; // length of each sequence
    unsigned int nSeq_; // count of sequences
    std::vector<std::pair<std::vector<char>,unsigned int> > vecSeqInvCountPair_;
};

DnaSort::DnaSort(unsigned int lenSeq, unsigned int nSeq)
    : lenSeq_(lenSeq)
    , nSeq_(nSeq)
{

}

DnaSort::~DnaSort()
{
    vecSeqInvCountPair_.clear();
}

void DnaSort::readSeq(unsigned int lenSeq, std::vector<char>& seq, FILE* pFile)
{
    char* str = (char*)malloc(lenSeq);
	char ch;

    if (READ_FROM_FILE)
    {
        fgets(str,lenSeq+1,pFile);
		fscanf(pFile,"%c",&ch);
    }
    else
    {
        gets(str);
        //scanf("%c",&ch);
    }

    //Now store it as seq (vector of chars)
    unsigned int i = 0;
    while (i < lenSeq)
    {
        seq.push_back(str[i]);
        ++i;
    }
    /*
    i = 0;
    while (i < lenSeq)
    {
        printf("%c",seq[i]);
		++i;
    }
    printf("read a line");
    */
}

void DnaSort::readListSeq(FILE* pFile)
{
    vecSeqInvCountPair_.reserve(nSeq_);

    unsigned int seq_i = 0;
    while (seq_i < nSeq_)
    {
        std::vector<char> seq;
        seq.reserve(lenSeq_);
        readSeq(lenSeq_,seq,pFile);

        Inversion inversion(seq,lenSeq_);
        //printf("inv: %d\n",inversion.inversionCount());

        vecSeqInvCountPair_.push_back(std::make_pair(seq,inversion.inversionCount()));
        ++seq_i;
    }
}

void DnaSort::sortSeq(bool print_flag)
{
    std::sort(vecSeqInvCountPair_.begin(),vecSeqInvCountPair_.end(),sort_pair_second<std::vector<char>,unsigned int>());

    if (print_flag)
    {
        for (std::vector<std::pair<std::vector<char>,unsigned int> >::iterator it = vecSeqInvCountPair_.begin(); it != vecSeqInvCountPair_.end(); ++it)
        {
            std::pair<std::vector<char>,unsigned int> seqInvCount = (*it);
            std::vector<char> seq = (*it).first;

            for (std::vector<char>::iterator chIt = seq.begin(); chIt != seq.end(); ++chIt)
            {
                printf("%c",(*chIt));
            }
            printf("\n");
        }
    }
}

// ----------------------------

void read_string(unsigned int str_len, std::vector<char>& vecChar)
{
    char* str = (char*)malloc(str_len);
	printf("str(input)(of len:%d): ",str_len);
    gets(str);

    unsigned int i = 0;
    while (i < str_len)
    {
        vecChar.push_back(str[i]);
        ++i;
    }

	printf("str: %s : %c \n",str,str[2]);
}


// ------------------------------
int main(int argc, char* argv[])
{
    unsigned n,m;
    FILE* pFile;
	
    if (READ_FROM_FILE)
    {
        pFile = fopen ("E:/cpp_practise/online_judge/poj/1007_dna_sorting.txt","r");
        fscanf(pFile,"%d",&n); // length of each sequence
        fscanf(pFile,"%d",&m); // no of sequences
		char ch;
		fscanf(pFile,"%c",&ch);
		int gh = 0;
    }
    else
    {
        pFile = 0;
        scanf("%d",&n); // length of each sequence
        scanf("%d",&m); // no of sequences
		char ch;
		do
		{
			scanf("%c",&ch);
		}while(ch != '\n');
		int gh = 0;
    }

    DnaSort dnaSort(n,m);
    dnaSort.readListSeq(pFile);
    dnaSort.sortSeq(true);


	// ---- Test for gets -----
	/*
    std::vector<char> vecChar;
    vecChar.reserve(5);
    read_string(5,vecChar);
    printf("char at pos: %c\n",vecChar[3]);
   */

    /*
    printf("enter two lines:\n");
    read_string(5);
    read_string(5);
    */
    //char* str = (char*)malloc(5);
    //str = "ACGTC";
    //printf("%d",(3+4)/2);

	//-------- Test for inversion count of a particular string -----
    /*
    std::string str_string("TTTTG");
    unsigned int size_str = 5;
    std::vector<char> str;
    str.reserve(size_str);
    unsigned count = 0;
    while (count < size_str)
    {
        str.push_back(str_string[count]);
        ++count;
    }

    //printf("%c",str[2]);
    //str[2] = 'C';
    //printf("%c",str[2]);
   
    Inversion inversion(str,size_str);
    printf("inv: %d\n",inversion.inversionCount());
    */
    return 0;
}
