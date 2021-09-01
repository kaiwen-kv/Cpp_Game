#include <iostream>
#include <string>
#include <vector>

using namespace std;

class matrix
{
    vector<vector<float> > data;
    int row;
    int col;

public:
    friend ostream &operator<<(ostream &out, matrix m);
    //friend matrix &operator-(matrix &mx1, const matrix & mx2);
    //friend matrix &operator+(matrix &mx1, const matrix & mx2);
    friend matrix operator+(const matrix &mx1, const matrix &mx2);
    friend matrix operator-(const matrix &mx1, const matrix &mx2);
    friend matrix operator*(const matrix &mx1, const matrix &mx2);
    //friend matrix &operator*(matrix &mx1, const matrix & mx2);
    matrix(int row, int col);
    matrix(matrix const &cp);
    matrix operator=(const matrix &mx1);
    void clear_the_data(int row, int col);
    void readin();
    void row_add(int first, int second);
    void row_sub(int first, float times, int second);
    void row_mult(int first, float times);
    void row_div(int first, float times);
    void row_swap(int first, int second);
    void shift_line_to_bottom(int r);
    void make_leading_one(int r, int c);
    matrix rref();
    int get(string s);
    matrix find_inverse();
};
int matrix::get(string s)
{
    if (s == "row")
    {
        return row;
    }
    if (s == "col")
    {
        return col;
    }
    return -1;
}
ostream &operator<<(ostream &out, vector<float> line)
{
    int size = line.size();
    for (int i = 0; i < size; i++)
    {
        out << line[i];
        if (i != size)
        {
            out << '\t';
        }
    }
    return out;
}
ostream &operator<<(ostream &out, vector<vector<float> > mx)
{
    int size = mx.size();
    for (int i = 0; i < size; i++)
    {
        //if (i != 0){out<<'\t' ;}
        out << '\t';
        out << mx[i] << endl;
    }
    return out;
}

ostream &operator<<(ostream &out, matrix m)
{
    out << m.row << " x " << m.col << endl;
    out << m.data;
    return out;
}
ostream &operator<<(ostream &out, vector<matrix> vm)
{
    int size = vm.size();
    for (int i = 0; i < size; i++)
    {
        char pos = 'A' + i;
        out << "M" << pos << ": ";
        out << vm[i] << endl;
    }
    return out;
}

matrix ::matrix(int row, int col)
{
    this->row = row;
    this->col = col;
    vector<float> one_row;
    for (int j = 0; j < col; j++)
    {
        one_row.push_back(0);
    }

    data.clear();
    for (int i = 0; i < row; i++)
    {

        data.push_back(one_row);
    }
}
matrix::matrix(matrix const &cp)
{
    this->data = cp.data;
    this->col = cp.col;
    this->row = cp.row;
}

matrix matrix::operator=(const matrix &mx1)
{
    this->data = mx1.data;
    this->col = mx1.col;
    this->row = mx1.row;
    return *this;
}
void matrix ::clear_the_data(int row, int col)
{
    this->row = row;
    this->col = col;
    vector<float> one_row;
    for (int j = 0; j < col; j++)
    {
        one_row.push_back(0);
    }

    data.clear();
    for (int i = 0; i < row; i++)
    {

        data.push_back(one_row);
    }
}
void print_matrix_except(vector<vector<float> > mx, int row, int col)
{
    int row_size = mx.size();
    for (int i = 0; i < row_size; i++)
    {
        int col_size = mx[i].size();
        if (i == row)
        {
            for (int j = 0; j < col_size; j++)
            {
                if (j == col)
                {
                    cout << "__";
                }
                else
                {
                    cout << mx[i][j];
                }
                cout << '\t';
            }
            cout << endl;
        }
        else
        {
            cout << mx[i] << endl;
        }
    }
}
void matrix::readin()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            print_matrix_except(data, i, j);
            float temp = j;
            cin >> temp;
            data[i][j] = temp;
            system("clear");
        }
    }
}
void matrix::row_add(int first, int second)
{
    if (first >= row)
    {
        return;
    }
    if (second >= row)
    {
        return;
    }
    for (int i = 0; i < col; i++)
    {
        data[first][i] += data[second][i];
    }
}
void matrix::row_sub(int first, float times, int second)
{
    if (first >= row)
    {
        return;
    }
    if (second >= row)
    {
        return;
    }
    for (int i = 0; i < col; i++)
    {
        data[first][i] -= times * data[second][i];
    }
}
void matrix::row_mult(int first, float times)
{
    if (first >= row)
    {
        return;
    }
    for (int i = 0; i < col; i++)
    {
        data[first][i] *= times;
    }
}
void matrix::row_div(int first, float times)
{
    if (first >= row)
    {
        return;
    }
    for (int i = 0; i < col; i++)
    {
        data[first][i] /= times;
    }
}
void matrix::row_swap(int first, int second)
{
    if (first >= row)
    {
        return;
    }
    if (second >= row)
    {
        return;
    }
    for (int i = 0; i < col; i++)
    {
        vector<float> temp;
        temp = data[first];
        data[first] = data[second];
        data[second] = temp;
    }
}
void matrix::shift_line_to_bottom(int r)
{
    vector<float> temp = data[r];
    for (int i = r; r < row - 1; r++)
    {
        data[r] = data[r + 1];
    }
    data[row - 1] = temp;
}

