#include <string>
#include <iostream>
#include <vector>

using namespace std;

const int my_speed = 3;
const int arm_speed = 1;
const int square_size_width = 10;
const int square_size_length = 30;

class square
{
    protected:
    char type;
    int pos;
    
public:
    void print();
    //square();
    //~square();
};
class emp : public square
{

public:
    emp();
};
class LLL : public square
{

public:
    LLL();
};
class TTT : public square
{

public:
    TTT();
};

class JJJ : public square
{

public:
    void print();
    JJJ();
};

int main()
{

}
