#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <vector>


using namespace std;

void client(boost::asio::io_service &ios) //����io_service����
{
	try
	{
		cout << "client start." << endl;

		boost::asio::ip::tcp::socket sock(ios); //����socket����
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"),6688); //�������Ӷ˵�

		sock.connect(ep); //socket ���Ӷ˵�

		vector<char> str(100, 0); //����һ��vector������
		sock.read_some(boost::asio::buffer(str)); //ʹ��bufffer()��װ��������������
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