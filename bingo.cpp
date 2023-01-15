#include <iostream>
#include <time.h>
#include <termios.h>
#include <curses.h>
#include <unistd.h>
using namespace std;

enum AI_MODE
{
    AI_EASY = 1,
    AI_HARD
};

enum LINE_NUMBER
{
    LN_R1,
    LN_R2,
    LN_R3,
    LN_R4,
    LN_R5,
    LN_C1,
    LN_C2,
    LN_C3,
    LN_C4,
    LN_C5,
    LN_RT,
    LN_LT,  
};

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
    int AImap[25];
    srand((unsigned int)time(0));
    for (int i = 0; i < 25; i++)
    {
        map[i] = i + 1;
        AImap[i] = i + 1;
    }
    for (int i = 0; i < 100; i++)
    {
        int idx1 = rand() % 25;
        int idx2 = rand() % 25;
        int tmp = map[idx1];
        map[idx1] = map[idx2];
        map[idx2] = tmp;

        idx1 = rand() % 25;
        idx2 = rand() % 25;
        tmp = AImap[idx1];
        AImap[idx1] = AImap[idx2];
        AImap[idx2] = tmp;
    }
    int bingoCount = 0;
    int AIBingoCount = 0;
    int AImode;
    while (true)
    {
        cout << "1. EASY" << endl;
        cout << "2. HARD" << endl;
        cout << "choose AI mode : ";
        
        cin >> AImode;

        if (AImode >= AI_EASY && AImode <= AI_HARD)
        {
            break;
        }
    }

    int nonSelected[25] = {};
    int nonSelectedCount = 0;


    while (true)
    {
        system("clear");

        int number;
        cout << "=========Player========" << endl;
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
        cout << endl;
        cout << "=========AI========" << endl;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (AImap[i * 5 + j] != INT32_MAX)
                {
                    cout << AImap[i * 5 + j] << "\t";
                }else
                {
                    cout << "*\t";
                }
                
            }
            cout << endl;
        }
        cout << "AIbingo Count : " << AIBingoCount << endl;
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
            for (int i = 0; i < 25; i++)
            {
                if (AImap[i] == number)
                {
                    AImap[i] = INT32_MAX;
                    break;
                }
            }
            if (bacc)
            {
                cout << "overlaped number" << endl;
                continue;
            }
        }

        switch(AImode)
        {
            case AI_EASY:
            {
                nonSelectedCount = 0;
                for (int i = 0; i < 25; i++)
                {
                    if (AImap[i] != INT32_MAX)
                    {
                        nonSelected[nonSelectedCount] = AImap[i];
                        nonSelectedCount++;
                    }
                }
                number = nonSelected[rand() % nonSelectedCount];
                break;

            }
            case AI_HARD:
            {
                int line = 0;
                int starCount = 0;
                int maxCount = 0;

                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        starCount = 0;
                        if (AImap[i * 5 + j] == INT32_MAX)
                        {
                            starCount++;
                        }  
                    }
                    if (starCount < 5 && maxCount < starCount)
                    {
                        maxCount = starCount;
                        line = i;
                    }
                    
                }
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        starCount = 0;
                        if (AImap[j * 5 + i] == INT32_MAX)
                        {
                            starCount++;
                        }  
                    }
                    if (starCount < 5 && maxCount < starCount)
                    {
                        maxCount = starCount;
                        line = i + 5;
                    }
                    
                }
                starCount = 0;
                for (int i = 0; i < 25; i += 6)
                {
                    if (AImap[i] == INT32_MAX)
                    {
                        starCount++;
                    }
                }
                if (starCount < 5 && maxCount < starCount)
                {
                    maxCount = starCount;
                    line = LN_LT;
                }
                starCount = 0;
                for (int i = 4; i < 24; i += 4)
                {
                    if (AImap[i] == INT32_MAX)
                    {
                        starCount++;
                    }
                }
                if (starCount < 5 && maxCount < starCount)
                {
                    maxCount = starCount;
                    line = LN_RT;
                }

                if (line <= LN_R5)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (AImap[line * 5 + i] != INT32_MAX)
                        {
                            number = AImap[line * 5 + i];
                            break;
                        }
                    }
                }else if (line <= LN_C5)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (AImap[line - 5 + (i * 5)] != INT32_MAX)
                        {
                            number = AImap[line * 5 + i];
                            break;
                        }
                    }
                }else if (line == LN_LT)
                {
                    for (int i = 0; i < 25; i += 6)
                    {
                        if (AImap[i] != INT32_MAX)
                        {
                            number = AImap[i];
                            break;
                        }
                    }
                }else
                {
                    for (int i = 4; i < 24; i += 4)
                    {
                        if (AImap[i] != INT32_MAX)
                        {
                            number = AImap[i];
                            break;
                        }
                    }
                }
                break;
            }
        }
        for (int i = 0; i < 25; i++)
            {
                if (map[i] == number)
                {
                    map[i] = INT32_MAX;
                    break;
                }
            }
            for (int i = 0; i < 25; i++)
            {
                if (AImap[i] == number)
                {
                    AImap[i] = INT32_MAX;
                    break;
                }
            }

        bingoCount = 0;
        AIBingoCount = 0;
        int rowCheck = 0, colCheck = 0;
        int AIrowCheck = 0, AIcolCheck = 0;
        for (int i = 0; i < 5; i++)
        {
            rowCheck = colCheck = 0;
            AIrowCheck = AIcolCheck = 0;
            for (int j = 0; j < 5; j++)
            {
                if (map[i * 5 + j] == INT32_MAX)
                    rowCheck++;
                if (AImap[i * 5 + j] == INT32_MAX)
                    AIrowCheck++;
            }
            if (rowCheck == 5)
                bingoCount++;
            if (AIrowCheck == 5)
                AIBingoCount++;
            for (int j = 0; j < 5; j++)
            {
                if (map[j * 5 + i] == INT32_MAX)
                    colCheck++;
                if (AImap[j * 5 + i] == INT32_MAX)
                    AIcolCheck++;
            }
            if (colCheck == 5)
                bingoCount++;
            if (AIcolCheck == 5)
                AIBingoCount++;
        }
        int diaCount = 0;
        int AIdiaCount = 0;
        for (int i = 0; i < 25; i += 6)
        {
            if (map[i] == INT32_MAX)
            {
                diaCount++;
            }
            if (AImap[i] == INT32_MAX)
            {
                AIdiaCount++;
            }
        }
        if (diaCount == 5)
        {
            bingoCount++;
        }
        if (AIdiaCount == 5)
        {
            AIBingoCount++;
        }
        diaCount = 0;
        AIdiaCount = 0;
        for (int i = 4; i < 24; i += 4)
        {
            if (map[i] == INT32_MAX)
            {
                diaCount++;
            }
            if (AImap[i] == INT32_MAX)
            {
                AIdiaCount++;
            }
        }
        if (diaCount == 5)
        {
            bingoCount++;
        }
        if (AIdiaCount == 5)
        {
            AIBingoCount++;
        }
        if (bingoCount > 4)
        {
            cout << "you win!";
            break;
        }else if (AIBingoCount > 4)
        {
            cout << "you lose";
            break;
        }

    }
    return 0;
}
