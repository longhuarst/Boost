#define BOOST_DATE_TIME_SOURCE	//thread����Ҫʹ��date_time��
#define BOOST_THREAD_NO_LIB
#include <boost/thread.hpp>
#include <iostream>
#include <stdlib.h>

using namespace std;


int main(int argc, char *argv[])
{

	boost::mutex mu;

	try
	{
		mu.lock();
		cout << "some operations" << endl;
		mu.unlock();
	}
	catch (...)
	{
		mu.unlock();
	}

	system("pause");
	
	return 0;
}