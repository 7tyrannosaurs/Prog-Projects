#include <iostream>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>


using namespace std;

class my_complex {

    private:

        double a, b;

    public:

        my_complex (double x = 0, double y = 0) {
            a = x;
            b = y;
        }

        my_complex (const my_complex & q) {
            a = q.a;
            b = q.b;
        }

        my_complex & operator = (const my_complex & q) {
            a = q.a;
            b = q.b;
            return *this;
        }

        bool operator == (my_complex x) {
            return (x.a == a) && (x.b == b);
        }

        bool operator != (my_complex x) {
            return (x.a != a) || (x.b != b);
        }

        const my_complex operator + (my_complex x) {
            return my_complex (a + x.a, b + x.b);
        }

        const my_complex operator - (my_complex x) {
            return my_complex (a - x.a, b - x.b);
        }

        const my_complex operator * (my_complex x) {
            return my_complex (a * x.a - b * x.b, b * x.a + a * x.b);
        }

        double abs (void) {
            return sqrt (a * a + b * b);
        }

        /*void print (void) {
            if (a != 0 && b != 0) {
                cout << a << " + " << b << "i" << endl;
            } else
                if (a != 0 && b == 0) {
                    cout << a << endl;
                } else
                    if (a == 0 && b != 0) {
                        cout << b << "i" << endl;
                    } else {
                        cout << a << endl;
                    }
        }*/

        double Re () {
            return a;
        }

        double Im () {
            return b;
        }

        friend ostream & operator << (ostream & os, const my_complex & v)
        {
            return os << v.a << " + " << v.b << "i" << endl;
        }

        friend istream & operator >> (istream & is, my_complex & n)
        {
            is >> n.a >> n.b;
            return is;
        }

        ~my_complex () {
        }

};


class my_vector {

    private:

        my_complex * data;
        int size_of_data;

    public:

        my_vector (int n) {
            data = new my_complex (n);
            int i;
            for (i = 0; i < n; ++i) {
                data[i] = my_complex (0);
            }
            size_of_data = n;
        }


        bool operator == (my_vector x) {
            if (x.size_of_data != size_of_data)
                return 0;
            for(int i = 0; i < size_of_data; ++i)
                if (data[i] != x.data[i])
                    return 0;
            return 1;
        }

        bool operator != (my_vector x) {
            if (x.size_of_data != size_of_data)
                return 1;
            for(int i = 0; i < size_of_data; ++i)
                if (data[i] == x.data[i])
                    return 1;
            return 0;
        }


        my_complex& operator [] (int i) {
            return data[i];
        }

        /*void resize(int n) {
            my_complex * n_data = new my_complex (size_of_data);
            for (int i = 0; i < size_of_data; ++i){
                n_data[i] = data[i];
            }

            delete [] data;
            cout << "HERE_2\n";

            data = new my_complex(n);

            cout << "HERE_1\n";
            for (int i = 0; i < n; ++i) {
                if (i < size_of_data)
                    data[i] = n_data[i];
                else
                    data[i] = my_complex ();
            }
            size_of_data = n;
        }*/

        /*void push_back (my_complex x) {
            my_complex * new_data = new my_complex (size_of_data + 1);
            for (int i = 0; i < size_of_data; ++i)
                new_data[i] = data[i];

        }*/

        void print (void) {
            for(int i = 0; i < size_of_data; ++i)
                cout << data[i];
        }

        my_vector (const my_vector & q) {
            data = new my_complex(q.size_of_data);
            size_of_data = q.size_of_data;
            for (int i = 0; i < size_of_data; ++i){
                data[i] = q.data[i];
            }
        }

        ~my_vector(){
            delete [] data;
        }
};

int main(void){

    my_complex A;

    cin >> A;
    cout << A;

    my_vector v(5);

    for (int i = 0; i < 5; ++i) {
        my_complex A (i, i +1);
        v[i] = A;
    }

    v.print();
    //v.resize(5);

    return 0;

}
