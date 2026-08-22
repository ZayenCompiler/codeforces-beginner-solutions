#include <iostream>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n, w;
    // the cost of the first banana, initial number of dollars the soldier has and number of bananas he wants
    cin >> k >> n >> w;

    int sum = 0;

    for (int i = 1; i <= w; ++i)
    {
        sum += i * k;
    }

    int borrow = 0;

    if (sum > n)
    {
        borrow = sum - n;
        cout << borrow;
    }
    else
    {
        cout << "0";
    }

    return 0;
}