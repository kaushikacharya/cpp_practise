// http://poj.org/problem?id=1007
// http://www.mkyong.com/c/how-to-handle-unknow-size-user-input-in-c/
// http://www.cplusplus.com/reference/cstdio/gets/
#include <cstdio>
#include <cstdlib>

class Inversion
{
public:
    Inversion(char* str,unsigned int len);
    ~Inversion();
public:
    unsigned int inversionCount();
private:
    unsigned int count_and_sort(unsigned int i, unsigned int j);
    unsigned int split_count_and_sort(unsigned int i, unsigned int mid_index, unsigned int j);
private:
    char* str_;
    unsigned int len_;
    unsigned int inversionCount_;
};

Inversion::Inversion(char* str,unsigned int len)
    : str_(str)
    , len_(len)
{
    inversionCount_ = 0;
    count_and_sort(0,len-1);
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

    char* str = (char*)malloc(str_size);
    unsigned int inv_count = 0;
    unsigned int count = 0;

    while (count < str_size)
    {
        if ((p <= mid_index) && (q <= j))
        {
            if (str_[q] < str_[p])
            {
                str[count] = str_[q];
                ++q;
                inv_count += mid_index - p + 1;
            }
            else
            {
                str[count] = str_[p];
                ++p;
            }
        }
        else if (mid_index < p)
        {
            str[count] = str_[q];
            ++q;
        }
        else
        {
            str[count] = str_[p];
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
    free(str);

    return inv_count; // remove later
}

// ----------------------------
void read_string(unsigned int str_len)
{
    char* str = (char*)malloc(str_len);
    printf("str(input): ");
    gets(str);
    printf("str: %s : %c\n",str,str[2]);
}

// ------------------------------
int main(int argc, char* argv[])
{
    /*
    printf("enter two lines:\n");
    read_string(5);
    read_string(5);
    */
    char* str = (char*)malloc(5);
    str = "ACGTC";
    //printf("%d",(3+4)/2);
    char* str_new = (char*)malloc(5);
    unsigned count = 0;
    while (count < 5)
    {
        str_new[count] = 'A';
        ++count;
    }
    str[2] = (char)str_new[2];

    Inversion inversion(str,5);
    printf("inv: %d\n",inversion.inversionCount());

    return 0;
}
