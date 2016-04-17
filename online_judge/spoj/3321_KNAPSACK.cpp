// http://www.spoj.com/problems/KNAPSACK/
#include <cstdio>
#include <vector>
#include <algorithm>

#define READ_FROM_FILE 0

template<typename S,typename V>
class KnapSack
{
public:
	KnapSack(S capacity, S nItem);
	~KnapSack();
public:
	void read_input(FILE* pFile);
	void process();
	V max_value();
private:
	S capacity_;
	S nItem_;
	std::vector<V> vecKnapSack_; //storing 2d array in a single dimension
private:
	struct SizeVal
	{
		S size;
		V val;
		SizeVal(S sz, V vl)
			: size(sz)
			, val(vl)
		{};
	};
	std::vector<SizeVal> vecSizeVal_;
};
//---
template<typename S,typename V>
KnapSack<S,V>::KnapSack(S capacity, S nItem)
: capacity_(capacity)
, nItem_(nItem)
{
	vecSizeVal_.reserve(capacity_);
	vecKnapSack_.reserve((capacity_+1)*(nItem_+1));
}
template<typename S,typename V>
KnapSack<S,V>::~KnapSack()
{}
template<typename S,typename V>
void KnapSack<S,V>::read_input(FILE* pFile)
{
	S size;
	V val;
	for (S item_i = 0; item_i != nItem_; ++item_i)
	{
		if (READ_FROM_FILE)
		{
			fscanf(pFile,"%u",&size);
			fscanf(pFile,"%u",&val);
		}
		else
		{
			scanf("%u",&size);
			scanf("%u",&val);
		}
		SizeVal sizeVal(size,val);
		vecSizeVal_.push_back(sizeVal);
	}
}
template<typename S,typename V>
void KnapSack<S,V>::process()
{
	//initialize for no item
	for (S sz=0; sz != (capacity_+1); ++sz)
	{
		vecKnapSack_.push_back(0);
	}

	V val;
	for (S item_i = 1; item_i != (nItem_+1); ++item_i)
	{
		for (S sz=0; sz != (capacity_+1); ++sz)
		{
			//Note: item i in vecSizeVal_ corresponds to index (i-1)
			//      But same is not true for vecKnapSack_
			if (sz < vecSizeVal_[item_i-1].size)
			{
				val = vecKnapSack_[(item_i-1)*(capacity_+1) + sz];
			}
			else
			{
				val = std::max(vecKnapSack_[(item_i-1)*(capacity_+1) + sz],
					vecSizeVal_[item_i-1].val + vecKnapSack_[(item_i-1)*(capacity_+1) + (sz - vecSizeVal_[item_i-1].size)]);
			}

			vecKnapSack_.push_back(val);
		}
	}
}
template<typename S,typename V>
V KnapSack<S,V>::max_value()
{
	return vecKnapSack_.back();
}
//---
int main(int argc, char* argv[])
{
	unsigned int capacity, nItem;
	FILE* pFile = 0;

	if (READ_FROM_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/spoj/3321_KNAPSACK_input.txt","r");
		fscanf(pFile,"%u",&capacity);
		fscanf(pFile,"%u",&nItem);
	}
	else
	{
		scanf("%u",&capacity);
		scanf("%u",&nItem);
	}
	KnapSack<unsigned int, unsigned long> knapSack(capacity,nItem);
	knapSack.read_input(pFile);
	knapSack.process();
	printf("%lu\n",knapSack.max_value());
	return 0;
}