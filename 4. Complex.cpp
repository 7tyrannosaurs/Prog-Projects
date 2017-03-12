#include <iostream>
#include <cmath>

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

        friend ostream & operator <<(ostream & os, const my_complex & v)
        {
            return os << v.a << " + " << v.b << "i" << endl;
        }

        friend istream & operator >>(istream & is, my_complex & n)
        {
            is >> n.a >> n.b;
            return is;
        }

        ~my_complex () {
        }

};


int main (void){

    my_complex A;
    my_complex B;
    my_complex C;
    cin >> A >> B >> C;
    cout << "A = " << A;
    cout << "B = " << B;
    cout << "C = " << C;

    C = B + A;
    C = B - A;
    C = B * A;
    cout << "New C = " << C;

    cout << "Abs = " << C.abs () << endl;

    return 0;

}
