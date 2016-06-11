#include <iostream>
#include <vector>

using namespace std;

long int sumOfIntegers(vector<int>& vecNum)
{
    long int sum = 0;
    for(vector<int>::iterator it = vecNum.begin(); it != vecNum.end(); ++it)
    {
        sum += *it;
    }
    return sum;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin >> n;

    // Now read the numbers
    vector<int> nums;
    nums.reserve(n);

    for (int i=0; i != n; ++i)
    {
        int num;
        cin >> num;
        nums.push_back(num);
    }

    long int sum = sumOfIntegers(nums);
    cout << sum << endl;

    return 0;
}
