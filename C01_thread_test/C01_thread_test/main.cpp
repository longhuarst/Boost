#define BOOST_DATE_TIME_SOURCE	//thread库需要使用date_time库
#define BOOST_THREAD_NO_LIB
#include <boost/thread.hpp>
#include <iostream>
#include <stdlib.h>

using namespace std;

namespace boost {
	template<typename T>
	class basic_atom :noncopyable
	{
	public:
		basic_atom(T x = T()) :n(x) {}
		T operator++()
		{
			mutex_t::scoped_lock lock(mu);
			return ++n;
		}
		operator T() { return n; }
	protected:
	private:
		T n;
		typedef mutex mutex_t;
		mutex_t mu;
	};
}



int main(int argc, char *argv[])
{

	boost::mutex mu; //申明一个互斥量对象

	try
	{
		mu.lock(); //锁定互斥量
		cout << "some operations" << endl; //临界区操作
		mu.unlock(); //解锁互斥量
	}
	catch (...) //必须使用try-catch块保证解锁互斥量
	{
		mu.unlock();
	}

	system("pause");

	boost::mutex mu2;
	boost::mutex::scoped_lock lock(mu2); //使用RAII型的lock_guard
	cout << "some operations" << endl;

	system("pause");

	typdef boost::basic_atom<int> atom_int;
	atom_int x;
	cout << ++x;
	system("pause");
	
	return 0;
}