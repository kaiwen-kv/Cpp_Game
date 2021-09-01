#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include "time_delay_ms.hpp"
#include <ctime>
#include <thread>
using namespace std;

class grid
{
    pair<int, int> food;
    vector<pair<int, int> > snake;
    int grid_size;
    char s_head_toward; //wasd
    int death;

public:
    grid();
    grid(int size);
    void change_food_position();
    void snake_move(char a); //wasd
    void print_grid();
    bool check_dir(char dir);
    void cin_move();
    void keep_move();
    void change_dir(char dir);
};

ostream &operator<<(ostream &out, vector<pair<int, int> > a)
{
    int size_a = a.size();
    for (int i = 0; i < size_a; i++)
    {
        out << '(' << a[i].first << ',' << a[i].second << ')';
    }
    return out;
}

void grid::change_dir(char dir)
{
    int s_size = snake.size();
    if ((dir != 'w') and (dir != 'a') and (dir != 's')and (dir != 'd')){
        return;
    }
    if (snake[s_size -1].first == snake[s_size - 2 ].first and (dir == 'a' or dir =='d')){
        return;
    }
    if (snake[s_size -1].second == snake[s_size - 2 ].second and (dir == 'w' or dir == 's')){
        return;
    }
    s_head_toward = dir;
}

void grid::keep_move()
{
    if (!check_dir(s_head_toward)){
        //throw 2;
    }
    snake_move(s_head_toward);
}

void grid::cin_move()
{
    char a;
    cin >> a;
    snake_move(a);
}

grid::grid()
{
    death = 0;
    grid_size = 7;
    for (int i = 0; i < 4; i++)
    {
        pair<int, int> body(3, i);
        snake.push_back(body);
    }
    s_head_toward = 'd';
    change_food_position();
}

grid::grid(int size)
{
    death = 0;
    grid_size = size;
    for (int i = 0; i < size / 2 + 1; i++)
    {
        pair<int, int> body(size / 2, i);
        snake.push_back(body);
    }
    s_head_toward = 'd';
    change_food_position();
}
void grid::change_food_position()
{
    int done = 0;
    while (1)
    {
        int g_s = grid_size * grid_size;
        int pos = rand() % g_s;
        food.first = pos / grid_size;
        food.second = pos % grid_size;
        int snake_size = snake.size();
        for (int i = 0; i < snake_size; i++)
        {
            if (food != snake[i])
            {
                if (i == snake_size - 1)
                {
                    done = 1;
                    break;
                }
                continue;
            }
            else
            {
                break;
            }
        }
        if (done == 1)
        {
            break;
        }
    }
}
void grid::snake_move(char a)
{

    pair<int, int> new_head;
    int snake_size = snake.size();
    if (a == 'w')
    {
        new_head.first = snake[snake_size - 1].first - 1;
        new_head.second = snake[snake_size - 1].second;

        if (new_head.first < 0)
        {
            new_head.first += grid_size;
        }
    }
    if (a == 'a')
    {
        new_head.first = snake[snake_size - 1].first;
        new_head.second = snake[snake_size - 1].second - 1;
        if (new_head.second < 0)
        {
            new_head.second += grid_size;
        }
    }
    if (a == 's')
    {
        new_head.first = snake[snake_size - 1].first + 1;
        new_head.second = snake[snake_size - 1].second;
        if (new_head.first >= grid_size)
        {
            new_head.first -= grid_size;
        }
    }
    if (a == 'd')
    {
        new_head.first = snake[snake_size - 1].first;
        new_head.second = snake[snake_size - 1].second + 1;
        if (new_head.second >= grid_size)
        {
            new_head.second -= grid_size;
        }
    }
    if (new_head == food) //吃
    {
        snake_size++;
        snake.push_back(new_head);
        this->change_food_position();

        return;
    }
    for (int i = 0; i < snake_size; i++)
    {
        if (snake[i] == new_head and (i != 0))
        {
            death = 1;
            cout << "throw 1 because (" << snake[i].first << ',' << snake[i].second << ") " << i << endl;
            throw 1;
        }
        if (i == snake_size - 1)
        {
            snake[i] = new_head;
        }
        else
        {

            snake[i] = snake[i + 1];
        }
    }
    s_head_toward = a;
}

bool grid::check_dir(char dir)

{
    s_head_toward = dir;
    pair<int, int> new_head;
    int snake_size = snake.size();
    if (dir == 'w')
    {
        new_head.first = snake[snake_size - 1].first - 1;
        new_head.second = snake[snake_size - 1].second;

        if (new_head.first < 0)
        {
            new_head.first += grid_size;
        }
    }
    if (dir == 'a')
    {
        new_head.first = snake[snake_size - 1].first;
        new_head.second = snake[snake_size - 1].second - 1;
        if (new_head.second < 0)
        {
            new_head.second += grid_size;
        }
    }
    if (dir == 's')
    {
        new_head.first = snake[snake_size - 1].first + 1;
        new_head.second = snake[snake_size - 1].second;
        if (new_head.first >= grid_size)
        {
            new_head.first -= grid_size;
        }
    }
    if (dir == 'd')
    {
        new_head.first = snake[snake_size - 1].first;
        new_head.second = snake[snake_size - 1].second + 1;
        if (new_head.second >= grid_size)
        {
            new_head.second -= grid_size;
        }
    }
    for (int i = 0; i < snake_size; i++)
    {

        if (snake[i] == new_head)
        {
            return false;
        }
    }
    return true;
}

void grid::print_grid()
{
    int s_size = snake.size();
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (i == food.first and j == food.second)
            {
                {
                    cout << "|s";
                }
            }
            else
            {
                for (int k = 0; k < s_size; k++)
                {
                    if (i != snake[k].first or j != snake[k].second)
                    {
                        if (k + 1 == s_size)
                        {
                            cout << "|_";
                        }
                    }
                    else
                    {
                        if (k + 1 == s_size)
                        {
                            cout << "|o";
                        }
                        else
                        {
                            cout << "|x";
                        }
                        break;
                    }
                }
            }
        }
        cout << "|\n";
    }
    cout << '\n';
}

void test()
{
    grid b(7);
    b.print_grid();
    char move;
    int times = 0;
    while (1)
    {
        times++;
        cout << "this is " << times << " th" << endl;
        cin >> move;
        sleep(1);
        system("clear");
        if (move == 'q')
        {
            break;
        }
        try
        {
            b.snake_move(move);
            b.print_grid();
        }
        catch (int stop)
        {
            cout << "invalid" << endl;
        }
    }
}

void auto_move()
{
    string toward = "wasd";
    grid b(7);
    b.print_grid();
    while (1)
    {
        if(!b.check_dir('w')and !b.check_dir('a')and !b.check_dir('s')and !b.check_dir('d')){
            cout << "no more move \ngame over\n";
            break;
        }
        char mv = toward[rand() % 4];
        if (b.check_dir(mv))
        {
            b.snake_move(mv);
        }
        else
        {
            continue;
        }
        
        b.print_grid();
        sleep_ms(100);
        system("clear");
    }
}

void man_move()
{
    grid b(7);
    b.print_grid();
    while (1)
    {
        try
        {
        }
        catch (int a)
        {
            cout << "game over" << endl;
            break;
        }
        b.print_grid();
        sleep_ms(100);
        system("clear");
    }
}
