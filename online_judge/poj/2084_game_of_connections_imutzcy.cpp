// http://www.kaixinwenda.com/article-imutzcy-8582025.html
#include<functional>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<numeric>
#include<cstring>
#include<cassert>
#include<cstdio>
#include<string>
#include<vector>
#include<bitset>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<list>
#include<set>
#include<map>

using namespace std;

const int MAX=100;
const int BASE=10000;

int a[101][MAX],i,j,n;


void multiply(int *a,int Max,int b)//????
{
	int i,array=0;
	for(i=Max-1;i>=0;i--){
		array+=b*a[i];
		a[i]=array%BASE;
		array/=BASE;
	}
}


void divide(int *a,int Max,int b)//????
{
	int i,div=0;
	for(i=0;i<=Max-1;i++){
		div=div*BASE+a[i];
		a[i]=div/b;
		div%=b;
	}
}

int main()
{
	memset(a[1],0,MAX*sizeof(int));
	for(i=2,a[1][MAX-1]=1;i<101;i++){
		memcpy(a[i],a[i-1],MAX*sizeof(int));    //h[1] = h[i-1]
		multiply(a[i],MAX,4*i-2);               //h[i] * = (4 * i - 2);
		divide(a[i],MAX,i+1);                   //h[i] / = (i + 1);
	}
	while(cin>>n,n+1){
		for(i=0;i<MAX&&a[n][i]==0;i++);       //?????? 0 ??? 
		cout<<a[n][i++];                      //??????0? 
		for(;i<MAX;i++)
			printf("%04d",a[n][i]);               // %04d  ?????????????5??? 
		cout<<endl;
	}
	return 0;
}