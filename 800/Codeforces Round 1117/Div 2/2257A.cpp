#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    int testCase;
    cin >> testCase;

    while (testCase--)
    {
        int n, m;
        cin >> n >> m;

        bool letter_exists[26] = {false};

        for (int i = 0; i < n; i++)
        {
            string word;
            cin >> word;
            char first_letter = toupper(word[0]);
            letter_exists[first_letter - 'A'] = true;
        }

        bool possible = true;

        for (int i = 0; i < m; i++)
        {
            string abbreviation;
            cin >> abbreviation;

            for (int j = 0; j < abbreviation.length(); j++)
            {
                char ch = abbreviation[j];

                if (!letter_exists[ch - 'A'])
                {
                    possible = false;
                }
            }
        }

        if (possible)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }

    return 0;
}