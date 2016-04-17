// http://poj.org/problem?id=2084
#include <cstdio>
#include <string>
#include <vector>
#include <limits>
#include <ctime>
#include <cassert>
#include <bitset>

#define MAX_N 100
#define BASE_POW 8 // 16

// http://www.parashift.com/c++-faq-lite/template-friends.html
template<typename T> class BigNum;
template<typename T> BigNum<T> operator*(BigNum<T>& bigNum1, BigNum<T>& bigNum2);
// http://www.cs.utsa.edu/~dj/ut/utsa/cs3343/lecture20.html
template<typename T>
class BigNum
{
public:
	BigNum(std::string str="0", T baseNum=10, unsigned char pow=BASE_POW);
	BigNum(std::vector<T> vec, T baseNum=10, unsigned char pow=BASE_POW);
	~BigNum();
public:
	void operator+=(BigNum<T> bigNum);
	bool operator==(BigNum<T> bigNum);
	friend BigNum<T> operator*<>(BigNum<T>& bigNum1, BigNum<T>& bigNum2);
public:
	std::vector<T> vec();
	std::string str();
	T getBase();
private:
	void setBase();
private:
	std::vector<T> vec_;
	unsigned char pow_; // we are considering base = 10 ^ pow_
	T base_;
};

template<typename T>
BigNum<T>::BigNum(std::string str, T baseNum, unsigned char pow)
: base_(baseNum)
, pow_(pow)
{
	T sizeVec = (str.size())/pow;
	if ( (str.size())%pow != 0 )
	{
		++sizeVec;
	}
	vec_.reserve(sizeVec);
	T elem = 0;
	T mult = 1;
	unsigned char i = 0;

	for (std::string::reverse_iterator rIt = str.rbegin(); rIt != str.rend(); ++rIt)
	{
		elem += mult*(*rIt-'0');
		++i;
		
		if (i == pow)
		{
			vec_.push_back(elem);
			// reset
			elem = 0;
			i = 0;
			mult = 1;
		}
		else
		{
			mult *= 10;
		}
	}
	if (i > 0)
	{
		vec_.push_back(elem);
	}

	//(*this).setBase();
}

template<typename T>
BigNum<T>::BigNum(std::vector<T> vec, T baseNum, unsigned char pow)
: vec_(vec)
, base_(baseNum)
, pow_(pow)
{
	//(*this).setBase();
}

template<typename T>
BigNum<T>::~BigNum()
{
}

template<typename T>
void BigNum<T>::setBase()
{
	base_ = 1;
	for (unsigned char i = 0; i < pow_; ++i)
	{
		base_ *= 10;
	}

}

template<typename T>
T BigNum<T>::getBase()
{
	return base_;
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
		std::string strElem;
		T elem = (*rIt);
		//printf("%llu ",elem);
		for (unsigned char i = 0; i < pow_; ++i)
		{
			if (elem == 0)
			{
				if (rIt != vec_.rbegin())
				{
					strElem += '0';
				}
			}
			else
			{
				strElem += elem%10 + '0';
				elem /= 10;
			}
		}

		// http://www.cplusplus.com/forum/beginner/11633/
		str += std::string(strElem.rbegin(),strElem.rend());
	}

	//printf("\n");
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
		vecSum.push_back(val%base_);
		carry = val/base_;
		int gh = 0;
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
	T base = bigNum1.getBase();
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
		carry = vec[i]/base;
		vec[i] = vec[i]%base;
	}
	while (carry > 0)
	{
		vec.push_back(carry%base);
		carry = carry/base;
	}
	
	BigNum<T> bigNum(vec,base);
	return bigNum;
}


void test_big_num()
{
	unsigned int baseNum = 1;
	for (unsigned char i = 0; i < BASE_POW; ++i)
	{
		baseNum *= 10;
	}

	BigNum<unsigned int> big1("432454",baseNum);
	BigNum<unsigned int> big2("765534",baseNum);
	//BigNum<unsigned int> big3 = big2*big1;
	BigNum<unsigned int> big3("1",baseNum);
	big3 += big1*big2;
	printf("%s\n",big3.str().c_str());
	/*
	BigNum<unsigned int> big1("56"); //567
	BigNum<unsigned int> big2("4932");

	//big1 += big2;
	BigNum<unsigned int> big3 = big2*big1;
	BigNum<unsigned int> big4("56");
	printf("equal=%d\n",big1==big4);
	printf("equal=%d\n",big1==big3);
	*/
	int gh = 0;
}

