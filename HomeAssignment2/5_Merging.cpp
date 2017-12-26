#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

void Merge (vector <int> &a, int T)
{
    if (a.size() == 1) {}
    else if (a.size() == 2)
    {
        if (a[1] < a[0])
            swap (a[0], a[1]);
    } else {
        int l = a.size() / 2;

        vector<int> A1;
        vector<int> A2;

        for (int i = 0; i < a.size(); i++)
        {
            if (i < l)
            {
                A1.push_back(a[i]);
            } else
              {
                A2.push_back(a[i]);
              }
        }

        if (T <= 0)
        {
            Merge(A1, 0);
            Merge(A2, 0);
        } else if (T == 1)
          {
              T = T - 1;
              thread Thread1 ([](vector<int> *a, int m){Merge(*a, m);}, &A1, 0);
              Merge(A2, 0);
              Thread1.join();
          } else {
              T = T - 2;
              thread Thread1 ([](vector<int> *a, int m){Merge(*a, m);}, &A1, T / 2);
              thread Thread2 ([](vector<int> *a, int m){Merge(*a, m);}, &A2, T - (T / 2));
              Thread1.join();
              Thread2.join();
          }

        int a1 = 0;
        int a2 = 0;
        for (int i = 0; i < a.size(); i++)
        {
            if (a1 < A1.size() && (a2 >= A2.size() || A1[a1] <= A2[a2]))
            {
                a[i] = A1[a1];
                a1++;
            } else if (a2 < A2.size())
              {
                a[i] = A2[a2];
                a2++;
              }
        }
    }
}

int main()
{
    int v;
    int T;

    cout << "Please, enter the array size: ";
    cin >> v;
    cout << endl;
    cout << "Please, enter the number of threads: ";
    cin >> T;
    cout << endl;

    vector <int> a(v);

    srand(time(NULL));

    for (int i = 0; i < a.size(); i++)
        a[i] = rand() % 100;

    for (int i = 0; i < a.size(); i++)
        cout << setw(5) << a[i];

    cout << endl << endl;

    Merge(a, T);

    cout << "Merged: " << endl << endl;

    for (int i = 0; i < a.size(); i++)
        cout << setw(5) << a[i];

    cout << endl;

    return 0;
}
