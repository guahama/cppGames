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
        cout << "pick your number";
        cout << endl;
        cout << bingoCount << endl;
        cin >> number;

        if (number == 0)
        {
            cout << "game end" << endl;
            break;
        }else if (number < 1 || number > 25)
        {
            cout << "wrong number" << endl;
            continue;
        }
        bool is_checked = true;
        for (int i = 0; i < 25; i++)
        {
            if (map[i] == number)
            {
                is_checked = false;
                map[i] = INT32_MAX;
                if (i % 6 == 0)
                {
                    bool is_bingo = true;
                    for (int j = 0; j < 5; j++)
                    {
                        if (map[j * 6] != INT32_MAX)
                        {
                            is_bingo = false;
                            break;
                        }
                    }
                    if (is_bingo)
                        bingoCount++;
                }
                if (i % 4 == 0 && i != 24 && i != 0)
                {
                    bool is_bingo = true;
                    for (int j = 1; j < 6; j++)
                    {
                        if (map[j * 4] != INT32_MAX)
                        {
                            is_bingo = false;
                            break;
                        }
                    }
                    if (is_bingo)
                        bingoCount++;
                }
                int row = i % 5;
                int col = i / 5;
                bool is_bingo = true;
                for (int j = 0; j < 5; j++)
                {
                    if (map[row + j] != INT32_MAX)
                    {
                        is_bingo = false;
                        break;
                    }
                }
                if (is_bingo)
                    bingoCount++;
                is_bingo = true;
                for (int j = 0; j < 5; j++)
                {
                    if (map[col + j * 5] != INT32_MAX)
                    {
                        is_bingo = false;
                        break;
                    }
                }
                if (is_bingo)
                    bingoCount++;
                break;
            }
            system("clear");
        }
        if (is_checked)
        {
            cout << "already selected" << endl;
            continue;
        }
        if (bingoCount > 4)
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
