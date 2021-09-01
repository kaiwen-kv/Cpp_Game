#include <string>
#include <iostream>
#include <vector>
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


ostream & operator<< ( ostream & out ,vector<int * > v){
    int size  = v.size();
    for (int i = 0 ; i < size ; i ++){
        out << *v[i] << ',';
    }
return out ;
}



ostream & operator<< (ostream & out ,vector<vector<int * > > vv){

    int size  = vv.size();
    for (int i = 0 ; i < size ; i ++){
        out << vv[i] << endl;
    }
return out ;
}
 void test1()
{
    vector<vector<int *> > vv;
    for (int i = 0; i < 5; i++)
    {
        vector<int *> temp; 
        for (int j = 0; j < 10; j++)
        {
            //int a = j + i * 10 ;
            temp.push_back(new int(j + i * 10));
        }
        vv.push_back(temp);
    }
    cout << vv <<endl;

    vv.erase(vv.begin() + 2 );
    cout << vv<<endl;

    vv[0] = vv[2];
    
    cout << vv<<endl;
}


void test2(){
    cout << abs(10 -11);
}
int main (){
    test2();
}