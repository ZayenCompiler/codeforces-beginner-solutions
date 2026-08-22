#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string one;
    cin >> one;

    string two;
    cin >> two;

    for (int i = 0; i < one.length(); ++i)
    {
        char a = tolower(one[i]);
        char b = tolower(two[i]);

        if (a < b)
        {
            cout << "-1";
            return 0;
        }
        else if (b < a)
        {
            cout << "1";
            return 0;
        }
    }

    cout << "0";

    return 0;
}