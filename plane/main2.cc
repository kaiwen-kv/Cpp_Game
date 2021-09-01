#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

class grid
{
    int size_h;
    int size_l;
    vector<string> data;

public:
    grid();
    grid(int h, int l);
    void move_plane(char d); //wasd
    friend ostream &operator<<(ostream &out, grid a);
};
grid::grid()
{
    size_h = 10;
    size_l = 20;

    data.clear();
    string ept(size_l, ' ');
    for (int i = 0; i < size_h; i++)
    {
        if (i != size_h - 1)
        {
            data.push_back(ept);
        }
    }
}

grid::grid(int h, int l)
{
}

ostream &operator<<(ostream &out, vector<string> a)
{
    int size = a.size();

    for (int i = 0; i < size; i++)
    {
        out << '|';
        out << a[i];
        out << '|'<<endl;
    }

    return out;
}
ostream &operator<<(ostream &out, grid a)
{
    string line(a.size_l + 2, 'z');
    out << line<<endl;
    out << a.data;
    out << line;
    return out;
}

int main()
{
    
    grid a;
    cout << a;
    /*
    a.move_plane('a');
    cout << a;
    a.move_plane('d');
    cout << a;
    a.move_plane('d');
    cout << a;
    a.move_plane('d');
    */
    cout << "<v>" << endl;
}
