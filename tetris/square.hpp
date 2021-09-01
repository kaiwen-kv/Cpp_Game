
#include <string>
#include <iostream>
using namespace std;
#ifndef SQUARE_H
#define SQUARE_H

class square
{
protected:
    char type;
    int pos;
    bool if_air;

public:
    void print();
    //square();
    //~square();
    virtual bool is_emp() = 0;
    virtual void set_zero() = 0;
};

void square::print()
{
    if (this->type == 'e')
    {
        cout << '_';
    }
    else
    {
        cout << this->type;
    }
}

#endif
