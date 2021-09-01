#include <stdlib.h>
#include <iostream>
#include <string>
#include "grid.hpp"
#include <vector>
#include "sleep_ms.hpp"
using namespace std;
void test1()
{
    
    cout << " _________________________________" << endl;
    cout << "|___|___|___|___|" << endl;
    cout << "|___|___|___|___|" << endl;
    cout << "|___|___|___|___|" << endl;
    cout << "|___|___|___|___|" << endl;
    char a;
    while (1)
    {
        cin >> a;
        if (a == 'w')
        {
            cout << "up" << endl;
        }
        else if (a == 's')
        {
            cout << "down" << endl;
        }
        else if (a == 'a')
        {
            cout << "left" << endl;
        }
        else if (a == 'd')
        {
            cout << "right" << endl;
        }
        else
        {
            cout << "re-enter" << endl;
            break;
        }
    }
}

ostream &operator<<(ostream &out, vector<int> a)
{
    int size = a.size();
    out << "|";
    for (int i = 0; i < size; i++)
    {

        if (a[i] == 0)
        {
            out << "_____|";
        }
        else if (a[i] < 10)
        {
            out << "__" << a[i] << "__|";
        }
        else if (a[i] < 100)
        {
            out << "_" << a[i] << "__|";
        }
        else if (a[i] < 1000)
        {
            out << "_" << a[i] << "_|";
        }
        else
        {
            out << "" << a[i] << "_|";
        }
    }
    out << endl;
    return out;
}

ostream &operator<<(ostream &out, grid a)
{
    int size = a.square.size();
    out << ' ';
    for (int i = 0; i < size; i++)
    {
        if (i == size - 1)
        {
            out << "___";
        }
        else
        {
            out << "____";
        }
    }
    out << endl;
    for (int i = 0; i < size; i++)
    {
        out << a.square[i];
    }
    return out;
}
/*

void test_move()
{
    vector<int> line1;
    line1.push_back(20);
    line1.push_back(2);
    line1.push_back(4);
    line1.push_back(4);

    vector<int> line2;
    line2.push_back(16);
    line2.push_back(2);
    line2.push_back(0);
    line2.push_back(0);

    vector<int> line3;
    line3.push_back(8);
    line3.push_back(2);
    line3.push_back(0);
    line3.push_back(0);

    vector<int> line4;
    line4.push_back(0);
    line4.push_back(2);
    line4.push_back(0);
    line4.push_back(0);

    vector<vector<int> > grid_44;
    grid_44.push_back(line1);
    grid_44.push_back(line2);
    grid_44.push_back(line3);
    grid_44.push_back(line4);

    grid myg(grid_44);
    cout << myg;
    myg.move_down();
    myg.pump_down();
    cout << myg;

    myg.move_up();
    cout << myg;

    myg.move_down();
    myg.pump_down();
    cout << myg;

    myg.move_up();
    cout << myg;

    myg.move_down();
    myg.pump_down();
    cout << myg;

    cout << myg;
}

void ran_add()
{
    grid myg(4);
    print(myg);
    myg.random_add();
    myg.random_add();
    myg.random_add();
    myg.random_add();
    myg.random_add();
    myg.random_add();
    myg.random_add();
    myg.random_add();
    myg.random_add();
    print(myg);
}
*/
void print_menu()
{
    system("clear");
    cout << "****************************" << endl;
    cout << "Welcome to 2048 " << endl;
    cout << "w - up" << endl;
    cout << "s - down" << endl;
    cout << "a - left" << endl;
    cout << "d - right" << endl;
    cout << "p - pause (stop the program)" << endl;
    cout << "****************************" << endl;
}
int main_test()
{
    char cmd;
    print_menu();
    cout << "Are you ready to start ? " << endl;
    cout << "Y-ready" << endl;
    while (cin >> cmd)
    {
        if (cmd == 'Y' or cmd == 'y')
        {
            break;
        }
    }
    cout << "Would you like to auto-play? Y-yes" << endl;
    char aut;
    cin >> aut;
    cout << "How large square would you want to play? eg. 4 denote 4x4\n";
    cout << "enter a numer: ";
    int size;
    cin >> size;
    grid myg(size);
    int check_invalid = 1;
    string wasd = "wasd";
    int clever_move = 0;
    while (1)
    {
        if (myg.no_empty() and !myg.try_move())
        {
            cout << "game over" << endl;
            myg.p_score();
            break;
        }

        if (!myg.no_empty() and check_invalid == 1)
        {
            myg.random_add();
        }
        print_menu();
        print(myg);
        if (aut == 'Y' or aut == 'y')
        {
            int c = rand() % 4;
            sleep_ms(100);
            cmd = wasd[c];
        }else if (aut == 'A' or aut == 'a')
        {
            sleep_ms(100);
            cmd = "sadw"[clever_move];
        }
        else
        {   
            cin >> cmd;
        }

        vector<vector<int> > temp = myg.get_data();
        if (cmd == 'w')
        {
            myg.move_up();
            myg.pump_up();
            check_invalid = 1;
        }
        else if (cmd == 's')
        {
            myg.move_down();
            myg.pump_down();
            check_invalid = 1;
        }
        else if (cmd == 'a')
        {
            myg.move_left();
            myg.pump_left();
            check_invalid = 1;
        }
        else if (cmd == 'd')
        {
            myg.move_right();
            myg.pump_right();
            check_invalid = 1;
        }
        else if (cmd == 'p')
        {
            break;
        }
        else
        {
            print_menu();
            check_invalid = 10;
        }
        if (temp == myg.get_data())
        {
            cout << "invalid move" << endl;
            
            check_invalid = 0;
            clever_move ++;
            clever_move  = clever_move %4;
        }else {
            clever_move = 0;
        }
        cout << "value - invalid move " << check_invalid << endl;
    }
    return 0;
}

int main()
{
    main_test();
}