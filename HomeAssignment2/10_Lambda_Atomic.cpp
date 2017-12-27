#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>

using namespace std;

template <class T> class Atomic
{
private:

	T data;
	mutable mutex mutex;

public:

	T load () const
	{
		mutex.lock();
		T res = data;
		mutex.unlock();
		return res;
	}
	void store(const T data1)
	{
		mutex.lock();
		data = data1;
		mutex.unlock();
	}
	T exchange(const T data1)
	{
		mutex.lock();
		T res = data;
		data = data1;
		mutex.unlock();
		return res;
	}


	operator T()
	{
		mutex.lock();
		T res = data;
		mutex.unlock();
		return res;
	}

	Atomic<T> &operator++()
	{
	    mutex.lock();
		data++;
		mutex.unlock();
		return *this;
	}

	Atomic<T> &operator++(int)
	{
	    mutex.lock();
	    Atomic<T> res(++data);
		mutex.unlock();
		return *this;
	}

	Atomic<T> &operator--()
	{
	    mutex.lock();
		data--;
		mutex.unlock();
		return *this;
	}

	Atomic<T> &operator--(int)
	{
	    mutex.lock();
	    Atomic<T> res(--data);
		mutex.unlock();
		return *this;
	}

	Atomic &operator= (const Atomic <T> &o)
	{
		mutex.lock();
		data = o.data;
		mutex.unlock();
		return *this;
	}

	Atomic &operator= (Atomic <T> &&o)
	{
		mutex.lock();
		data = (*o).data;
		mutex.unlock();
		return *this;
	}

	template <typename application, typename... args>
    application apply (application(T::*app) (args...), args... app_args)
    {
        mutex.lock();
        application res = (data.*app)(app_args...);
        mutex.unlock();
        return res;
    }

	Atomic ()
	{
		data = T();
	}

	Atomic (const T &d)
	{
		data = d;
	}

	Atomic (const Atomic <T> &o)
	{
		data = o.data;
	}

	Atomic (Atomic <T> &&o)
	{
		data = (*o).data;
	}

	~Atomic ()
	{}
};
