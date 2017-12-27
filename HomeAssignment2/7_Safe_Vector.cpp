#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

class safe_vector
{
private:

    int s;
    int v_size;
    int* f;
    recursive_mutex rm;

public:

    safe_vector()
    {
        v_size = 0;
        f = nullptr;
    }

    safe_vector(int c)
    {
        v_size=0;
        s = c;
        f = new int[c];
    }

    safe_vector (const safe_vector &v_2)
    {
        v_size = v_2.v_size;
        s = v_2.s;
        f = new int[s];
        for (int i=0; i<v_size; i++)
        {
            f[i] = v_2.f[i];
        }
    }

    safe_vector (safe_vector &&v_2)
    {
        swap(*this, v_2);
    }

    ~safe_vector()
    {
        if (f!=nullptr)
            delete[] f;
    }

    int* begin()
    {
        return(f);
    }
    int* end()
    {
        if (f==NULL)
        {
            return NULL;
        }
        return (f+v_size);
    }

    int size()
    {
        return (v_size);
    }

    bool empty()
    {
        if (v_size==0)
        {
            return true;
        }
        return false;
    }
    int capacity ()
    {
        return s;
    }

    void push_back(int data)
    {
        rm.lock();
        f[v_size] = data;
        ++v_size;
        rm.unlock();
    }

    void clear()
    {
        f=nullptr;
        v_size=0;
    }
    int pop(int n)
    {
        rm.lock();
        if (n >= v_size)
        {
            rm.unlock();
            throw out_of_array();
        }
        int result = f[n];
        for (int i = n; i<v_size; i++)
        {
            f[i] = f[i + 1];
        }
        v_size--;
        rm.unlock();
        return result;
    }
    int pop_back()
    {
        return pop(v_size-1);
    }

    void fill (int data)
    {
        rm.lock();
        for (int i = 0; i < s; i++)
        {
            f[i] = data;
        }
        v_size = s;
        rm.unlock();
    }

    void resize (int _cap)
    {
        rm.lock();
        if (_cap == s)
        {
            rm.unlock();
            return;
        }
        safe_vector new_v(_cap);
        for (int i = 0; i < _cap && i < v_size; i++)
        {
            new_v[i] = f[i];
        }
        swap(*this, new_v);
        rm.unlock();
    }
    void reserve (int s_res)
    {
        rm.lock();
        resize(s+s_res);
        rm.unlock();
    }
    void shrink_to_fit ()
    {
        rm.lock();
        resize(v_size);
        rm.unlock();
    }

    int &operator[] (int n)
    {
        rm.lock();
        if (f == nullptr)
        {
            rm.unlock();
            throw null_vector();
        }
        rm.unlock();
        return f[n];
    }
    int &at (int n)
    {
        rm.lock();
        if (f == nullptr)
        {
            rm.unlock();
            throw null_vector();
        }
        if (n >= v_size)
        {
            rm.unlock();
            throw out_of_array();
        }
        rm.unlock();
        return f[n];
    }

    safe_vector operator= (const safe_vector &v_2)
    {
        rm.lock();
        safe_vector v2(v_2);
        swap(*this, v2);
        rm.unlock();
        return *this;
    }
    safe_vector operator= (safe_vector &&v_2)
    {
        rm.lock();
        if (f!=nullptr)
            delete [] f;
        swap(*this, v_2);
        rm.unlock();
        return *this;
    }

    class null_vector : std::exception
    {
        const char* what ()
        {
            return "err_null_vector";
        }
    };
    class out_of_array : std::exception
    {
        const char* what ()
        {
            return "err_out_of_array";
        }
    };

    void swap (safe_vector &v_1, safe_vector &v_2)
    {
        v_1.rm.lock();

        int v_1_size = v_1.v_size;
        int v_1_cap = v_1.s;
        int* v_1_first = v_1.f;

        v_2.rm.lock();

        v_1.v_size = v_2.v_size;
        v_1.s = v_2.s;
        v_1.f = v_2.f;

        v_1.rm.unlock();

        v_2.v_size = v_1_size;
        v_2.s = v_1_cap;
        v_2.f = v_1_first;

        v_2.rm.unlock();
    }

};
