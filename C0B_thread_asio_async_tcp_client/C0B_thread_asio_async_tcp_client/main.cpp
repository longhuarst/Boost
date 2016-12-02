#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;

class client 
{
private:
	boost::asio::io_service& ios;
	boost::asio::ip::tcp::endpoint ep;
	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> sock_pt;

public:
	client(boost::asio::io_service & io):
		ios(io),
		ep(boost::asio::ip::address::from_string("127.0.0.1"),6688)
	{
		start();
	}

	void start()
	{
		sock_pt sock(new boost::asio::ip::tcp::socket(ios));
		sock->async_connect(ep, boost::bind(&client::conn_handler, this, boost::asio::placeholders::error, sock));
	}

	void conn_handler(const boost::system::error_code& ec, sock_pt sock)
	{
		if (ec)
			return;

		cout << "recive from " << sock->remote_endpoint().address();

		boost::shared_ptr<vector<char>> str(new vector<char>(100, 0));

		sock->async_read_some(boost::asio::buffer(*str), bind(&client::read_handler, this, boost::asio::placeholders::error, str));

		start();
	}

	void read_handler(const boost::system::error_code& ec,boost::shared_ptr<vector<char>> str)
	{
		if (ec)
			return;
		cout << &(*str)[0] << endl;
	}
};

int main(int argc, char *argv[])
{
	try 
	{
		cout << "client start." << endl;

		boost::asio::io_service ios;

		client cl(ios);

		ios.run();

	}
	catch (std::exception &e)
	{
		cout << e.what() << endl;
	}

	system("pause");
	
	
	return 0;
}