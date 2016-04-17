// https://www.hackerrank.com/challenges/sherlock-and-the-beast
#include <iostream>
#include <string>

void process(unsigned long N);

void process(unsigned long N)
{
	//3*x + 5*y = N
	unsigned long digits5, digits3;
	unsigned long interN = N;
	digits3 = 0;
	while (true)
	{
		if (interN%3 == 0)
		{
			break;
		}
		else if (interN < 3)
		{
			break;
		}
		else if (interN < 5)
		{
			break;
		}
		else
		{
			interN -= 5;
			++digits3;
		}
	}

	if (interN%3 == 0)
	{
		digits5 = interN/3;
		unsigned long digit_i = 0;
		std::string str;
		for (digit_i = 0; digit_i != 3*digits5; ++digit_i)
		{
			str += '5';
		}
		for (digit_i = 0; digit_i != 5*digits3; ++digit_i)
		{
			str += '3';
		}
		std::cout << str << std::endl;
	}
	else
	{
		std::cout << -1 << std::endl;
	}
}

int main(int argc, char* argv[])
{
	unsigned int nCase;
	std::cin >> nCase;

	unsigned long N;
	for (unsigned int case_i = 0; case_i != nCase; ++case_i)
	{
		std::cin >> N;
		process(N);
	}

	return 0;
}