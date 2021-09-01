#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "sleep_ms.hpp"
#include "plane.hpp"
#include <thread>
using namespace std;

grid * my_grid = new grid;
char cmd = ' ';

void change_dir(){
    while (1){
    cin >> cmd;
    cout << "run dir"<<endl;
    my_grid->move_plane(cmd);
    }
}
void fly(){
    int t = 0;
    while (1){
        t++;
        cout << "run fly"<<endl;
        my_grid->move_bul();
        if(t % 6 == 0){
            my_grid->add_my_bul();
        }
        


        if (cmd == '\''){
        //my_grid->add_my_bul();
        cmd = ' ';
        }
        my_grid->check_army_crash();
        system("clear");
        cout << *my_grid;
        sleep_ms(100);
    }
}
int main(){
    cout << "welcome"<<endl;
    cout << "enter height and length"<<endl;
    cout << "height and length at least 5"<<endl;
    int h =10;
    int l = 10;
    //cin >> h;
    //cin >> l;
    delete my_grid;
    
    if( h < 5){
        h = 5;
        cout << "height at least 5"<<endl;
    }
    if( l < 5){
        l = 5;
        cout << "length at least 5"<<endl;
    }
    my_grid = new grid(h,l);
    cout << *my_grid;
    thread th1(fly);
    thread th2(change_dir);
    th1.join();
    th2.join();
}

