#include "square.hpp"

#ifndef emp_H
#define emp_H
class emp : public square
{
public:
    emp();
    emp(char type);
    bool is_emp();
    void set_zero();
};

emp::emp()
{
    this->type = 'e';
    //pos = 0;
}
emp::emp(char type)
{
    this->type = type;
    //pos = 0;
}
bool emp::is_emp(){
    if (type == 'e'){
        return true;
    }
    else {
        return false;
    }
}

void emp::set_zero(){
    this->type = 'e';
}

#endif
