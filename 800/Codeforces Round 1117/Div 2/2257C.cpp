#include <iostream>
#include <vector>

using namespace std;

void solve()
{
    int n;
    if (!(cin >> n))
        return;

    vector<int> p(n + 1);
    for (int i = 2; i <= n; ++i)
    {
        cin >> p[i];
    }

    int m;
    cin >> m;
    vector<bool> is_dam(n + 1, false);
    for (int i = 0; i < m; ++i)
    {
        int a;
        cin >> a;
        is_dam[a] = true;
    }

    vector<vector<int>> free_children(n + 1);
    vector<int> camera_edges;

    for (int i = n; i >= 1; --i)
    {
        int count = (is_dam[i] ? 1 : 0) + static_cast<int>(free_children[i].size());
        bool has_free_dam = false;

        if (count > 0)
        {
            has_free_dam = true;
            if (count > 1)
            {
                if (is_dam[i])
                {

                    for (int child : free_children[i])
                    {
                        camera_edges.push_back(child);
                    }
                }
                else
                {

                    for (size_t j = 1; j < free_children[i].size(); ++j)
                    {
                        camera_edges.push_back(free_children[i][j]);
                    }
                }
            }
        }

        if (has_free_dam && i > 1)
        {
            free_children[p[i]].push_back(i);
        }
    }

    cout << camera_edges.size();
    for (int u : camera_edges)
    {
        cout << " " << u;
    }
    cout << "\n";
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