void matrix::make_leading_one(int r, int c)
{
    if (data[r][c] == 0)
    {
        return;
    }
    row_div(r, data[r][c]);
    for (int i = 0; i < row; i++)
    {
        if (i != r)
        {
            row_sub(i, data[i][c], r);
        }
    }
}

matrix matrix::rref()
{
    int rrr = 0;
    int ccc = 0;
    int shift_line_times = 0;
    int leading_row_num = 0;
    while (1)
    {
        //cout << data << endl;
        //cout << rrr << ccc << leading_row_num << endl;

        if (ccc >= col)
        {
            break;
        };
        if (rrr >= row)
        {
            rrr = leading_row_num;
            ccc++;
            continue;
        }
        if (data[rrr][ccc] == 0)
        {
            shift_line_to_bottom(rrr);
            shift_line_times++;
        }
        else
        {
            make_leading_one(rrr, ccc);
            leading_row_num++;
            rrr++;
            ccc++;
        }
        if (shift_line_times >= row)
        {
            ccc++;
            shift_line_times = 0;
            continue;
        }
    }
    return *this;
}

matrix matrix::find_inverse()
{
    //check col and row;
    if (col != row)
    {
        return matrix(1, 1);
    }
    else
    {
        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (i == j)
                {
                    data[i].push_back(1);
                }
                else
                {
                    data[i].push_back(0);
                }
            }
        }
        cout <<"herezzz";
        col *= 2;
        this->rref();
        return *this;
    }
}
matrix operator+(const matrix &mx1, const matrix &mx2)
{
    matrix mx3(mx1);
    if (mx1.col == mx2.col && mx1.row == mx2.row)
    {
        int col = mx1.col;
        int row = mx1.row;
        for (int i = 0; i < col * row; i++)
        {
            mx3.data[i / col][i % col] = mx1.data[i / col][i % col] + mx2.data[i / col][i % col];
        }
    }
    return mx3;
}
matrix operator-(const matrix &mx1, const matrix &mx2)
{
    matrix mx3(mx1);
    if (mx1.col == mx2.col && mx1.row == mx2.row)
    {
        int col = mx1.col;
        int row = mx1.row;
        for (int i = 0; i < col * row; i++)
        {
            mx3.data[i / col][i % col] = mx1.data[i / col][i % col] - mx2.data[i / col][i % col];
        }
    }
    return mx3;
}

/*
matrix &operator-(matrix &mx1, const matrix & mx2)
{
    if (mx1.col == mx2.col && mx1.row == mx2.row)
    {
        int col = mx1.col;
        int row = mx1.row;
        for (int i = 0; i < col * row; i++)
        {
            mx1.data[i / col][i % col] -= mx2.data[i / col][i % col];
        }
    }
    return mx1;
}*/
matrix operator*(const matrix &mx1, const matrix &mx2)
{

    int row1 = mx1.row;
    int col1 = mx1.col;
    int row2 = mx2.row;
    int col2 = mx2.col;
    matrix mx3(1, 1);
    if (col1 == row2)
    {
        mx3.clear_the_data(row1, col2);
        for (int i = 0; i < row1; i++)
        {
            for (int j = 0; j < col2; j++)
            {
                for (int k = 0; k < col1; k++)
                {
                    mx3.data[i][j] += mx1.data[i][k] * mx2.data[k][j];
                }
            }
        }
    }
    return mx3;
}

