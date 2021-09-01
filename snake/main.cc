#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <ctime>
#include <thread>
#include "snake.hpp"
#include <string>
#include <curses.h>
using namespace std;

grid ten(20);

int stop_sign = 0;

int restart = 0;
void kep_mv()
{
    while (1)
    {
        //system(" ");
        if (stop_sign)
        {
            break;
        }
        try
        {
            ten.keep_move();
        }
        catch (int a)
        {
            cout << "game is over" << endl;
            cout << "enter any to quit" << endl;
            cout << "if want a new game, enter n" << endl;
            stop_sign = 1;
            break;
        }
        ten.print_grid();
        sleep_ms(400);
        system("clear");
    }
}

void cin_mv()
{
    while (1)
    {
        if (stop_sign)
        {
            break;
        }
        char a;
        cin >> a;
        if (a == 'n')
        {
            restart = 1;
            break;
        }
        if (a == 'p')
        {
            stop_sign = 1;
            break;
        }
        ten.change_dir(a);
        //sleep_ms(500);
    }
}

void testz()
{
    thread mv1(kep_mv);
    thread mv2(cin_mv);
    while (1)
    {
        if (stop_sign == 1)
        {
            break;
        }

        mv1.join();
        mv2.join();
        if (restart == 1)
        {
            continue;
        }
        else
        {
            break;
        }
    }
    //return 0;
}
void test1()
{
    string order = "ssaaaaasssssssssssssssssssss";
    int order_size = order.size();
    cout << "order_size " << order_size << endl;
    for (int i = 0; i < order_size - 1; i++)
    {
        cout << "towards  --- " << i << " ------ " << order[i] << endl;
        ten.snake_move(order[i]);
        ten.print_grid();
    }
}

int main()
{
    cout << "game start " << endl;
    cout << "w - up " << endl;
    cout << "s - down " << endl;
    cout << "a - left " << endl;
    cout << "d - right " << endl;
    cout << "there should \"enter\" after each command\n";
    sleep(1);
    cout << "enter any character to start" << endl;
    string start_sign;
    cin >> start_sign;
    system("clear");
    if (start_sign == "auto")
    {
        auto_move();
    }
    else
    {
        testz();
    }
    return 0;
}
