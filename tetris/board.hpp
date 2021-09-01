#include <vector>
#include "square.hpp"
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

string all_type = "JLOTlZ";

ostream &operator<<(ostream &out, vector<int> a)
{
    int size = a.size();
    for (int i = 0; i < size; i++)
    {
        out << a[i] << ',';
    }
    return out;
}
class board
{

    vector<vector<square *> > data;
    vector<int> air_square;

    char air_type;
    int air_dir;
    char next_sq;
    int length;
    int width;
    int score;
    int game;
public:
    void filled_new_sq(int pos);
    board(int length, int width);
    void print();
    void set_new_air();
    void set_down();
    //void check_move();
    void move(char dirm);
    bool check_change();
    void rotate();
    void change();
    void print_next_shape();
    void print_score();
    bool game_over();
    void check_if_score();
    void check_if_score2();
    friend void print_out_vec(vector<int> a, int length);
    ~board();
};


void board::rotate()
{
    bool check = true;
    int size = air_square.size();
    vector<int> the_new_v;
    the_new_v.push_back(this->air_square[0]);

    int x1 = this->air_square[0] % this->width;
    int y1 = this->air_square[0] / this->width;
    for (int i = 1; i < size; i++)
    {
        int x2 = this->air_square[i] % this->width;
        int y2 = this->air_square[i] / this->width;
        int new_x = x1 - y1 + y2;
        int new_y = y1 - x2 + x1;
        if (abs(new_x - x2) > 4){
            return;
        }
        the_new_v.push_back(new_y * this->width + new_x);
    }
    for (int i = 0; i < size; i++)
    {
        int cur_pos = the_new_v[i];
        if (cur_pos >= width * (length + 3))
        {
            return;
        }
        if (cur_pos % width == 0 and air_square[i] % width == width - 1)
        {
            return;
        }
        if (cur_pos % width == width - 1 and air_square[i] % width == 0)
        {
            return;
        }
        int pass_continue = 0;
        for (int j = 0; j < size; j++)
        {
            if (cur_pos == air_square[j])
            {
                pass_continue = 1;
                break;
            }
        }
        if (pass_continue)
        {
            continue;
        }
        if (!data[cur_pos / width][cur_pos % width]->is_emp())
        {
            cout << "-z";
            return;
        }
    }

    //air_square[i] += width;

    for (int j = 0; j < size; j++)
    {
        int cur_pos = air_square[j];
        data[cur_pos / this->width][cur_pos % width] = new emp();
    }
    for (int j = 0; j < size; j++)
    {
        int cur_pos = the_new_v[j];
        data[cur_pos / width][cur_pos % width] = new emp(this->air_type);
    }
    this->air_square = the_new_v;
}

board::board(int length, int width)
{
    data.clear();
    vector<square *> temp;
    this->length = length;
    this->width = width;
    for (int j = 0; j < width; j++)
    {
        square *temp_sq = new emp;
        temp.push_back(temp_sq);
    }
    for (int i = 0; i < length + 3; i++)
    {
        data.push_back(temp);
    }
    air_dir = 0;
    air_type = all_type[rand() % 6];
    next_sq = all_type[rand() % 6];
    //filled_new_sq(width / 2);
    //这里初始就加一个块
}

void board::filled_new_sq(int pos)
{
    air_square.clear();
    air_square.push_back(pos);
    if (air_type == 'L')
    {
        air_square.push_back(pos + width);
        air_square.push_back(pos - width);
        air_square.push_back(pos + width + 1);
    }
    else if (air_type == 'J')
    {
        air_square.push_back(pos + width);
        air_square.push_back(pos - width);
        air_square.push_back(pos + width - 1);
    }
    else if (air_type == 'O')
    {
        air_square.push_back(pos + width);
        air_square.push_back(pos + width + 1);
        air_square.push_back(pos + 1);
    }
    else if (air_type == 'l')
    {
        air_square.push_back(pos - width);
        air_square.push_back(pos + width);
        air_square.push_back(pos - width * 2);
    }
    else if (air_type == 'T')
    {
        air_square.push_back(pos - width);
        air_square.push_back(pos - 1);
        air_square.push_back(pos + 1);
    }
    else if (air_type == 'Z')
    {
        air_square.push_back(pos - 1);
        air_square.push_back(pos + width);
        air_square.push_back(pos + width + 1);
    }
    else if (air_type == 'N') //反Z
    {
        air_square.push_back(pos + 1);
        air_square.push_back(pos - width);
        air_square.push_back(pos - width - 1);
    }
    else
    {
    }
    int size = air_square.size();
    for (int i = 0; i < size; i++)
    {
        if (air_square[i] >= (width * (length + 3)))
        {
            continue;
            cout << "here";
        }
        if (air_square[i] < 0)
        {
            continue;
            cout << "here";
        }
        data[air_square[i] / width][air_square[i] % width] = new emp(this->air_type);
    }

    return;
}


