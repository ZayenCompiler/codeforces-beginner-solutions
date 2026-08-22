#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

using ll = long long;

const ll INF = (1LL << 62);

struct Matrix
{
    ll a[5][5];

    Matrix(int x, bool identity = false)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                a[i][j] = INF;
            }
        }

        if (identity)
        {
            for (int i = 0; i < x; i++)
                a[i][i] = 0;
        }
    }
};

int n, q, x;
int BLOCK_SIZE;
int numberOfBlocks;

vector<ll> d;
vector<ll> s;

Matrix multiply(const Matrix &A, const Matrix &B)
{
    Matrix C(x);

    for (int i = 0; i < x; i++)
    {
        for (int k = 0; k < x; k++)
        {
            if (A.a[i][k] == INF)
                continue;

            for (int j = 0; j < x; j++)
            {
                if (B.a[k][j] == INF)
                    continue;

                C.a[i][j] = min(
                    C.a[i][j],
                    A.a[i][k] + B.a[k][j]);
            }
        }
    }

    return C;
}

vector<ll> applyMatrix(const Matrix &M, const vector<ll> &v)
{
    vector<ll> result(x, INF);

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (M.a[i][j] == INF || v[j] == INF)
                continue;

            result[i] = min(
                result[i],
                M.a[i][j] + v[j]);
        }
    }

    return result;
}

Matrix createPlatformMatrix(ll length, ll penalty)
{
    Matrix M(x);

    for (int j = 0; j < x; j++)
    {

        ll target = length - x + 1 + j;

        for (int i = 0; i < x; i++)
        {

            ll source = -x + 1 + i;

            if (target <= 0)
            {
                if (target == source)
                    M.a[j][i] = 0;

                continue;
            }

            ll remaining = target - (i + 1);

            if (remaining <= 0)
            {
                M.a[j][i] = 0;
            }
            else
            {
                ll jumps = (remaining + x - 1) / x;
                M.a[j][i] = jumps * penalty;
            }
        }
    }

    return M;
}

vector<ll> initialState(ll length, ll penalty)
{
    vector<ll> state(x, INF);

    for (int j = 0; j < x; j++)
    {
        ll position = length - x + 1 + j;

        if (position <= 0)
        {
            state[j] = INF;
            continue;
        }

        ll distance = position - 1;

        ll jumps = (distance + x - 1) / x;

        state[j] = jumps * penalty;
    }

    return state;
}

vector<Matrix> segTree;

void rebuildBlock(int block)
{
    Matrix result(x, true);

    int left = block * BLOCK_SIZE;
    int right = min(n, left + BLOCK_SIZE);

    for (int i = left; i < right; i++)
    {
        Matrix current = createPlatformMatrix(d[i], s[i]);

        result = multiply(current, result);
    }

    segTree[numberOfBlocks + block] = result;
}

void updateBlockInSegmentTree(int block)
{
    int node = numberOfBlocks + block;

    segTree[node] = Matrix(x, true);

    int left = block * BLOCK_SIZE;
    int right = min(n, left + BLOCK_SIZE);

    for (int i = left; i < right; i++)
    {
        Matrix current = createPlatformMatrix(d[i], s[i]);

        segTree[node] = multiply(current, segTree[node]);
    }

    node /= 2;

    while (node >= 1)
    {

        segTree[node] =
            multiply(segTree[node * 2 + 1],
                     segTree[node * 2]);

        node /= 2;
    }
}

vector<ll> queryBlocks(
    int leftBlock,
    int rightBlock,
    vector<ll> state)
{
    if (leftBlock > rightBlock)
        return state;

    int L = leftBlock + numberOfBlocks;
    int R = rightBlock + numberOfBlocks;

    Matrix leftResult(x, true);
    Matrix rightResult(x, true);

    while (L <= R)
    {
        if (L % 2 == 1)
        {

            leftResult =
                multiply(segTree[L], leftResult);

            L++;
        }

        if (R % 2 == 0)
        {

            rightResult =
                multiply(rightResult, segTree[R]);

            R--;
        }

        L /= 2;
        R /= 2;
    }

    Matrix combined =
        multiply(rightResult, leftResult);

    return applyMatrix(combined, state);
}

