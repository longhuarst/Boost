#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

void resolv_connect(boost::asio::ip::tcp::socket &sock, const char * name, int port)
{
	boost::asio::ip::tcp::resolver rlv(sock.get_io_service());
	boost::asio::ip::tcp::resolver::query qry(name, boost::lexical_cast<string>(port));

	boost::asio::ip::tcp::resolver::iterator iter = rlv.resolve(qry);
	boost::asio::ip::tcp::resolver::iterator end;

	boost::system::error_code ec = boost::asio::error::host_not_found;

	for (; ec && iter != end; ++iter)
	{
		sock.close();
		sock.connect(*iter, ec);
	}

	if (ec) {
		cout << "can't connect." << endl;
		throw boost::system::system_error(ec);
	}

	cout << "connect success." << endl;
}

int main(int argc, char *argv[])
{

	try
	{
		boost::asio::io_service ios;
		boost::asio::ip::tcp::socket sock(ios);
		resolv_connect(sock, "www.boost.org", 80);


		ios.run();
	}
	catch (std::exception & e)
	{
		cout << e.what();
	}

	system("pause");
	return 0;
}