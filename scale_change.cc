#include <iostream>
#include <vector>
#include "read_vector.hpp"
#include <sstream>
using namespace std;

class Solution
{
public:
    vector<int> s_int(string s)
    {
        int size = s.size();
        vector<int> rslt;
        for (int i = 0; i < size; i++)
        {

            if (s[i] < '9')
            {
                rslt.push_back(s[i] - '0');
            }
            else
            {
                rslt.push_back(s[i] - 'a' + 10);
            }
        }
        return rslt;
    }
    int vec_num(vector<int> nums, int form)
    {
        int size = nums.size();
        int rslt = 0;
        for (int i = 0; i < size; i++)
        {
            rslt *= form;
            rslt += nums[i];
        }
        return rslt;
    }
    string num_s(int nums, int form)
    {
        char end;
        if (nums == 0 ){
            return "";
        }
        if (nums % form >= 10)
        {
            end = nums % form - 10 + 'a';
        }
        else
        {
            end = nums % form + '0';
        }
        return num_s(nums / form, form) + string(1, end);
    }
    string trans(string inp, int from, int to)
    {
        return num_s(vec_num(s_int(inp), from), to);
    }
};



int main (){
    string s;
        int from;
        int to;
    while (1){
        cout << "Enter original number : "<<endl;
        cin >> s;
        cout << "Enter original form (2,8,10,16,32...) : "<<endl;
        cin >> from;
        cout << "Enter wanted form (2,8,10,16,32...)  "<<endl;
        cin >> to;
        cout << Solution().trans(s,from,to)<<endl;
        cout << "Would you want again ?\n if yes press 'Y'"<<endl;
        char c;
        cin >> c;
        if (!(c == 'Y' or c == 'y'))break;
        system("clear");
    }
    cout << "END\n\n";
}
