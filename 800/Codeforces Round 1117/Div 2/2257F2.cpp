#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = (1LL << 60);

struct Matrix
{
    ll a[10][10];

    Matrix()
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                a[i][j] = INF;
            }
        }
    }
};

int n, q, x;

const int BLOCK_SIZE = 100;

int blocks;
int treeSize;

vector<ll> d;
vector<ll> s;

vector<Matrix> seg;

Matrix multiplyMatrix(const Matrix &A, const Matrix &B)
{
    Matrix C;

    for (int i = 0; i < x; i++)
    {
        for (int k = 0; k < x; k++)
        {
            if (A.a[i][k] >= INF)
                continue;

            for (int j = 0; j < x; j++)
            {
                if (B.a[k][j] >= INF)
                    continue;

                C.a[i][j] =
                    min(
                        C.a[i][j],
                        A.a[i][k] + B.a[k][j]);
            }
        }
    }

    return C;
}

Matrix identityMatrix()
{
    Matrix I;

    for (int i = 0; i < x; i++)
        I.a[i][i] = 0;

    return I;
}

void applyPlatform(
    const vector<ll> &in,
    vector<ll> &out,
    ll length,
    ll penalty)
{
    ll pref[10];
    ll suff[10];

    pref[0] = in[0];

    for (int i = 1; i < x; i++)
        pref[i] = min(pref[i - 1], in[i]);

    suff[x - 1] = in[x - 1];

    for (int i = x - 2; i >= 0; i--)
        suff[i] = min(suff[i + 1], in[i]);

    out.assign(x, INF);

    ll a = length / x;
    ll b = length % x;

    for (int j = 0; j < x; j++)
    {

        ll target = length - x + 1 + j;

        if (target <= 0)
        {
            int index =
                (int)(target + x - 1);

            if (index >= 0 && index < x)
                out[j] = in[index];

            continue;
        }

        ll t = b + j - 1;

        ll best = INF;

        ll hi = t - x;

        if (hi >= 0)
        {
            hi = min(hi, (ll)x - 1);

            best =
                min(
                    best,
                    pref[hi] + (a + 1) * penalty);
        }

        ll left =
            max(0LL, t - x + 1);

        ll right =
            min((ll)x - 1, t);

        if (left <= right)
        {

            ll minimum;

            if (left == 0)
                minimum = pref[right];
            else
                minimum = suff[left];

            best =
                min(
                    best,
                    minimum + a * penalty);
        }

        left = max(0LL, t + 1);

        if (left < x)
        {
            best =
                min(
                    best,
                    suff[left] +
                        (a - 1) * penalty);
        }

        out[j] = best;
    }
}

Matrix buildBlock(int block)
{
    Matrix result;

    int L = block * BLOCK_SIZE;
    int R = min(
        n,
        L + BLOCK_SIZE);

    for (int basis = 0; basis < x; basis++)
    {
        vector<ll> cur(x, INF);
        vector<ll> nxt;

        cur[basis] = 0;

        for (int i = L; i < R; i++)
        {
            applyPlatform(
                cur,
                nxt,
                d[i],
                s[i]);

            cur.swap(nxt);
        }

        for (int row = 0; row < x; row++)
        {
            result.a[row][basis] = cur[row];
        }
    }

    return result;
}

void rebuildBlock(int block)
{
    int node = treeSize + block;

    seg[node] = buildBlock(block);

    node /= 2;

    while (node >= 1)
    {

        seg[node] =
            multiplyMatrix(
                seg[node * 2 + 1],
                seg[node * 2]);

        node /= 2;
    }
}

vector<ll> applyMatrix(
    const Matrix &M,
    const vector<ll> &v)
{
    vector<ll> result(x, INF);

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (M.a[i][j] >= INF)
                continue;

            if (v[j] >= INF)
                continue;

            result[i] =
                min(
                    result[i],
                    M.a[i][j] + v[j]);
        }
    }

    return result;
}

