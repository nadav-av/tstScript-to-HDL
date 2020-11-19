#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

struct var
{
    char var[40];
};

int main()
{
    ofstream MyFile("script.tst");
    cout << "How many variables?" << endl;
    unsigned int n;
    cin >> n;
    var* arr= new var[n];

    cout << "Enter name of Cycle.hdl to load:" << endl;
    char name[30];
    cin >> name;

    for(int i=0; i<n;i++)
    {
        cout << "enter name of var " << i+1 << endl;
        cin >> arr[i].var;
    }
    
    MyFile << "load " << name << ".hdl," << endl;
    MyFile << "output-file " << name << ".out," << endl;
    MyFile << "compare-to " << name << ".cmp," << endl;
    MyFile << "output-list ";

    for(int k=0; k<n; k++)
    {
        MyFile << arr[k].var << "%B3.1.3 ";
    }

    MyFile << "out%B3.1.3;" << endl;
    MyFile << endl;

    
    std::vector<std::vector<int> > output(n, std::vector<int>(1 << n));

    unsigned num_to_fill = 1U << (n - 1);
    for(unsigned col = 0; col < n; ++col, num_to_fill >>= 1U)
    {
        for(unsigned row = num_to_fill; row < (1U << n); row += (num_to_fill * 2))
        {
            fill_n(&output[col][row], num_to_fill, 1);
        }
    }

    // These loops just print out the results, nothing more.
    for(unsigned x = 0; x < (1 << n); ++x)
    {
        for(unsigned y = 0; y < n; ++y)
        {
            MyFile << "set "  << arr[y].var << " " << output[y][x] << "," << endl;
        }

        MyFile << "eval," << endl << "output;"<< endl;
        MyFile << endl;
    }


    MyFile.close();

    return 0;
}