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
	mutex mutex;

public:

	T load ()
	{
		mutex.lock();
		T res = data;
		mutex.unlock();
		return res;
	}
	void store(T data1)
	{
		mutex.lock();
		data = data1;
		mutex.unlock();
	}
	T exchange(T data1)
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


void decrease(Atomic<int>* p, int s)
{
	for (int i = 0; i < s; i++)
    {
		(*p)--;
        (*p)++;
        (*p)++;
	}
}

int main()
{
	int threads = 10;
	Atomic <int> a(-1);
	decrease(&a, 1);

	thread* ar = new thread[threads];

	for (int i = 0; i < threads; i++)
    {
		ar[i] = thread(decrease, &a, 1000);
		cout << "Thread " << i + 1 << ": " << a << endl;
	}

	for (int i = 0; i < threads; i++)
	{
		ar[i].join();
	}

	cout << endl << "Last: " << a.exchange(256) << endl;
	cout << "Given: " << a.load() << endl;

	delete [] ar;

	return 0;
}
