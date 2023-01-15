#include <iostream>
#include <time.h>
#include <termios.h>
#include <curses.h>
#include <unistd.h>
using namespace std;

int getche_linux() 
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}


int main(int argc, char const *argv[])
{
    int map[25];
    srand((unsigned int)time(0));
    for (int i = 0; i < 25; i++)
    {
        map[i] = i + 1;
    }
    for (int i = 0; i < 100; i++)
    {
        int idx1 = rand() % 25;
        int idx2 = rand() % 25;
        int tmp = map[idx1];
        map[idx1] = map[idx2];
        map[idx2] = tmp;
    }
    int bingoCount = 0;
    while (true)
    {
        int number;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (map[i * 5 + j] != INT32_MAX)
                {
                    cout << map[i * 5 + j] << "\t";
                }else
                {
                    cout << "*\t";
                }
                
            }
            cout << endl;
        }
        cout << "bingo Count : " << bingoCount << endl;
        cout << "pick your number" << endl;
        cin >> number;

        if (number == 0)
        {
            cout << "game end" << endl;
            break;
        }else if (number < 1 || number > 25)
        {
            cout << "wrong number" << endl;
            continue;
        }else
        {
            bool bacc = true;
            for (int i = 0; i < 25; i++)
            {
                if (map[i] == number)
                {
                    map[i] = INT32_MAX;
                    bacc = false;
                    break;
                }
            }
            if (bacc)
            {
                cout << "overlaped number" << endl;
                continue;
            }
        }

        bingoCount = 0;
        int rowCheck = 0, colCheck = 0;
        for (int i = 0; i < 5; i++)
        {
            rowCheck = colCheck = 0;
            for (int j = 0; j < 5; j++)
            {
                if (map[i * 5 + j] == INT32_MAX)
                    rowCheck++;
            }
            if (rowCheck == 5)
            bingoCount++;
            for (int j = 0; j < 5; j++)
            {
                if (map[j * 5 + i] == INT32_MAX)
                    colCheck++;
            }
            if (colCheck == 5)
            bingoCount++;
        }
        int diaCount = 0;
        for (int i = 0; i < 25; i += 6)
        {
            if (map[i] == INT32_MAX)
            {
                diaCount++;
            }
        }
        if (diaCount == 5)
        {
            bingoCount++;
        }
        diaCount = 0;
        for (int i = 4; i < 24; i += 4)
        {
            if (map[i] == INT32_MAX)
            {
                diaCount++;
            }
        }
        if (diaCount == 5)
        {
            bingoCount++;
        }
        if (bingoCount >= 5)
        {
            break;
        }
        

    }
    if (bingoCount > 4)
    {
        cout << "you win!";
    }else
    {
        cout << "you lose";
    }

    return 0;
}
