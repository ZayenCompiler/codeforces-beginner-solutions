#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, a;
    cin >> n >> m >> a;

    long long stones_n = (n + a - 1) / a;
    long long stones_m = (m + a - 1) / a;

    cout << stones_n * stones_m;

    return 0;
}