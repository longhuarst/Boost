#include <boost/thread.hpp>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <stack>



using namespace std;

boost::mutex mu_io;

class buffer
{
public:
	buffer(int size):un_read(0),capacity(size) {}

	void put(int x) {
		{
			boost::mutex::scoped_lock lock(mu);
			while (is_full()) {
				{
					boost::mutex::scoped_lock lock(mu_io);
					cout << "full waiting ..." << endl;
				}
				condition_put.wait(mu);
			}
			stk.push(x);
			++un_read;
		}
		condition_get.notify_one();
	}

	void get(int *x) {
		{
			boost::mutex::scoped_lock lock(mu);
			
			while (is_empty()) {
				{
					boost::mutex::scoped_lock lock(mu_io);
					cout << "empty waiting ..." << endl;
				}
				condition_get.wait(mu);
			}
			*x = stk.top();
			stk.pop();
			--un_read;
		}
		condition_put.notify_one();
	}
protected:
private:
	boost::mutex mu;
	int un_read, capacity;
	boost::condition_variable_any condition_put;
	boost::condition_variable_any condition_get;
	stack<int> stk;

	bool is_full() {
		return un_read == capacity;
	}

	bool is_empty() {
		return un_read == 0;
	}
	
};




buffer buf(5);

void producer(int n)
{
	for (int i = 0; i < n; ++i) {
		
		buf.put(i);
		{
			boost::mutex::scoped_lock lock(mu_io);
			cout << "put " << i << endl;
		}
	}
}

void consumer(int n)
{
	int x;
	for (int i = 0; i < n; ++i) {
		buf.get(&x);
		{
			boost::mutex::scoped_lock lock(mu_io);
			cout << "get " << x << endl;
		}
	}
}

int main(int argc, char *argv[])
{
	

	boost::thread t1(boost::bind(producer, 20));
	boost::thread t2(boost::bind(consumer, 10));
	boost::thread t3(boost::bind(consumer, 10));

	t1.join();
	t2.join();
	t3.join();

	system("pause");
	
	
	return 0;
}