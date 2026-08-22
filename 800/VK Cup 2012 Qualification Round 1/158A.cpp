#include <iostream>

using namespace std;

int main()
{
    int k, n;
    cin >> n;
    cout << "";
    cin >> k;
    // k = the place of cut off anything above this is accepted to the next round

    int nextRound = 0;

    int arr[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    for (int j = 0; j < n; j++)
    {
        if (arr[j] >= arr[k - 1] && arr[j] > 0)
        {
            nextRound++;
        }
    }

    cout << nextRound;

    return 0;
}