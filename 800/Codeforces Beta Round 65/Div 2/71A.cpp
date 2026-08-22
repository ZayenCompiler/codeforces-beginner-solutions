#include <iostream>
#include <string>
using namespace std;
int main()
{
    int testCase;
    cin >> testCase;
    while (testCase--)
    {
        string word;
        cin >> word;
        if (word.length() > 10)
        {
            int random;
            random = word.length() - 2;
            cout << word[0] << random << word[word.size() - 1] << "\n";
        }
        else
        {
            cout << word << "\n";
        }
    }

    return 0;
}