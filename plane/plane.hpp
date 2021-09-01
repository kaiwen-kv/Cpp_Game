#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class grid
{
    int size_h;
    int size_l;
    int score;
    int plane_pos; //1- 2 * size_l -2
    int arm_p;
    vector<pair<int, int> > my_bul;
    vector<int> arm_pos;

public:
    grid();
    grid(int h, int l);
    void move_plane(char d); //wasd
    //void random_army();
    void add_my_bul();
    void clear_out();
    void move_bul();
    void random_army_move();
    void check_army_crash();
    friend ostream &operator<<(ostream &out, grid a);
};
grid::grid()
{
    score= 0;
    size_h = 10;
    size_l = 20;
    plane_pos = 1;
    //arm_pos.push_back(-1);
    //arm_pos.push_back(-1);
    //arm_pos.push_back(-1);
}
void grid::add_my_bul()
{
    int size = my_bul.size();
    pair<int, int> n_b(size_h - 2, plane_pos);
    if (size == 0 or my_bul[size - 1] != n_b)
    {
        my_bul.push_back(n_b);
        cout << "pt bull success" << endl;
    }
}

void grid::clear_out()
{
    vector<pair<int, int> > old_my_bul = my_bul;
    int size = my_bul.size();
    my_bul.clear();
    for (int i = 0; i < size; i++)
    {
        if (old_my_bul[i].first >= 0)
        {
            my_bul.push_back(old_my_bul[i]);
        }
    }
}

void grid::move_bul()
{
    int size = my_bul.size();
    for (int i = 0; i < size; i++)
    {
        my_bul[i].first--;
    }
}

grid::grid(int h, int l)
{
    score= 0;
    size_h = h;
    size_l = l;
    plane_pos = 1;
    arm_p =rand()% (size_l - 2) + 1;
    //arm_pos.push_back(-1);
    //arm_pos.push_back(-1);
    //arm_pos.push_back(-1);
}

void grid::move_plane(char d) //a-left  d-right
{

    if (d == 'a')
    {
        if (plane_pos - 1 > 0)
        {
            plane_pos--;
        }
    }
    else if (d == 'd')
    {
        if (plane_pos + 1 < size_l - 1)
        {
            plane_pos++;
        }
    }
    else
    {
        return;
    }
}


void grid::random_army_move()
{
    arm_p  = rand()% (size_l - 2) + 1;;
    score ++;
}


void grid::check_army_crash(){
int size = my_bul.size();
for(int i = 0 ; i < size; i ++){
    if (my_bul[i].first == 0 and arm_p == my_bul[i].second){
        this->random_army_move();
    }
}
}


ostream &operator<<(ostream &out, grid a)
{
    string side(a.size_l + 2, 'z');
    out << side << endl;
    for (int i = 0; i < a.size_h - 2; i++)
    {
        out << '|';

        for (int j = 0; j < a.size_l; j++)
        {
            char check = ' ';

            int b_size = a.my_bul.size();

            for (int k = 0; k < b_size; k++)
            {
                if (i == a.my_bul[k].first and j == a.my_bul[k].second)
                {
                    check = 'x';
                    break;
                }
            }

            if (i == 0)
            {
                if (j == a.arm_p - 1)
                {
                    check = '<';
                }
                if (j == a.arm_p)
                {
                    check = 'M';
                }
                if (j == a.arm_p + 1)
                {
                    check = '>';
                }
            }
            if (i == 0)
            {
                if (j == a.arm_p - 1)
                {
                    check = '<';
                }
                if (j == a.arm_p)
                {
                    check = 'M';
                }
                if (j == a.arm_p + 1)
                {
                    check = '>';
                }
            }
            out << check;
        }
        out << '|' << endl;
    }
    out << '|';
    for (int i = 0; i < a.size_l; i++)
    {
        if (i != a.plane_pos)
        {
            out << " ";
        }
        else
        {
            out << "M";
        }
    }
    out << '|' << endl;

    out << '|';
    for (int i = 0; i < a.size_l; i++)
    {
        if (i != a.plane_pos - 1)
        {
            out << " ";
        }
        else
        {
            out << "WWW";
            i += 2;
        }
    }
    out << '|' << endl;

    out << side << endl;
    out << "score : "<<a.score<<endl;
    return out;
}
