#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

using int128 = __int128_t;

void print128(int128 n)
{
    if (n == 0)
    {
        cout << 0 << "\n";
        return;
    }
    string s = "";
    while (n > 0)
    {
        s += (char)('0' + (n % 10));
        n /= 10;
    }
    for (int i = (int)s.length() - 1; i >= 0; --i)
    {
        cout << s[i];
    }
    cout << "\n";
}

void solve()
{
    long long S;
    int q;
    if (!(cin >> S >> q))
        return;

    vector<long long> divs;
    for (long long i = 1; i * i <= S; ++i)
    {
        if (S % i == 0)
        {
            divs.push_back(i);
            if (i * i != S)
            {
                divs.push_back(S / i);
            }
        }
    }
    sort(divs.begin(), divs.end());

    int K = (int)divs.size();

    vector<int128> P(K + 1, 0);
    for (int i = 1; i <= K; ++i)
    {
        long long d_curr = divs[i - 1];
        long long d_prev = (i == 1) ? 0 : divs[i - 2];
        long long len = d_curr - d_prev;
        long long val = S / d_curr;
        P[i] = P[i - 1] + (int128)len * val;
    }

    while (q--)
    {
        long long x, y;
        cin >> x >> y;

        long long max_d = S / y;
        auto it = upper_bound(divs.begin(), divs.end(), max_d);
        int m = (int)(it - divs.begin());

        long long d_m = (m == 0) ? 0 : divs[m - 1];

        int128 ans = 0;

        long long part1_len = min(x, d_m);
        ans += (int128)part1_len * y;

        if (x > d_m)
        {

            auto it2 = lower_bound(divs.begin(), divs.end(), x);
            int p = (int)(it2 - divs.begin()) + 1;

            if (p > m)
            {

                ans += (P[p - 1] - P[m]);

                long long d_prev = (p == 1) ? 0 : divs[p - 2];
                long long partial_len = x - d_prev;
                long long val = S / divs[p - 1];
                ans += (int128)partial_len * val;
            }
        }

        print128(ans);
    }
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t)
    {
        while (t--)
        {
            solve();
        }
    }

    return 0;
}