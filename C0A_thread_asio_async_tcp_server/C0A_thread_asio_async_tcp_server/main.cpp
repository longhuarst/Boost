#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;


class a_timer
{
public:
	template<typename F> //ģ������,���Խ�������ɵ�����
	a_timer(boost::asio::io_service&ios, int x, F func) :
		f(func), //��ʼ���ص������ͼ�����
		count_max(x),
		count(0),
		t(ios, boost::posix_time::millisec(500)) //������ʱ��
	{
		t.async_wait(boost::bind(&a_timer::call_func, this, boost::asio::placeholders::error)); //�첽�ȴ���ʱ�� ע��ص�����
	}

	void call_func(const boost::system::error_code &)
	{
		if (count >= count_max) //�������ﵽ����ֵ���˳�
			return;
		++count;
		f(); //����function����
		t.expires_at(t.expires_at() + boost::posix_time::millisec(500)); //���ö�ʱ������ֹʱ��Ϊ0.5��֮��
		t.async_wait(boost::bind(&a_timer::call_func, this, boost::asio::placeholders::error)); //�ٴ�������ʱ��,�첽�ȴ�
	}
protected:
private:
	int count, count_max; //��������Ա����
	boost::function<void()> f; //function����,�����޲��޷��صĿɵ�����
	boost::asio::deadline_timer t; //asio��ʱ������
};

class server
{
private:
	boost::asio::io_service &ios;
	boost::asio::ip::tcp::acceptor acceptor;
	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> sock_pt;

public:
	server(boost::asio::io_service & io):
		ios(io),
		acceptor(ios,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),6688))
	{
		start();
	}

	void start()
	{
		sock_pt sock(new boost::asio::ip::tcp::socket(ios));

		acceptor.async_accept(*sock, boost::bind(&server::accept_handler, this, boost::asio::placeholders::error, sock));
	}

	void accept_handler(const boost::system::error_code &ec, sock_pt sock)
	{
		if (ec)
			return;

		cout << "client:" << sock->remote_endpoint().address() << endl;
		sock->async_write_some(boost::asio::buffer("hello asio"), boost::bind(&server::write_handler, this, boost::asio::placeholders::error));
		
		start();
	}

	void write_handler(const boost::system::error_code&)
	{
		cout << "send msg complete." << endl;
	}



};


int main(int argc, char *argv[])
{
	try
	{
		cout << "server start." << endl;
		boost::asio::io_service ios;

		server serv(ios);
		ios.run();
	}
	catch (std::exception &e) 
	{
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}