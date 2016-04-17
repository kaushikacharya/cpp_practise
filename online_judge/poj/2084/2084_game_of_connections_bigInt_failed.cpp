// http://poj.org/problem?id=2084
#include <cstdio>
#include <string>
#include <vector>
#include <limits>
#include <ctime>

// http://www.parashift.com/c++-faq-lite/template-friends.html
template<typename T> class BigNum;
template<typename T> BigNum<T> operator*(BigNum<T>& bigNum1, BigNum<T>& bigNum2);

template<typename T>
class BigNum
{
public:
	BigNum(std::string str);
	BigNum(std::vector<T> vec);
	~BigNum();
public:
	void operator+=(BigNum<T> bigNum);
	bool operator==(BigNum<T> bigNum);
	friend BigNum<T> operator*<>(BigNum<T>& bigNum1, BigNum<T>& bigNum2);
	/*friend BigNum<T> operator*(const BigNum<T>& bigNum1, const BigNum<T>& bigNum2)
	{
		std::vector<T> vec;
		BigNum<T> bigNum(vec);
		return bigNum;
	}*/
public:
	std::vector<T> vec();
	std::string str();
private:
	std::vector<T> vec_;
};

template<typename T>
BigNum<T>::BigNum(std::string str)
{
	vec_.reserve(str.size());
	for (std::string::reverse_iterator rIt = str.rbegin(); rIt != str.rend(); ++rIt)
	{
		vec_.push_back(*rIt-'0');
	}
}

template<typename T>
BigNum<T>::BigNum(std::vector<T> vec)
: vec_(vec)
{
}

template<typename T>
BigNum<T>::~BigNum()
{
}

template<typename T>
std::vector<T> BigNum<T>::vec()
{
	return vec_;
}

template<typename T>
std::string BigNum<T>::str()
{
	std::string str;
	for (std::vector<T>::reverse_iterator rIt = vec_.rbegin(); rIt != vec_.rend(); ++rIt)
	{
		str += (*rIt)+'0';
	}

	return str;
}

template<typename T>
void BigNum<T>::operator +=(BigNum<T> bigNum)
{
	std::vector<T> vecSum;
	T sz = std::max(vec_.size(), bigNum.vec().size());
	vecSum.reserve(sz);

	T carry = 0;
	for (T i = 0; i < sz; ++i)
	{
		T val = carry;
		if (i < vec_.size())
		{
			val += vec_[i];
		}
		if (i < bigNum.vec().size())
		{
			val += bigNum.vec()[i];
		}
		vecSum.push_back(val%10);
		carry = val/10;
		//int gh = 0;
	}
	if (carry > 0)
	{
		vecSum.push_back(carry);
	}

	vec_ = vecSum;
}

template<typename T>
bool BigNum<T>::operator ==(BigNum<T> bigNum)
{
	bool flag = true;

	if(vec_.size() != bigNum.vec().size())
	{
		flag = false;
	}
	else
	{
		for (T i = 0; i < vec_.size(); ++i)
		{
			if (vec_[i] != bigNum.vec()[i])
			{
				flag = false;
				break;
			}
		}
	}

	return flag;
}

// http://www.learncpp.com/cpp-tutorial/92-overloading-the-arithmetic-operators/

template<typename T>
BigNum<T> operator*(BigNum<T>& bigNum1, BigNum<T>& bigNum2)
{
	std::vector<T> vec;
	T sz = bigNum1.vec().size()+bigNum2.vec().size()-1;
	vec.reserve(sz);
	//initialize
	for (T i = 0; i < sz; ++i)
	{
		vec.push_back(0);
	}

	for (T i=0; i < bigNum2.vec().size(); ++i)
	{
		for (T j=0; j < bigNum1.vec().size(); ++j)
		{
			T val = bigNum2.vec()[i] * bigNum1.vec()[j];
			vec[i+j] += val;
		}
	}

	T carry = 0;
	for (T i = 0; i < sz; ++i)
	{
		vec[i] += carry;
		carry = vec[i]/10;
		vec[i] = vec[i]%10;
	}
	while (carry > 0)
	{
		vec.push_back(carry%10);
		carry = carry/10;
	}
	
	BigNum<T> bigNum(vec);
	return bigNum;
}


