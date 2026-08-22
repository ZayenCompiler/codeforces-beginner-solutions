#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    if ((m >= 1 && m <= 16) && (n >= 1 && n <= 16) && (m <= n))
    {
        cout << (m * n) / 2;
    }

    return 0;
}