void board::set_down()
{
    int s_air = air_square.size();
    cout << "s_air = " << s_air << endl;
    if (length == 0)
    {
        return;
    }
    for (int i = 0; i < s_air; i++)
    {
        if (data[air_square[i] / width][air_square[i] % width]->is_emp())
        {
            cout << i;
            cout << "  game \n";
            return;
        }
        cout << "(" << air_type << ")";
        data[air_square[i] / width][air_square[i] % width] = new emp(air_type);
    }
    air_type = next_sq;
    //srand(time(NULL));
    next_sq = all_type[rand() % 6];
    air_dir = 0;
    //filled_new_sq(width / 2 + width);
}


void board::set_new_air()
{
    int s_air = air_square.size();
    cout << "s_air = " << s_air << endl;
    if (length == 0)
    {
        return;
    }
    for (int i = 0; i < s_air; i++)
    {
        if (data[air_square[i] / width][air_square[i] % width]->is_emp())
        {
            cout << i;
            cout << "  game \n";
            return;
        }
        cout << "(" << air_type << ")";
        data[air_square[i] / width][air_square[i] % width] = new emp(air_type);
    }
    air_type = next_sq;
    //srand(time(NULL));
    next_sq = all_type[rand() % 6];
    air_dir = 0;
    filled_new_sq(width / 2 + width);
}

void board::move(char dirm)
{
    bool check = true;
    int size = air_square.size();
    int towards;
    if (dirm == 's')
    {
        towards = width;
    }
    else if (dirm == 'd')
    {
        towards = 1;
    }
    else if (dirm == 'a')
    {
        towards = -1;
    }
    else
    {
        towards = 0;
    }
    for (int i = 0; i < size; i++)
    {
        int cur_pos = air_square[i] + towards;
        if (cur_pos >= width * (length + 3))
        {

            set_down();
            check_if_score2();
            game_over();
            filled_new_sq(width / 2 + width);

            return;
        }
        if (cur_pos % width == 0 and air_square[i] % width == width - 1)
        {
            return;
        }
        if (cur_pos % width == width - 1 and air_square[i] % width == 0)
        {
            return;
        }
        int pass_continue = 0;
        for (int j = 0; j < size; j++)
        {
            if (cur_pos == air_square[j])
            {
                pass_continue = 1;
                break;
            }
        }
        if (pass_continue)
        {
            continue;
        }
        if (!data[cur_pos / width][cur_pos % width]->is_emp())
        {
            if (dirm == 'd' or dirm == 'a'){
                return ;
            }
            cout << air_square;
            set_down();
            check_if_score2();
            game_over();
            filled_new_sq(width / 2 + width);
            return;
        }
    }

    //air_square[i] += width;

    for (int j = 0; j < size; j++)
    {
        int cur_pos = air_square[j];
        data[cur_pos / this->width][cur_pos % width] = new emp();
    }
    for (int j = 0; j < size; j++)
    {
        air_square[j] += towards;
        int cur_pos = air_square[j];
        data[cur_pos / width][cur_pos % width] = new emp(this->air_type);
    }
}
/*
void board::move()
{
    if (length == 0)
    {
        return;
    }
    vector<vector<square *> > temp_data = data;
    vector<int> temp_air_square = air_square;
    int size_temp_air_square = temp_air_square.size();
    for (int k = 0; k < size_temp_air_square; k++)
        {

            int pos_temp = temp_air_square[k];
            temp_data[pos_temp / width][pos_temp % width] = new emp();
        }
    bool check = true;
    for (int k = 0; k < size_temp_air_square; k++)
    {

        int pos_temp = temp_air_square[k] + width;
        if (pos_temp >= width * length)
        {
            check = false;
            cout << 'x';
            break;
        }
        if (!temp_data[pos_temp / width][pos_temp % width]->is_emp())
        {
            check = false;
            cout << 'i';
            break;
        }
    }

    if (check == true)
    {
        
        air_square = temp_air_square;
        for (int k = 0; k < size_temp_air_square; k++)
        {
            temp_air_square[k]= temp_air_square[k]+width;
            int pos_temp = temp_air_square[k];
            cout << "pos"<<pos_temp<<endl;
            temp_data[pos_temp / width][pos_temp % width] = new emp(this->air_type);
        }
        //data = temp_data;
    }
}


*/