void main_function()
{
    vector<matrix> my_matrix_vec;
    
    cout << "Welcome to Matrix calculator\n";
    while (1)
    {
        system("clear");
        cout << "Which operation you want to do?\n";
        cout << "1. Adding new Matirx\n";
        cout << "2. Matrix simple operation(e.g. A+B A-B A*B)\n";
        cout << "3. Matrix RREF\n";
        cout << "4. Find inverse of a Square Matrix";
        cout << "0. Clear all data\n";
        cout << "q. logout and saving data\n";
        cout << "There is (are) all the matrix we have\n";
        cout << my_matrix_vec;
        char cmd;
        cin >> cmd;
        if (cmd == '1') //cout << "1. Adding new Matirx\n";
        {
            cout << "Enter the size you want to add\n(e.g.3x2)\n";
            int r;
            char op;
            int c;
            cin >> r >> op >> c;
            if (cin.fail())
            {
                cout << "Error data type\n";
                continue;
            }
            matrix add_new(r, c);
            add_new.readin();
            my_matrix_vec.push_back(add_new);
        }
        else if (cmd == '2') //cout << "2. Matrix simple operation(e.g. A+B A-B A*B)\n";
        {
            cout << "Which two matrix you want to operate ?\n(Enter the character e.g. A+B , A-B , A*B)\n";
            char m1;
            char m2;
            char c;
            int mm1;
            int mm2;
            cin >> m1 >> c >> m2;
            if (m1 > 96)
            {
                mm1 = m1 - 'a';
            }
            else
            {
                mm1 = m1 - 'A';
            }
            if (m2 > 96)
            {
                mm2 = m2 - 'a';
            }
            else
            {
                mm2 = m2 - 'A';
            }
            int my_all_matrix_num = my_matrix_vec.size();
            if (mm1 >= my_all_matrix_num or mm2 >= my_all_matrix_num)
            {
                cout << "Enter a valid Matrix number\n";
            }
            else
            {
                if (c == '+')
                {
                    my_matrix_vec.push_back(my_matrix_vec[mm1] + my_matrix_vec[mm2]);
                }
                else if (c == '-')
                {
                    my_matrix_vec.push_back(my_matrix_vec[mm1] - my_matrix_vec[mm2]);
                }
                else if (c == '*')
                {
                    my_matrix_vec.push_back(my_matrix_vec[mm1] * my_matrix_vec[mm2]);
                }
                else
                {
                    cout << "Enter a valid Matrix operator \n";
                }
            }
        }
        else if (cmd == '3') //cout << "3. Matrix RREF\n";
        {
            cout << "Which matrix you want to transfor to RREF ?\n(Enter the character e.g. A , C)\n";
            char m1;
            int mm1;
            cin >> m1;
            if (m1 > 96)
            {
                mm1 = m1 - 'a';
            }
            else
            {
                mm1 = m1 - 'A';
            }
            int my_all_matrix_num = my_matrix_vec.size();
            if (mm1 >= my_all_matrix_num)
            {
                cout << "Enter a valid Matrix number\n";
            }
            else
            {
                my_matrix_vec.push_back(matrix(my_matrix_vec[mm1]).rref());
            }
        }
        else if (cmd == '4') //Find inverse of a Square Matrix";
        {
            cout << "Which matrix you want to find the inverse?\n(Enter the character e.g. A , C)\n";
            char m1;
            int mm1;
            cin >> m1;
            if (m1 > 96)
            {
                mm1 = m1 - 'a';
            }
            else
            {
                mm1 = m1 - 'A';
            }
            int my_all_matrix_num = my_matrix_vec.size();
            if (mm1 >= my_all_matrix_num)
            {
                cout << "Enter a valid Matrix number\n";
            }
            else
            {
                int row = my_matrix_vec[mm1].get("row");
                int col = my_matrix_vec[mm1].get("col");
                if (row == 0)
                {
                    cout << "the wrong type matrix enter\n";
                }
                if (col == 0)
                {
                    cout << "the wrong type matrix enter\n";
                }
                if (row != col)
                {
                    cout << "the wrong type matrix enter\n";
                }
                my_matrix_vec.push_back(matrix (my_matrix_vec[mm1]).find_inverse());
            }
        }
        else if (cmd == '5')
        {
            cout << "did'not finish\nwaiting to be adding\n";
        }
        else if (cmd == '6')
        {
            cout << "did'not finish\nwaiting to be adding\n";
        }
        else if (cmd == '7')
        {
            cout << "did'not finish\nwaiting to be adding\n";
        }
        else if (cmd == '0') //cout << "0. Clear all data\n";
        {
            my_matrix_vec.clear();
        }
        else if (cmd == 'q') //cout << "0. logout and saving data\n";
        {
            cout << "did'not finish the data remember function\nwaiting to be adding\n";
            break;
        }
        else
        {
            cout << "Cannot find the cmd you Enter\n";
        }
    }
}

void test2()
{
    matrix a(2, 2);
    matrix b(2, 2);
    a.readin();
    b.readin();
    cout << "print a and b\n";
    cout << a;
    cout << b;
    cout << "line-----------\n";
    cout << "line-----------\n";
    matrix c(a * b);
    cout << c;
}

int main()
{
    //test2();
    main_function();
}
