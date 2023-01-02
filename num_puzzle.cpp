#include <iostream>
#include <time.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>
using namespace std;

char getche_linux() 
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    printf("%c", ch);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main(int argc, char const *argv[])
{
    srand((unsigned int)time(0));
    int nums[25] = {};
    for (int i = 0; i < 24; i++)
    {
        nums[i] = i + 1;
    }
    nums[24] = INT32_MAX;
    for (int i = 0; i < 24; i++)
    {
        int a = rand() % 24;
        int b = rand() % 24;
        int tmp;

        tmp = nums[a];
        nums[a] = nums[b];
        nums[b] = tmp;
    }

    while (true)
    {
        system("cls");
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (nums[i * 5 + j] == INT32_MAX)
                    cout << "*\t";
                else
                    cout << nums[i * 5 + j] << "\t";
            }
            cout << endl;
        }
        cout << "command : wasd, quit : q" << endl;
        char command = getche_linux();
        if (command == 'q')
            break;

        switch (command)
        {
        case 'w':
            break;
        case 'a':
            break;
        case 's':
            break;
        case 'd':
            break;
        
        default:
            break;
        }

    }
    
    

    return 0;
}
