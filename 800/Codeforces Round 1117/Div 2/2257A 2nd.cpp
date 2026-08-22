#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>

using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;

    unordered_set<char> valid_chars;

    for (int i = 0; i < n; ++i)
    {
        string w;
        cin >> w;
        valid_chars.insert(toupper(w[0]));
    }

    bool possible = true;

    for (int i = 0; i < m; ++i)
    {
        string a;
        cin >> a;
        if (possible)
        {
            for (char c : a)
            {
                if (valid_chars.find(c) == valid_chars.end())
                {
                    possible = false;
                    break;
                }
            }
        }
    }

    if (possible)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
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