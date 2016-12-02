#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;


class a_timer
{
public:
	template<typename F> //模板类型,可以接受任意可调用物
	a_timer(boost::asio::io_service&ios, int x, F func) :
		f(func), //初始化回调函数和计数器
		count_max(x),
		count(0),
		t(ios, boost::posix_time::millisec(500)) //启动定时器
	{
		t.async_wait(boost::bind(&a_timer::call_func, this, boost::asio::placeholders::error)); //异步等待计时器 注册回调函数
	}

	void call_func(const boost::system::error_code &)
	{
		if (count >= count_max) //计数器达到上限值则退出
			return;
		++count;
		f(); //调用function对象
		t.expires_at(t.expires_at() + boost::posix_time::millisec(500)); //设置定时器的终止时间为0.5秒之后
		t.async_wait(boost::bind(&a_timer::call_func, this, boost::asio::placeholders::error)); //再次启动定时器,异步等待
	}
protected:
private:
	int count, count_max; //计数器成员变量
	boost::function<void()> f; //function对象,持有无参无返回的可调用物
	boost::asio::deadline_timer t; //asio定时器对象
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