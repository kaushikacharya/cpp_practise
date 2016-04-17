#include <algorithm>
#include <iostream>
#include <vector>

void pair_sum_func(std::vector<int>& inputVec, int sumVal, std::vector<std::pair<int,int> >& pairResult);
void store_pair(int num1, int num2, std::vector<std::pair<int,int> >& pairResult);

int main( int argc, char* argv[] )
{
    std::size_t test_case = 1;
    //std::vector<int> inputVec;
    std::vector<std::pair<int,int> > result;

    switch (test_case)
    {
    case 0:
#if 0
        static const int arr[] = {-2, -1, 1, 3, 7, 9, 10, 14, 20};
        std::vector<int> inputVec(arr, arr + sizeof(arr)/sizeof(arr[0]) );
        int sumVal = 11;

        pair_sum_func(inputVec, sumVal, result);
#endif
        break;
	case 1:
		static const int arr[] = {3, 7, 9, 2, -2, -1, 1, 2, 10, 14, 20};
        std::vector<int> inputVec(arr, arr + sizeof(arr)/sizeof(arr[0]) );
        int sumVal = 11;

        pair_sum_func(inputVec, sumVal, result);
        break;
    }

    return 0;
}

void pair_sum_func(std::vector<int>& inputVec, int sumVal, std::vector<std::pair<int,int> >& pairResult)
{
    int i = 0;
    int j = inputVec.size()-1;
    //TBD: don't save duplicate values - DONE
    //first sort the input vector
	std::sort(inputVec.begin(),inputVec.end());

    while (i < j)
    {
        // In this iteration, we keep i fixed and keep changing j
        int curSum = inputVec[i] + inputVec[j];

        if (curSum == sumVal)
        {
            //store it
            store_pair(inputVec[i],inputVec[j],pairResult);
        }
        else if (sumVal < curSum)
        {
            //keep decreasing j
            --j;
            while (i < j)
            {
                curSum = inputVec[i] + inputVec[j];
                if (curSum == sumVal)
                {
                    //store it
                    store_pair(inputVec[i],inputVec[j],pairResult);
                } 
                else if (curSum < sumVal)
                {
                    break;
                }
                --j;
            }
        }
        else
        {
            //keep increasing j
            ++j;
            while ( j < inputVec.size())
            {
                curSum = inputVec[i] + inputVec[j];
                if (curSum == sumVal)
                {
                    //store it
                    store_pair(inputVec[i],inputVec[j],pairResult);
                }
                else if (sumVal < curSum)
                {
                    break;
                }
                ++j;
            }
        }

        ++i;
    }

    int gh = 0;
}

void store_pair(int num1, int num2, std::vector<std::pair<int,int> >& pairResult)
{
    if (pairResult.empty())
    {
        pairResult.push_back(std::make_pair(num1,num2));
    } 
    else
    {
        //compare with the last stored pair
        std::pair<int,int> lastPair = pairResult.back();

        if ((lastPair.first == num1) && (lastPair.second == num2))
        {
            //don't store
        } 
        else
        {
            pairResult.push_back(std::make_pair(num1,num2));
        }
    }
}