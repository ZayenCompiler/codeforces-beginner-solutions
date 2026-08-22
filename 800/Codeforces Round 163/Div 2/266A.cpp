#include <iostream>
#include <string>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    string colour;
    cin >> colour;

    int count_R = 0;
    int count_G = 0;
    int count_B = 0;

    for (int i = 0; i < N - 1; ++i)
    {
        if (colour[i] == 'R' && colour[i + 1] == 'R')
        {
            count_R++;
        }
        else if (colour[i] == 'G' && colour[i + 1] == 'G')
        {
            count_G++;
        }
        else if (colour[i] == 'B' && colour[i + 1] == 'B')
        {
            count_B++;
        }
    }

    cout << count_R + count_G + count_B;

    return 0;
}