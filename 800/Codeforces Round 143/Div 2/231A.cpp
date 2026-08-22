#include <iostream>

using namespace std;

int main()
{
    int friend_1;
    int friend_2;
    int friend_3;
    int testCase;
    cin >> testCase;

    int problemSolveable = 0;
    while (testCase--)
    {
        cin >> friend_1 >> friend_2 >> friend_3;
        if (friend_1 == 1 && friend_2 == 1 && friend_3 == 1)
        {
            problemSolveable++;
        }
        else if (friend_1 == 1 && friend_2 == 1)
        {
            problemSolveable++;
        }
        else if (friend_1 == 1 && friend_3 == 1)
        {
            problemSolveable++;
        }
        else if (friend_2 == 1 && friend_3 == 1)
        {
            problemSolveable++;
        }
    }
    cout << problemSolveable << "\n";

    return 0;
}