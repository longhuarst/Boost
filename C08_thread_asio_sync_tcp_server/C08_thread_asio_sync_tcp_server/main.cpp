#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost::asio;

int main(int argc, char *argv[])
{

	try 
	{
		cout << "server start." << endl;
		
		io_service ios; //asio程序必须的io_service对象

		boost::asio::ip::tcp::acceptor acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 6688)); //创建acceptor对象,ipv4 接受6688端口
		cout << acceptor.local_endpoint().address()<< endl;


		while (true) //循环执行任务
		{
			boost::asio::ip::tcp::socket sock(ios); //一个socket 对象
			acceptor.accept(sock); //阻塞等待socket连接

			cout << "client:" << sock.remote_endpoint().address() << endl;

			sock.write_some(buffer("hello asio")); //发送数据
			
		}
		
	}
	catch (std::exception & e) //捕获可能发生的异常
	{
		cout << e.what() << endl;
	}

	system("pause");
	
	return 0;
}