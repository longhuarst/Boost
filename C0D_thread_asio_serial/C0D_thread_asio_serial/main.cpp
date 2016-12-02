#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <vector>

using namespace std;

void time_exipred(const boost::system::error_code& ec, boost::asio::serial_port *sp)
{
	cout << "time_exipred" << endl;
	sp->close();
}

void read_handler(const boost::system::error_code& ec)
{
	cout << ec.message() << endl;
}



int main(int argc, char *argv[])
{
	boost::asio::io_service ios;
	boost::asio::serial_port sp(ios, "COM4");

	sp.set_option(boost::asio::serial_port::baud_rate(115200));
	sp.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
	sp.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
	sp.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
	sp.set_option(boost::asio::serial_port::character_size(boost::asio::serial_port::character_size(8)));

	size_t len = sp.write_some(boost::asio::buffer("hello serial"));
	cout << len << endl;
	
	vector<char> v(100,0);
	sp.async_read_some(boost::asio::buffer(v),boost::bind(read_handler,boost::asio::placeholders::error));

	boost::asio::deadline_timer t(ios, boost::posix_time::seconds(2));
	t.async_wait(boost::bind(&boost::asio::serial_port::cancel,  boost::ref(sp)));

	ios.run();

	cout << "read data:" <<&v[0] << endl;
	system("pause");
	
	
	return 0;
}