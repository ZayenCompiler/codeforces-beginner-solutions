#include <iostream>
#include <vector>

using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<long long> a(n), b(m);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < m; ++i)
        cin >> b[i];

    long long bea_needed = b[0] + m - 1;
    long long ver_needed = a[0] + n - 1;

    if (bea_needed <= ver_needed)
    {
        cout << 1 << "\n";
    }
    else
    {
        cout << 2 << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}