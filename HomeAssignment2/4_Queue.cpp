#include<iostream>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<thread>
#include<cstdlib>

using namespace std;

template<typename T>

class Queue
{
private:

	mutable mutex m;
	queue<T> data;
	condition_variable cond;

public:

	Queue()
	{
	}

	Queue(Queue const& o)
	{
		lock_guard<mutex> locker(o.m);
		data = o.data;
	}

	~Queue()
	{
	}

	void push(T v)
	{
		lock_guard<mutex> locker(m);
		data.push(v);
		cond.notify_one();
	}

	void cond_pop(T& value)
	{
		unique_lock<mutex> locker(m);
		cond.wait(locker, [this] {return !data.empty(); });
		value = data.front();
		data.pop();
	}

	shared_ptr<T> cond_pop()
	{
		unique_lock<mutex> locker(m);
		cond.wait(locker, [this] {return !data.empty(); });
		shared_ptr<T> r(make_shared<T>(data.front()));
		data.pop();
		return r;
	}

	bool popping(T& value)
	{
		lock_guard<mutex> locker(m);
		if (data.empty())
			return false;
		value = data.front();
		data.pop();
		return true;
	}

	shared_ptr<T> popping()
	{
		lock_guard<mutex> locker(m);
		if (data.empty())
			return shared_ptr<T>();
		shared_ptr<T> r(make_shared<T>(data.front()));
		data.pop();
		return r;
	}

	bool empty() const
	{
		lock_guard<mutex> locker(m);
		return data.empty();
	}

	void print (int c)
	{
        lock_guard<mutex> locker(m);
        for (int i = 0; i < c; i++)
        {
             cout << data.front() << endl;
             data.pop();
        }
	}

};

void func(Queue <int>& myQueue)
{
	myQueue.push(*myQueue.popping());
}

int main() {

    int c;
	Queue<int> myQueue;
	cout << "Enter the number of threads: ";
	cin >> c;
	cout << endl;

	thread *t = new thread[c];
	for (int i = 0; i < c; i++) {
		myQueue.push(i);
	}
	for (int i = 0; i < c; i++)
		t[i] = thread(func, ref(myQueue));
	for (int i = 0; i < c; i++) {
		t[i].join();
	}

    myQueue.print(c);

	return 0;
}
