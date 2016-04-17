#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
//problem statement: http://www.ardendertat.com/2011/12/01/programming-interview-questions-19-find-next-palindrome-number/

std::size_t next_palindrome_func(std::size_t input);

int main( int argc, char* argv[] )
{
	std::size_t test_case = 2;
	std::size_t input;

	switch (test_case)
	{
	case 0:
		input = 23140;
		break;
	case 1:
		input = 231149;
		break;
	case 2:
		input = 129913;
		break;
	}

	std::size_t output = next_palindrome_func(input);
	std::cout << "input: " << input << " :: output: " << output << std::endl;
	return 0;
}

std::size_t next_palindrome_func(std::size_t input)
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
		if (input < 9)
		{
			output = input + 1;
		}
		else
		{
			output = 11;
		}
		return output;
	}

	std::size_t mid_index = n_digits/2;
	//Note: left_half is the flip of left half on input

	if (n_digits % 2 == 0)
	{
		//even no of digits
		std::size_t left_half = vecDigit[mid_index];
		divisor = 1;
		for (std::size_t i = mid_index+1; i < n_digits; ++i)
		{
			left_half = left_half*10 + vecDigit[i];
		}
		std::size_t right_half = input%((std::size_t)(std::pow(10.0,(int)mid_index)));

		if (left_half < right_half)
		{
			std::size_t i = mid_index;
			bool incr_flag(true);
			for (std::size_t i = mid_index; i < n_digits; ++i)
			{
				if (incr_flag)
				{
					if (vecDigit[i] < 9)
					{
						++vecDigit[i];
						incr_flag = false;
						break;
					}
					else
					{
						vecDigit[i] = 0;
					}
				}
			}
			for (std::size_t i = 0; i < mid_index; ++i)
			{
				vecDigit[i] = vecDigit[n_digits-1-i];
			}
#if 0
			while(i < n_digits)
			{
				//compare vecDigit[i],vecDigit[n_digits-i-1]
				if (vecDigit[n_digits-i-1] < vecDigit[i])
				{
					vecDigit[n_digits-i-1] = vecDigit[i];
					break;
				}
				else if (vecDigit[i] < vecDigit[n_digits-i-1])
				{
					vecDigit[i] = vecDigit[n_digits-i-1];
					break;
				}
				++i;
			}
			//now assign left side digits to corresponding right side digits for the rest of right side
			while(i < n_digits)
			{
				vecDigit[n_digits-i-1] = vecDigit[i];
				++i;
			}
#endif
		}
		else if (right_half < left_half)
		{
			for (std::size_t i = 0; i < mid_index; ++i)
			{
				vecDigit[i] = vecDigit[n_digits-1-i];
			}
		}
	}
	else
	{
		//odd no of digits
		std::size_t left_half = vecDigit[mid_index+1];
		for (std::size_t i = mid_index+2; i < n_digits; ++i)
		{
			left_half = left_half*10 + vecDigit[i];
		}
		//std::size_t left_half = input/((std::size_t)(std::pow(10.0,(int)mid_index+1)));
		std::size_t right_half = input%((std::size_t)(std::pow(10.0,(int)mid_index)));

		if (left_half == right_half)
		{
		}
		else if (left_half < right_half)
		{
			if (vecDigit[mid_index] < 9)
			{
				++vecDigit[mid_index];
			}
			else
			{
				//e.g. input: 23940, output: 24042
				vecDigit[mid_index] = 0;
				bool incr_flag(true);
				for (std::size_t i = mid_index+1; i < n_digits; ++i)
				{
					if (incr_flag)
					{
						if (vecDigit[i] < 9)
						{
							++vecDigit[i];
							incr_flag = false;
							break;
						}
						else
						{
							vecDigit[i] = 0;
						}
					}
				}
			}

			for (std::size_t i = 0; i < mid_index; ++i)
			{
				vecDigit[i] = vecDigit[n_digits-1-i];
			}
		}
		else
		{
			for (std::size_t i = 0; i < mid_index; ++i)
			{
				vecDigit[i] = vecDigit[n_digits-1-i];
			}
		}

	}

	//create output from vecDigit
	output = vecDigit[0];
	divisor = 1;
	for (std::size_t i = 1; i < n_digits; ++i)
	{
		divisor *= 10;
		output += divisor*vecDigit[i];
	}

	return output;
}