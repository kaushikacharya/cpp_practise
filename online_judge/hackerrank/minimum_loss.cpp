// https://www.hackerrank.com/challenges/minimum-loss/problem
// Dec 29th 2017

#include <bits/stdc++.h>

using namespace std;

bool cmp(const pair<long,int>& p1, const pair<long,int>& p2)
{
    return p1.first < p2.first;
}

int minimumLoss(vector <long> vecPrice) {
    // Complete this function
    // cout << "vec size: " << vecPrice.end()-vecPrice.begin() << endl;

    vector<pair<long,int> > vecPricePos(vecPrice.size());
    for (vector<long>::iterator it = vecPrice.begin(); it != vecPrice.end(); ++it)
    {
        int pos = it - vecPrice.begin();
        vecPricePos[pos] = make_pair(*it,pos);
    }
    // sort based on value
    sort(vecPricePos.begin(), vecPricePos.end(), cmp);

    long minLoss = numeric_limits<long>::max();

    for (int i=vecPricePos.size()-1; i > 0; --i)
    {
        // case: Buying property at vecPricePos[i].first
        // Find the selling price which will lead to minimum loss for this buy value.
        for (int j = i-1; j >= 0; --j)
        {
            long loss = vecPricePos[i].first - vecPricePos[j].first;

            if (loss >= minLoss)
            {
                break; // No need to check further as loss isn't going to be minimized any further
            }
            if (vecPricePos[i].second < vecPricePos[j].second)
            {
                // Found a value which is later in position. Hence no need to look further as other values would have bigger loss.
                minLoss = min(minLoss, loss);
                break;
            }
        }

        if (minLoss == 1)
        {
            // lowest loss possible
            break;
        }
    }

    return minLoss;
}

int main() {
    // cout << "int max: " << numeric_limits<unsigned int>::max() << endl;
    // cout << "long max: " << numeric_limits<long>::max() << endl;
    int n;
    cin >> n;
    vector<long> price(n);
    for(int price_i = 0; price_i < n; price_i++){
       cin >> price[price_i];
    }
    int result = minimumLoss(price);
    cout << result << endl;
    return 0;
}

/***
Learning:
1. My solution is O(n*n) in worst case. Whereas the editorial shows how to do it in O(n*log n).
2. Use upper_bound of set for binary search
*/