ll query(int l, int r)
{

    vector<ll> state =
        initialState(d[l], s[l]);

    if (l == r)
        return state[x - 1];

    int firstPlatform = l + 1;

    int firstBlock = firstPlatform / BLOCK_SIZE;
    int lastBlock = r / BLOCK_SIZE;

    if (firstBlock == lastBlock)
    {
        for (int i = firstPlatform; i <= r; i++)
        {
            Matrix M =
                createPlatformMatrix(d[i], s[i]);

            state = applyMatrix(M, state);
        }

        return state[x - 1];
    }

    int endOfFirstBlock =
        min(n - 1,
            (firstBlock + 1) * BLOCK_SIZE - 1);

    for (int i = firstPlatform;
         i <= endOfFirstBlock;
         i++)
    {
        Matrix M =
            createPlatformMatrix(d[i], s[i]);

        state = applyMatrix(M, state);
    }

    int firstCompleteBlock = firstBlock + 1;
    int lastCompleteBlock = lastBlock - 1;

    if (firstCompleteBlock <= lastCompleteBlock)
    {
        state =
            queryBlocks(
                firstCompleteBlock,
                lastCompleteBlock,
                state);
    }

    int startOfLastBlock =
        lastBlock * BLOCK_SIZE;

    for (int i = startOfLastBlock;
         i <= r;
         i++)
    {
        Matrix M =
            createPlatformMatrix(d[i], s[i]);

        state = applyMatrix(M, state);
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

    BLOCK_SIZE = 100;

    numberOfBlocks =
        (n + BLOCK_SIZE - 1) / BLOCK_SIZE;

    int treeSize = 1;

    while (treeSize < numberOfBlocks)
        treeSize *= 2;

    vector<Matrix> actualTree(
        2 * treeSize,
        Matrix(x, true));

    segTree = move(actualTree);

    for (int block = 0;
         block < numberOfBlocks;
         block++)
    {
        int node = treeSize + block;

        Matrix result(x, true);

        int left = block * BLOCK_SIZE;
        int right =
            min(n, left + BLOCK_SIZE);

        for (int i = left; i < right; i++)
        {
            Matrix current =
                createPlatformMatrix(d[i], s[i]);

            result =
                multiply(current, result);
        }

        segTree[node] = result;
    }

    for (int node = treeSize - 1;
         node >= 1;
         node--)
    {
        segTree[node] =
            multiply(
                segTree[node * 2 + 1],
                segTree[node * 2]);
    }

    auto rebuildBlockFinal =
        [&](int block)
    {
        int node = treeSize + block;

        Matrix result(x, true);

        int left = block * BLOCK_SIZE;
        int right =
            min(n, left + BLOCK_SIZE);

        for (int i = left; i < right; i++)
        {
            Matrix current =
                createPlatformMatrix(d[i], s[i]);

            result =
                multiply(current, result);
        }

        segTree[node] = result;

        node /= 2;

        while (node >= 1)
        {
            segTree[node] =
                multiply(
                    segTree[node * 2 + 1],
                    segTree[node * 2]);

            node /= 2;
        }
    };

    auto queryCompleteBlocks =
        [&](int leftBlock,
            int rightBlock,
            vector<ll> state)
    {
        if (leftBlock > rightBlock)
            return state;

        int L = treeSize + leftBlock;
        int R = treeSize + rightBlock;

        Matrix leftResult(x, true);
        Matrix rightResult(x, true);

        while (L <= R)
        {
            if (L % 2 == 1)
            {
                leftResult =
                    multiply(
                        segTree[L],
                        leftResult);

                L++;
            }

            if (R % 2 == 0)
            {
                rightResult =
                    multiply(
                        rightResult,
                        segTree[R]);

                R--;
            }

            L /= 2;
            R /= 2;
        }

        Matrix combined =
            multiply(
                rightResult,
                leftResult);

        return applyMatrix(combined, state);
    };

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

            rebuildBlockFinal(block);
        }
        else if (type == '2')
        {

            --i;

            s[i] = v;

            int block =
                i / BLOCK_SIZE;

            rebuildBlockFinal(block);
        }
        else
        {

            int l = i - 1;
            int r = (int)v - 1;

            vector<ll> state =
                initialState(
                    d[l],
                    s[l]);

            if (l == r)
            {
                cout << state[x - 1] << '\n';
                continue;
            }

            int first = l + 1;

            int firstBlock =
                first / BLOCK_SIZE;

            int lastBlock =
                r / BLOCK_SIZE;

            if (firstBlock == lastBlock)
            {
                for (int p = first; p <= r; p++)
                {
                    Matrix M =
                        createPlatformMatrix(
                            d[p],
                            s[p]);

                    state =
                        applyMatrix(M, state);
                }

                cout << state[x - 1] << '\n';
                continue;
            }

            int firstBlockEnd =
                min(
                    n - 1,
                    (firstBlock + 1) *
                            BLOCK_SIZE -
                        1);

            for (int p = first;
                 p <= firstBlockEnd;
                 p++)
            {
                Matrix M =
                    createPlatformMatrix(
                        d[p],
                        s[p]);

                state =
                    applyMatrix(M, state);
            }

            int middleLeft =
                firstBlock + 1;

            int middleRight =
                lastBlock - 1;

            if (middleLeft <= middleRight)
            {
                state =
                    queryCompleteBlocks(
                        middleLeft,
                        middleRight,
                        state);
            }

            int lastBlockStart =
                lastBlock * BLOCK_SIZE;

            for (int p = lastBlockStart;
                 p <= r;
                 p++)
            {
                Matrix M =
                    createPlatformMatrix(
                        d[p],
                        s[p]);

                state =
                    applyMatrix(M, state);
            }

            cout << state[x - 1] << '\n';
        }
    }

    return 0;
}