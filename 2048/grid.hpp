#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class grid
{
    int size;
    vector<vector<int> > square;
    int score;

public:
    grid();
    grid(int size);
    grid(vector<vector<int> > a);

    void pump_left();
    void pump_right();
    void pump_up();
    void pump_down();

    void move_left();
    void move_right();
    void move_up();
    void move_down();

    void random_add();
    void p_score();
    bool no_empty();
    bool try_move();
    //bool check_valid_move(char c);
    vector<vector<int> > get_data();

    friend void print(grid a);
    friend ostream &operator<<(ostream &out, grid a);
};

vector<vector<int> > grid::get_data()
{
    return square;
}

void grid::p_score()
{
    cout << " Final score : " << score << endl;
}
bool grid::no_empty()
{
    for (int i = 0; i < size * size; i++)
    {
        if (square[i / size][i % size] == 0)
        {
            return false;
        }
    }
    return true;
}
void print(grid a)
{
    cout << a;
    cout << "score : " << a.score << endl;
}

grid::grid()
{
    size = 1;
    square.clear();
    vector<int> a;
    a.push_back(0);
    square.push_back(a);
    score = 0;
}
grid::grid(int size)
{
    this->size = size;
    square.clear();
    vector<int> a;

    for (int i = 0; i < size; i++)
    {
        a.push_back(0);
    }
    for (int i = 0; i < size; i++)
    {
        square.push_back(a);
    }
    score = 0;
}
grid::grid(vector<vector<int> > a)
{
    this->square = a;
    size = a.size();
    score = 0;
}

void grid::move_left()
{
    vector<vector<int> > s;
    vector<int> a;
    a.clear();
    //创建新的grid
    for (int i = 0; i < size; i++)
    {
        a.push_back(0);
    }
    for (int i = 0; i < size; i++)
    {
        s.push_back(a);
    }
    //改
    for (int i = 0; i < size; i++)
    {
        int move = 0;
        for (int j = 0; j + move < size; j++)
        {
            if (square[i][j + move] != 0)
            {
                s[i][j] = square[i][j + move];
            }
            else
            {
                move++;
                j--;
            }
        }
        //a.clear();
    }
    this->square = s;
}

void grid::move_right()
{
    vector<vector<int> > s;
    vector<int> a;
    a.clear();
    //创建新的grid
    for (int i = 0; i < size; i++)
    {
        a.push_back(0);
    }
    for (int i = 0; i < size; i++)
    {
        s.push_back(a);
    }
    //改
    for (int i = 0; i < size; i++)
    {
        int move = 0;
        for (int j = size - 1; j - move >= 0; j--)
        {
            if (square[i][j - move] != 0)
            {
                s[i][j] = square[i][j - move];
            }
            else
            {
                move++;
                j++;
            }
        }
        //a.clear();
    }
    this->square = s;
}

void grid::move_up()
{
    vector<vector<int> > s;
    vector<int> a;
    a.clear();
    //创建新的grid
    for (int i = 0; i < size; i++)
    {
        a.push_back(0);
    }
    for (int i = 0; i < size; i++)
    {
        s.push_back(a);
    }
    //改
    for (int i = 0; i < size; i++)
    {
        int move = 0;
        for (int j = 0; j + move < size; j++)
        {
            if (square[j + move][i] != 0)
            {
                s[j][i] = square[j + move][i];
            }
            else
            {
                move++;
                j--;
            }
        }
        //a.clear();
    }
    this->square = s;
}

void grid::move_down()
{
    vector<vector<int> > s;
    vector<int> a;
    a.clear();
    //创建新的grid
    for (int i = 0; i < size; i++)
    {
        a.push_back(0);
    }
    for (int i = 0; i < size; i++)
    {
        s.push_back(a);
    }
    //改
    for (int i = 0; i < size; i++)
    {
        int move = 0;
        for (int j = size - 1; j - move >= 0; j--)
        {
            if (square[j - move][i] != 0)
            {
                s[j][i] = square[j - move][i];
            }
            else
            {
                move++;
                j++;
            }
        }
        //a.clear();
    }
    this->square = s;
}

void grid::pump_left()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (square[i][j] == square[i][j + 1])
            {
                score += square[i][j];
                square[i][j] *= 2;

                for (int k = j + 1; k < size; k++)
                {
                    if (k + 1 == size)
                    {
                        square[i][k] = 0;
                    }
                    else
                    {
                        square[i][k] = square[i][k + 1];
                    }
                }
            }
        }
    }
}
void grid::pump_right()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j >= 0; j--)
        {
            if (square[i][j] == square[i][j - 1])
            {
                score += square[i][j];
                square[i][j] *= 2;

                for (int k = j - 1; k >= 0; k--)
                {
                    if (k == 0)
                    {
                        square[i][k] = 0;
                    }
                    else
                    {
                        square[i][k] = square[i][k - 1];
                    }
                }
            }
        }
    }
}
void grid::pump_up()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (square[j][i] == square[j + 1][i])
            {
                score += square[j][i];
                square[j][i] *= 2;

                for (int k = j + 1; k < size; k++)
                {
                    if (k + 1 == size)
                    {
                        square[k][i] = 0;
                    }
                    else
                    {
                        square[k][i] = square[k + 1][i];
                    }
                }
            }
        }
    }
}
void grid::pump_down()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j > 0; j--)
        {
            if (square[j][i] == square[j - 1][i])
            {
                score += square[j][i];
                square[j][i] *= 2;
                for (int k = j - 1; k >= 0; k--)
                {
                    if (k == 0)
                    {
                        square[k][i] = 0;
                    }
                    else
                    {
                        square[k][i] = square[k - 1][i];
                    }
                }
            }
        }
    }
}

void grid::random_add()
{
    int random;
    int num = (rand() % 2 + 1) * 2;
    while (1)
    {
        random = rand() % (size * size);
        if (square[random / size][random % size] == 0)
        {
            square[random / size][random % size] = num;
            break;
        }
        else
        {
            continue;
        }
    }
}

bool grid::try_move()
{
    vector<vector<int> > temp = square;
    int temp_s = this->score;

    this->move_up();
    this->pump_up();
    if (temp_s != this->score)
    {
        return true;
    }

    square = temp;
    this->move_down();
    this->pump_down();
    if (temp_s != this->score)
    {
        return true;
    }

    square = temp;
    this->move_left();
    this->pump_left();
    if (temp_s != this->score)
    {
        return true;
    }

    square = temp;
    this->move_right();
    this->pump_right();
    if (temp_s != this->score)
    {
        return true;
    }
    square = temp;

    return false;
}
/*


bool grid::check_valid_move(char c)
{
    vector<vector<int> > temp = square;
    int temp_s = this->score;
    if (c == 'w')
    {

        this->move_up();
        this->pump_up();
        if (temp_s != this->score)
        {
            return true;
        }
    }
    else if (c == 's')
    {

        square = temp;
        this->move_down();
        this->pump_down();
        if (temp_s != this->score)
        {
            return true;
        }
    }
    else if (c == 'a')
    {

        square = temp;
        this->move_left();
        this->pump_left();
        if (temp_s != this->score)
        {
            return true;
        }
    }
    else if (c == 'd')
    {

        square = temp;
        this->move_right();
        this->pump_right();
        if (temp_s != this->score)
        {
            return true;
        }
        square = temp;
    }
    else
    {
        return false;
    }
}
*/