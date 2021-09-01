#include <string>
#include <iostream>
#include <vector>
#include "board.hpp"
#include "sq_all.hpp"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <ctime>
#include <thread>
#include <string>
#include <curses.h>

using namespace std;

int length = 10;
int width = 10;
int move_speed = 0;
board myb(width, length);

void func1()
{
    char cmd;
    while (1)
    {
        //操作指示*************

        //*************
        myb.print();
        cin >> cmd;
        if (cin.eof())
        {
            break;
        }
        if (cmd == 'p')
        { //pause 暂停
            break;
        }
        else if ((cmd == 's') or (cmd == 'a') or (cmd == 'd'))
        {
            try
            {
                myb.move(cmd);
            }
            catch (string s)
            {
                cout << s << endl;
                break;
            }
        }
        else if (cmd == 'w')
        {
            myb.rotate();
        }
        else
        {
        }
        system("clear");
    }
}

void func2()
{
}

void test()
{
    myb.print();
    //myb.move();
}

int main()
{

    //welcome page
    cout << "************************";
    cout << "welcome Tetris\n";
    cout << "guideline:\n";
    cout << "a - move left\n";
    cout << "d - move right\n";
    cout << "s - move down fast\n";
    cout << "w - rotate the current shape\n";
    cout << "************************";

    myb.set_new_air();
    myb.filled_new_sq(width / 2 + width);

    func1();
    /*
    thread line1 (func1);
    thread line2 (func2);
    line1.join();
    line2.join();
    */
}