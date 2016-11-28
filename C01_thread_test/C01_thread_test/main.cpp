#define BOOST_DATE_TIME_SOURCE	//thread����Ҫʹ��date_time��
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

	boost::mutex mu; //����һ������������

	try
	{
		mu.lock(); //����������
		cout << "some operations" << endl; //�ٽ�������
		mu.unlock(); //����������
	}
	catch (...) //����ʹ��try-catch�鱣֤����������
	{
		mu.unlock();
	}

	system("pause");

	boost::mutex mu2;
	boost::mutex::scoped_lock lock(mu2); //ʹ��RAII�͵�lock_guard
	cout << "some operations" << endl;

	system("pause");

	typdef boost::basic_atom<int> atom_int;
	atom_int x;
	cout << ++x;
	system("pause");
	
	return 0;
}