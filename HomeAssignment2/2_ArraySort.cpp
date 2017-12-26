#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

void sorting (vector <int> &a)
{
    cout << "Thread: " << this_thread::get_id() << endl;
    sort (a.begin(), a.end());
}

void printing (vector<vector<int> > a)
{
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            cout << setw(5) << a[i][j];
        }
        cout << endl;
    }
}

int main ()
{
    srand (time(NULL));

    int arrcolumns = rand() % 10 + 1;
    int arrstrings = rand() % 10 + 1;

    vector<vector<int> > a;

    for (int i = 0; i < arrstrings; i++)
    {
        vector <int> arr_i;
        for (int j = 0; j < arrcolumns; j++)
        {
            arr_i.push_back(rand() % 50);
        }
        a.push_back(arr_i);
    }

    cout << endl;
    printing(a);
    cout << endl;

    for (int i = 0; i < arrstrings; i++)
    {
        thread t(sorting, ref (a[i]));
        t.join();
    }

    cout << endl;
    printing(a);

    return 0;
}
