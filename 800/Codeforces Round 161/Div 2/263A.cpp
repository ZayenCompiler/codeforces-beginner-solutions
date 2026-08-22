#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int matrix[5][5];
    int row, col;

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            cin >> matrix[i][j];

            if (matrix[i][j] == 1)
            {
                row = i;
                col = j;
            }
        }
    }
    int count = abs(row - 2) + abs(col - 2);

    cout << count;

    return 0;
}