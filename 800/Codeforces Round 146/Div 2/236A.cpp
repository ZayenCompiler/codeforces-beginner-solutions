#include <iostream>
#include <string>
#include <set>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string name;
    cin >> name;

    set<char> distinct_Letters;
    for (char c : name)
    {
        distinct_Letters.insert(c); // Sets ignore duplicates automatically
    }
    if (distinct_Letters.size() % 2 == 0)
    {
        cout << "CHAT WITH HER!";
    }
    else
    {
        cout << "IGNORE HIM!";
    }

    return 0;
}