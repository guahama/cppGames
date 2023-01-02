#include <iostream>
#include <time.h>
using namespace std;

enum NUM
{
    NUM_0,
    NUM_1,
    NUM_2,
    NUM_3
};

int main(int argc, char const *argv[])
{
    srand((unsigned int)time(0));
    int numlist[9];
    for (int i = 0; i < 9; i++)
    {
        numlist[i] = i + 1;
    }
    for (int i = 0; i < 100; i++)
    {
        int a = rand() % 9;
        int b = rand() % 9;
        int tmp;

        tmp = numlist[a];
        numlist[a] = numlist[b];
        numlist[b] = tmp;
    }
    int AiPick[4];
    for (int i = 0; i < 4; i++)
    {
        AiPick[i] = numlist[i];
    }
    // for (int i = 0; i < 4; i++)
    // {
    //     cout << AiPick[i] << " ";
    // }
    // cout << endl;
    while (true)
    {
        int strikeCount = 0;
        int ballCount = 0;
        int playerPick[4];
        bool breaked = false;
        for (int i = 0; i < 4; i++)
        {
            int num;
            cin >> num;
            if (num <= 0 || num >= 10)
            {
                cout << "game end";
                breaked = true;
                break;
            }
            playerPick[i] = num;
        }
        if (breaked)
            break;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (playerPick[i] == AiPick[j])
                {
                    if (i == j)
                    {
                        strikeCount++;
                    }else
                    {
                        ballCount++;
                    }
                    break;
                }
            }
        }
        if (strikeCount == 0 && ballCount == 0)
        {
            cout << "Out" << endl;
        }else if (strikeCount == 4)
        {
            cout << "Win" << endl;
            break;
        }else
        {
            cout << strikeCount << "Strike" << ballCount << "Ball" << endl;
        }
    }
    return 0;
}

