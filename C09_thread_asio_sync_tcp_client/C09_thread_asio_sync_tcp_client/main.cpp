#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <vector>


using namespace std;

void client(boost::asio::io_service &ios) //传入io_service对象
{
	try
	{
		cout << "client start." << endl;

		boost::asio::ip::tcp::socket sock(ios); //创建socket对象
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"),6688); //创建连接端点

		sock.connect(ep); //socket 连接端点

		vector<char> str(100, 0); //定义一个vector缓冲区
		sock.read_some(boost::asio::buffer(str)); //使用bufffer()包装缓冲区接收数据
		cout << "recive from " << sock.remote_endpoint().address();
		cout << &str[0] << endl;
	}
	catch (std::exception & e)
	{
		cout << e.what() << endl;
	}
	
}


int main(int argc, char *argv[])
{
	boost::asio::io_service ios;

	client(ios);

	ios.run();

	system("pause");
	
	return 0;
}