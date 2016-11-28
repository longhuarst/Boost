#define BOOST_DATE_TIME_SOURCE	//thread库需要使用date_time库
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

	boost::mutex mu2;
	boost::mutex::scoped_lock lock(mu2);
	cout << "some operations" << endl;
	
	return 0;
}