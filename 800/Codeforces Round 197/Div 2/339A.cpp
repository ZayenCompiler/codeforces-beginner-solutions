#include <iostream>
#include <string>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string str;
    cin >> str;

    int ones = 0;
    int twos = 0;
    int threes = 0;

    for (char c : str)
    {
        if (c == '1')
            ones++;
        else if (c == '2')
            twos++;
        else if (c == '3')
            threes++;
    }

    bool first = true;

    for (int i = 0; i < ones; ++i)
    {
        if (!first)
            cout << '+';

        cout << '1';
        first = false;
    }

    for (int i = 0; i < twos; ++i)
    {
        if (!first)
            cout << '+';

        cout << '2';
        first = false;
    }

    for (int i = 0; i < threes; ++i)
    {
        if (!first)
            cout << '+';

        cout << '3';
        first = false;
    }

    cout << '\n';

    return 0;
}