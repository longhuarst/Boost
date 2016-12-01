#include <iostream>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

using namespace std;

boost::mutex io_mu;

class rw_data
{
public:
	rw_data():m_x(0) {}

	void write()
	{
		boost::unique_lock<boost::shared_mutex> ul(rw_mu);
		++m_x;
	}

	void read(int *x)
	{
		boost::shared_lock<boost::shared_mutex> sl(rw_mu);
		*x = m_x;
	}
protected:
private:
	int m_x;
	boost::shared_mutex rw_mu;
};


void writer(rw_data &d)
{
	for (int i = 0; i < 20; ++i) {
		boost::this_thread::sleep(boost::posix_time::millisec(10));
		d.write();
	}
}

void reader(rw_data &d)
{
	int x;
	for (int i = 0; i < 10; ++i) {
		boost::this_thread::sleep(boost::posix_time::millisec(5));
		d.read(&x);
		boost::mutex::scoped_lock lock(io_mu);
		cout << "reader:" << x << endl;
	}
}

int main(int argc, char *argv[])
{
	rw_data d;
	boost::thread_group pool;

	pool.create_thread(bind(reader, ref(d)));
	pool.create_thread(bind(reader, ref(d)));
	pool.create_thread(bind(reader, ref(d)));
	pool.create_thread(bind(reader, ref(d)));
	pool.create_thread(bind(writer, ref(d)));
	pool.create_thread(bind(writer, ref(d)));

	pool.join_all();

	system("pause");

	return 0;
}