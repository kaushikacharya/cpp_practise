/**
* Problem: Disjoint set (Union-Find)
* URL: https://practice.geeksforgeeks.org/problems/disjoint-set-union-find/1
*      https://www.geeksforgeeks.org/disjoint-set-data-structures/
* Date: Jan 30, 2021
*/

// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;
int find(int a[],int x);
void unionSet(int a[],int x ,int z);
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[n+1];
		for(int i=1;i<=n;i++)
			a[i]=i;
		int k;
		cin>>k;
		for(int i=0;i<k;i++){
			string s;
			cin>>s;
			if(s=="UNION"){
				int z,x;
				cin>>x>>z;
				unionSet(a,x,z);
			}
			else{
				int x;
				cin>>x;
				int parent=find(a,x);
				cout<<parent<<" ";
			}
		}
		cout<<endl;
	}
}// } Driver Code Ends


/*Complete the functions below*/
int find(int a[],int x)
{
    //add code here
    if (a[x] == x) {
        return x;
    }

    int parent = find(a, a[x]);
    // update the parent of x with the root of the tree
    a[x] = parent;

    return parent;
}

void unionSet(int a[],int x,int z)
{
    //add code here.
    int parent_x = find(a, x);
    int parent_y = find(a, z);

    if (parent_x == parent_y) {
        return;
    }

    a[parent_x] = parent_y;
}
