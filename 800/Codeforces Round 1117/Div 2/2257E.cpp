#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct StackItem
{
    long long C;
    long long delta;
    long long sum_delta;
    long long req_prefix;
};

struct PQItem
{
    long long C;
    long long delta;
    int proj;
    int job_idx;

    bool operator>(const PQItem &other) const
    {
        return C > other.C;
    }
};

void solve()
{
    int n;
    long long x;
    if (!(cin >> n >> x))
        return;

    vector<vector<StackItem>> macro_jobs(n);
    vector<vector<long long>> req(n);

    for (int i = 0; i < n; ++i)
    {
        int m;
        cin >> m;
        vector<long long> a(m), b(m);
        for (int j = 0; j < m; ++j)
            cin >> a[j];
        for (int j = 0; j < m; ++j)
            cin >> b[j];

        req[i].resize(m);
        vector<StackItem> st;

        for (int j = 0; j < m; ++j)
        {
            long long cur_C = a[j];
            long long cur_delta = b[j] - a[j];

            while (!st.empty())
            {
                StackItem top = st.back();
                if (top.delta <= 0 || (cur_delta >= 0 && cur_C <= top.C + top.delta))
                {
                    st.pop_back();
                    cur_C = max(top.C, cur_C - top.delta);
                    cur_delta = top.delta + cur_delta;
                }
                else
                {
                    break;
                }
            }

            long long prev_sum = st.empty() ? 0 : st.back().sum_delta;
            long long prev_req = st.empty() ? 0 : st.back().req_prefix;

            long long new_sum = prev_sum + cur_delta;
            long long new_req = max(prev_req, cur_C - prev_sum);

            st.push_back({cur_C, cur_delta, new_sum, new_req});
            req[i][j] = new_req;
        }

        macro_jobs[i] = st;
    }

    priority_queue<PQItem, vector<PQItem>, greater<PQItem>> pq;
    for (int i = 0; i < n; ++i)
    {
        if (!macro_jobs[i].empty() && macro_jobs[i][0].delta > 0)
        {
            pq.push({macro_jobs[i][0].C, macro_jobs[i][0].delta, i, 0});
        }
    }

    long long current_x = x;
    vector<long long> proj_gains(n, 0);

    while (!pq.empty())
    {
        auto top = pq.top();
        if (current_x >= top.C)
        {
            pq.pop();
            current_x += top.delta;
            proj_gains[top.proj] += top.delta;

            int next_idx = top.job_idx + 1;
            if (next_idx < (int)macro_jobs[top.proj].size() && macro_jobs[top.proj][next_idx].delta > 0)
            {
                pq.push({macro_jobs[top.proj][next_idx].C, macro_jobs[top.proj][next_idx].delta, top.proj, next_idx});
            }
        }
        else
        {
            break;
        }
    }

    int best_height = 0;
    int best_building = 1;

    for (int i = 0; i < n; ++i)
    {
        long long money_for_proj = current_x - proj_gains[i];

        int h = 0;
        int m = req[i].size();
        for (int j = 0; j < m; ++j)
        {
            if (money_for_proj >= req[i][j])
            {
                h = j + 1;
            }
            else
            {
                break;
            }
        }

        if (h > best_height)
        {
            best_height = h;
            best_building = i + 1;
        }
    }

    cout << best_height << " " << best_building << "\n";
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