template<typename T>
class Game
{
public:
	Game();
	~Game();
public:
	BigNum<T> connections(T num1, T num2);
private:
	T base_;
	std::vector<BigNum<T> > vecConnections_;
	BigNum<T> zeroBigNum_;
	BigNum<T> oneBigNum_;
	std::bitset<2*MAX_N> bitSet_; //each bit initialized to false
};

template<typename T>
Game<T>::Game()
{
	base_ = 1;
	for (unsigned char i = 0; i < BASE_POW; ++i)
	{
		base_ *= 10;
	}

	zeroBigNum_ = BigNum<T>("0",base_);
	oneBigNum_ = BigNum<T>("1",base_);
	bitSet_[0] = true;
	bitSet_[1] = true;

	vecConnections_.reserve(2*MAX_N);
	//initialize
	for (T i = 0; i < 2*MAX_N; ++i)
	{
		vecConnections_.push_back(zeroBigNum_); // BigNum<T>("0")
	}
	vecConnections_[1] = oneBigNum_; // num2-num1 = 1
}

template<typename T>
Game<T>::~Game()
{
}

template<typename T>
BigNum<T> Game<T>::connections(T num1, T num2)
{
	if (!bitSet_[num2-num1])
	{
		BigNum<T> val = zeroBigNum_; // val("0")
		T numMid = num1+1;

		while (numMid <= num2)
		{
			BigNum<T> val1 = oneBigNum_;//val1("1");
			if (num1+1 < numMid)
			{
				val1 = connections(num1+1,numMid-1);
			}

			BigNum<T> val2 = oneBigNum_;//val2("1");
			if (numMid < num2)
			{
				val2 = connections(numMid+1,num2);
			}
			/*
			if (val1 == oneBigNum_)
			{
				val += val2;
			}
			else if (val2 == oneBigNum_)
			{
				val += val1;
			} 
			else
			{
				val += val1*val2;
			}
			*/
			val += val1*val2;

			numMid += 2;
		}

		vecConnections_[num2-num1] = val;
		bitSet_[num2-num1] = true;
	}

	return vecConnections_[num2-num1];
}

int main(int argc, char* argv[])
{
	bool test_flag = false;
	//printf("max: %llu\n",std::numeric_limits<unsigned long long>::max());
	Game<unsigned long long> game;

	if (test_flag)
	{
		//test_big_num();
		/*
		FILE* pInputFile = fopen("d:/cpp_practise/online_judge/poj/2084_game_of_connections_input.txt","w");
		for (unsigned char i = 1; i < 101; ++i)
		{
			fprintf(pInputFile,"%d\n",i);
		}
		fprintf(pInputFile,"%d\n",-1);
		fclose(pInputFile);
		*/

		//unsigned long long max_limit = std::numeric_limits<unsigned long long>::max();
		int total_time = 0;
		FILE* pFile = fopen("d:/cpp_practise/online_judge/poj/2084_game_of_connections_output.txt","w");
		for (unsigned char i = 1; i < 101; ++i)
		{
			clock_t t = clock();
			BigNum<unsigned long long> connections = game.connections(1,2*i);
			t = clock() - t;
			total_time += t;
			/*
			if (max_limit/2 < connections)
			{
			printf("exceeded\n");
			}
			*/
			// http://stackoverflow.com/questions/38561/what-is-the-argument-for-printf-that-formats-a-long
			//printf("i = %d :: connections: %s :: time(clocks):%d  time(in sec): %f\n",i,connections.str().c_str(),t,((float)t)/CLOCKS_PER_SEC);
			//fprintf(pFile,"i = %d :: connections: %s\n",i,connections.str().c_str());
			fprintf(pFile,"%s\n",connections.str().c_str());
			fprintf(pFile,"clicks: %d :: time(in sec): %f\n",t,((float)t)/CLOCKS_PER_SEC);
		}

		fprintf(pFile,"TOTAL:: clicks: %d :: time(in sec): %f\n",total_time,((float)total_time)/CLOCKS_PER_SEC);
		fclose(pFile);
	}
	else
	{
		int ch;
		int total_time = 0;
		
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
				//Game<unsigned long long> game(2*ch);
				//clock_t t = clock();
				printf("%s\n",game.connections(1,2*ch).str().c_str());
				//t = clock() - t;
				//printf("clicks: %d :: time(in sec): %f\n",t,((float)t)/CLOCKS_PER_SEC);
				//total_time += t;
			}
		}
		
		//printf("TOTAL:: clicks: %d :: time(in sec): %f\n",total_time,((float)total_time)/CLOCKS_PER_SEC);
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

Verified my output with this program's output
http://www.kaixinwenda.com/article-imutzcy-8582025.html
*/