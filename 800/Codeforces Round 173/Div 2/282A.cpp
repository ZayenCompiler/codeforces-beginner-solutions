#include <iostream>
#include <string>
using namespace std;

int main()
{
    int x = 0;
    string word;
    int number_of_statements;
    cin >> number_of_statements;

    while (number_of_statements--)
    {
        cin >> word;
        if (word == "X++")
        {
            x = x + 1;
        }
        else if (word == "--X")
        {
            --x;
        }
        else if (word == "++X")
        {
            ++x;
        }
        else if (word == "X--")
        {
            x = x - 1;
        }
    }
    cout << x;

    return 0;
}