void board::print_next_shape()
{
    if (next_sq == 'l')
    {
        cout << " l\n l\n l\n l" << endl;
    }
    else if (next_sq == 'L')
    {
        cout << " L\n L\n LL" << endl;
    }
    else if (next_sq == 'O')
    {
        cout << " OO\n OO" << endl;
    }
    else if (next_sq == 'Z')
    {
        cout << "ZZ\n ZZ" << endl;
    }
    else if (next_sq == 'T')
    {
        cout << " TTT\n T" << endl;
    }
    else if (next_sq == 'T')
    {
        cout << " TTT\n T" << endl;
    }
    else if (next_sq == 'T')
    {
        cout << " TTT\n T" << endl;
    }
    else
    {
    }
}

bool board::check_change()
{
    return true;
}
void board::change()
{
}

void board::print()
{
    this->print_score();
    if (length == 0)
    {
        return;
    }

    for (int i = 3; i < length + 3; i++)
    {
        if (i == 3)
        {
            //cout << "------------\n";
        }
        for (int j = 0; j < width; j++)
        {

            data[i][j]->print();
            //cout << "p";
        }
        //if (i = 2)
        cout << endl;
    }
    this->print_next_shape();
}
bool board::game_over()
{
    for (int i = 0; i < 4; i++)
    {
        if (air_square[i] < 3 * width)
        {
            return true;
        }
    }
    return false;
}
void board::print_score(){
    cout << "Your score is : " << score<<endl;
}

void board::check_if_score()
{
    int size = air_square.size();
    vector<square *> nw;
    for (int s = 0; s < width; s++)
    {
        nw.push_back(new emp());
    }
    for (int i = 0; i < size; i++)
    {
        int line = air_square[i] / width;
        int pass_continue = 0;
        for (int j = 0; j < width; j++)
        {
            if (data[line][j]->is_emp())
            {
                pass_continue = 1;
            }
            break;
        }
        if (pass_continue)
        {
            continue;
        }
        score++;
        //data.erase(data.begin() + line);
        //data.push_back(nw);
        for (int p = i; p > 0; p--)
        {
            data[p] = data[p - 1];
        }
        data[0] = nw;
    }
}

void board::check_if_score2()
{
    for (int i = length + 2; i > 0; i--)
    {
        int pass_continue = 0;
        for (int j = 0; j < width; j++)
        {

            if (!data[i][j]->is_emp())
            {
                continue;
            }
            else
            {
                pass_continue = 1;
                break;
            }
        }
        if (pass_continue == 1)
        {
            continue;
        }
        score ++;
        for (int j = i; j > 0; j--)
        {
            data[j] = data[j - 1];
        }
        for (int j = 0; j < width; j++)
        {
            data[0][j]->set_zero();
        }
        i ++;
    }
}

board::~board() {}

void print_out_vec(vector<int> a, int length)
{
    int size = a.size();
    for (int i = 0; i < size; i++)
    {
        cout << '[' << a[i] / length << '/' << a[i] % length << ']';
    }
}
