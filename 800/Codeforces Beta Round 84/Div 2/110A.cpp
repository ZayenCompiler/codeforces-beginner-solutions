#include <iostream>
#include <string>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string n;
    cin >> n;

    int count = 0;

    for (char digit : n)
    {
        if (digit == '4' || digit == '7')
        {
            count++;
        }
    }

    if (count == 4 || count == 7)
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }

    return 0;
}