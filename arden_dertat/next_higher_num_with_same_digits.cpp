#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
//problem statement: http://www.ardendertat.com/2012/01/02/programming-interview-questions-24-find-next-higher-number-with-same-digits/
std::size_t next_higher_num(std::size_t input);

int main( int argc, char* argv[] )
{
    std::size_t test_case = 4;
    std::size_t input;

    switch (test_case)
    {
    case 0:
        input = 1234;
        break;
	case 1:
		input = 12543;
		break;
	case 2:
		input = 2541;
		break;
	case 3:
		input = 9999;
		break;
	case 4:
		input = 1000;
		break;
    }

    std::size_t output = next_higher_num(input);
	std::cout << "input: " << input << " output: " << output << std::endl;

    return 0;
}

std::size_t next_higher_num(std::size_t input)
{
    std::size_t output = input;
    std::size_t n_digits = 1;
    std::size_t divisor = 10;
    std::vector<std::size_t> vecDigit;

    vecDigit.push_back(input % divisor);

    while(input/divisor)
    {
        divisor *= 10;
        vecDigit.push_back((input % divisor)/(divisor/10));
        ++n_digits;
    }

    if (n_digits == 1)
    {
        return input;
    }

    std::size_t index_i = 1;
    while (index_i < vecDigit.size())
    {
        //checking the validity of vecDigit[index_i]
        if (vecDigit[index_i] < vecDigit[index_i-1])
        {
            //getting the next big number in vecDigit[0:index_i] will give the next big num we are looking for.
            //get the smallest digit from vecDigit[0:index_i-1] which is > vecDigit[index_i]
            //  and put that digit in vecDigit[index_i]
            std::size_t nextBigDigit = vecDigit[index_i-1];
            std::size_t index_j = index_i-1;
            std::size_t j = index_j;

            while (j > 0)
            {
                --j;
                if ( (vecDigit[index_i] < vecDigit[j]) && 
                    (vecDigit[j] < nextBigDigit) )
                {
                    nextBigDigit = vecDigit[j];
                    index_j = j;
                }
            }

            //swap
			std::swap(vecDigit[index_i],vecDigit[index_j]);
            //TBD: check if std::swap will do the swapping in vector also
            //std::size_t temp = vecDigit[index_i];
            //vecDigit[index_i] = vecDigit[index_j];
            //vecDigit[index_j] = temp;

            //Now we should sort vecDigit[0:index_i-1] so that least significant is having the biggest value
            std::sort(vecDigit.begin(),vecDigit.begin()+index_i, std::greater<std::size_t>());
			//TBD: we don't need sorting. We just need to reverse vecDigit[0:index_i-1]

			//now populate the output
			output = 0;
			j = 0;
			divisor = 1;
			while(j < vecDigit.size())
			{
				output += divisor*vecDigit[j];
				divisor *= 10;
				++j;
			}

			break;
        }

		++index_i;
    }

    return output;
}

/** Suggestions:
1. http://www.ardendertat.com/2012/01/02/programming-interview-questions-24-find-next-higher-number-with-same-digits/#comment-688948782
   Sandipan mentions alternate of sort.
   In reply, Arden mentions what we need to be careful.
2. "Since we know that digits are always between 0 and 9, we can use counting sort, radix sort, or bucket sort which can work in linear time O(K)."
3. http://wordaligned.org/articles/next-permutation 
	Mentions link to google code jam. And does detail analysis.
*/