Matrix queryBlocks(int L, int R)
{
    Matrix leftResult =
        identityMatrix();

    Matrix rightResult =
        identityMatrix();

    L += treeSize;
    R += treeSize;

    while (L <= R)
    {
        if (L & 1)
        {
            leftResult =
                multiplyMatrix(
                    seg[L],
                    leftResult);

            L++;
        }

        if (!(R & 1))
        {
            rightResult =
                multiplyMatrix(
                    rightResult,
                    seg[R]);

            R--;
        }

        L >>= 1;
        R >>= 1;
    }

    return multiplyMatrix(
        rightResult,
        leftResult);
}

vector<ll> initialState(
    ll length,
    ll penalty)
{
    vector<ll> state(x, INF);

    for (int j = 0; j < x; j++)
    {
        ll position =
            length - x + 1 + j;

        if (position <= 0)
            continue;

        ll distance =
            position - 1;

        ll jumps =
            (distance + x - 1) / x;

        state[j] =
            jumps * penalty;
    }

    return state;
}

ll solveQuery(int l, int r)
{

    vector<ll> state =
        initialState(
            d[l],
            s[l]);

    if (l == r)
        return state[x - 1];

    int firstPlatform = l + 1;

    int firstBlock =
        firstPlatform / BLOCK_SIZE;

    int lastBlock =
        r / BLOCK_SIZE;

    if (firstBlock == lastBlock)
    {
        vector<ll> nxt;

        for (int i = firstPlatform;
             i <= r;
             i++)
        {
            applyPlatform(
                state,
                nxt,
                d[i],
                s[i]);

            state.swap(nxt);
        }

        return state[x - 1];
    }

    int firstBlockEnd =
        min(
            n - 1,
            (firstBlock + 1) *
                    BLOCK_SIZE -
                1);

    vector<ll> nxt;

    for (int i = firstPlatform;
         i <= firstBlockEnd;
         i++)
    {
        applyPlatform(
            state,
            nxt,
            d[i],
            s[i]);

        state.swap(nxt);
    }

    int middleLeft =
        firstBlock + 1;

    int middleRight =
        lastBlock - 1;

    if (middleLeft <= middleRight)
    {
        Matrix middle =
            queryBlocks(
                middleLeft,
                middleRight);

        state =
            applyMatrix(
                middle,
                state);
    }

    int lastBlockStart =
        lastBlock * BLOCK_SIZE;

    for (int i = lastBlockStart;
         i <= r;
         i++)
    {
        applyPlatform(
            state,
            nxt,
            d[i],
            s[i]);

        state.swap(nxt);
    }

    return state[x - 1];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> x;

    d.resize(n);
    s.resize(n);

    for (int i = 0; i < n; i++)
        cin >> d[i];

    for (int i = 0; i < n; i++)
        cin >> s[i];

    blocks =
        (n + BLOCK_SIZE - 1) /
        BLOCK_SIZE;

    treeSize = 1;

    while (treeSize < blocks)
        treeSize <<= 1;

    seg.resize(
        2 * treeSize);

    for (int i = 0; i < 2 * treeSize; i++)
        seg[i] = identityMatrix();

    for (int block = 0;
         block < blocks;
         block++)
    {
        seg[treeSize + block] =
            buildBlock(block);
    }

    for (int node = treeSize - 1;
         node >= 1;
         node--)
    {
        seg[node] =
            multiplyMatrix(
                seg[node * 2 + 1],
                seg[node * 2]);
    }

    while (q--)
    {
        char type;
        int i;
        ll v;

        cin >> type >> i >> v;

        if (type == '1')
        {

            --i;

            d[i] = v;

            int block =
                i / BLOCK_SIZE;

            rebuildBlock(block);
        }
        else if (type == '2')
        {

            --i;

            s[i] = v;

            int block =
                i / BLOCK_SIZE;

            rebuildBlock(block);
        }
        else
        {

            int l = i - 1;
            int r = (int)v - 1;

            cout
                << solveQuery(l, r)
                << '\n';
        }
    }

    return 0;
}