void test_big_num()
{
	BigNum<unsigned int> big1("56"); //567
	BigNum<unsigned int> big2("4932");

	//big1 += big2;
	BigNum<unsigned int> big3 = big2*big1;
	BigNum<unsigned int> big4("56");
	printf("equal=%d\n",big1==big4);
	printf("equal=%d\n",big1==big3);
	int gh = 0;
}

template<typename T>
class Game
{
public:
	Game(T n);
	~Game();
public:
	BigNum<T> connections(T num1, T num2);
private:
	T n_;
	std::vector<BigNum<T> > vecConnections_;
};

template<typename T>
Game<T>::Game(T n)
: n_(n)
{
	vecConnections_.reserve(n);
	//initialize
	for (T i = 0; i < n; ++i)
	{
		vecConnections_.push_back(BigNum<T>("0"));
	}
}

template<typename T>
Game<T>::~Game()
{
}

template<typename T>
BigNum<T> Game<T>::connections(T num1, T num2)
{
	if (num2 - num1 <= 1)
	{
		return BigNum<T>("1");
	}
/*
	if (vecConnections_[num2-num1] > 0)
	{
		return vecConnections_[num2-num1];
	}
*/

	if (vecConnections_[num2-num1] == BigNum<T>("0"))
	{
		BigNum<T> val("0");
		T numMid = num1+1;

		while (numMid <= num2)
		{
			BigNum<T> val1("1");
			if (num1+1 < numMid)
			{
				val1 = connections(num1+1,numMid-1);
			}

			BigNum<T> val2("1");
			if (numMid < num2)
			{
				val2 = connections(numMid+1,num2);
			}

			val += val1*val2;

			numMid += 2;
		}

		//if (vecConnections_[num2-num1] == 0)
		//{
			vecConnections_[num2-num1] = val;
		//}
		return val;
	}
	else
	{
		return vecConnections_[num2-num1];
	}
}

void test_cases()
{
	unsigned long long max_limit = std::numeric_limits<unsigned long long>::max();
	for (char i = 1; i < 101; ++i)
	{
		clock_t t = clock();
		Game<unsigned int> game(2*i);
		BigNum<unsigned int> connections = game.connections(1,2*i);
		t = clock() - t;
		/*
		if (max_limit/2 < connections)
		{
			printf("exceeded\n");
		}
		*/
		// http://stackoverflow.com/questions/38561/what-is-the-argument-for-printf-that-formats-a-long
		//printf("i = %d :: connections: %llu :: time(clocks):%d  time(in sec): %f\n",i,connections,t,((float)t)/CLOCKS_PER_SEC);
		printf("i = %d :: connections: %s :: time(clocks):%d  time(in sec): %f\n",i,connections.str().c_str(),t,((float)t)/CLOCKS_PER_SEC);
	}
}

int main(int argc, char* argv[])
{
	bool test_flag = true;
	//printf("max: %llu\n",std::numeric_limits<unsigned long long>::max());

	if (test_flag)
	{
		test_cases();
		//test_big_num();
	}
	else
	{
		char ch;
		while (scanf("%d",&ch) != EOF)
		{
			if (ch == -1)
			{
				break;
			}
			else
			{
				//Game<unsigned long long> game(2*ch);
				//printf("%llu\n",game.connections(1,2*ch));
				Game<unsigned int> game(2*ch);
				printf("%s\n",game.connections(1,2*ch).str().c_str());
			}
		}
	}

	return 0;
}

/*
http://stackoverflow.com/questions/12102621/can-i-make-my-own-custom-data-type-larger-than-the-ones-in-c
Mark Garcia's answer

http://online-judge.uva.es/board/viewtopic.php?f=14&t=50671&p=127261&hilit=bigger+than+long+long#p127261
suggests using arrays

http://stackoverflow.com/questions/269268/how-to-implement-big-int-in-c
orcmid suggests "The Art of Computer Programming" chapter 4

http://stackoverflow.com/questions/5381882/types-bigger-than-long-long-in-c
http://stackoverflow.com/questions/589575/size-of-int-long-etc

http://mahmoud.devgator.com/?page=programming&single=1&post=125&like=0
Addition and Multiplication implemented

Libraries:
https://mattmccutchen.net/bigint/index.html
http://gmplib.org/
*/