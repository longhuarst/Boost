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
		
		io_service ios; //asio��������io_service����

		boost::asio::ip::tcp::acceptor acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 6688)); //����acceptor����,ipv4 ����6688�˿�
		cout << acceptor.local_endpoint().address()<< endl;


		while (true) //ѭ��ִ������
		{
			boost::asio::ip::tcp::socket sock(ios); //һ��socket ����
			acceptor.accept(sock); //�����ȴ�socket����

			cout << "client:" << sock.remote_endpoint().address() << endl;

			sock.write_some(buffer("hello asio")); //��������
			
		}
		
	}
	catch (std::exception & e) //������ܷ������쳣
	{
		cout << e.what() << endl;
	}

	system("pause");
	
	return 0;
}