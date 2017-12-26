#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <cstdlib>

using namespace std;

mutex m;

void Foo()
{
     m.lock();
     cout << "Current thread: " << this_thread::get_id() << endl;
     this_thread::sleep_for(chrono::seconds(rand()%10));
     cout << "Leaving thread: " << this_thread::get_id() << endl;
     m.unlock();
}

int main()
{
     srand(time(NULL));
     thread t1(Foo);
     thread t2(Foo);
     thread t3(Foo);
     t1.join();
     t2.join();
     t3.join();
     return 0;
}
