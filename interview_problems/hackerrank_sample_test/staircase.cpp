#include <iostream>
#include <limits>

using namespace std;

void StairCase(int n)
{
    for (int i=1; i <= n; ++i)
    {
        // First print the spaces
        for (int j=1; j <= (n-i); ++j)
        {
            cout << " ";
        }
        // Now print the #
        for (int j=1; j<=i;++j)
        {
            cout << "#";
        }
        cout << " " << endl;
    }
}

int main() {
    int _n;
    cin >> _n;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

    // _n = 6;
    StairCase(_n);

    return 0;
}
