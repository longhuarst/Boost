

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

using namespace boost::asio; //打开asio命名空间
using namespace std;

void print(const boost::system::error_code & /*e*/)
{
	cout << "hello asio" << endl;
}

int main(int argc, char *argv[])
{

	io_service ios; //所有asio程序必须要有一个io_service对象
	deadline_timer t(ios, boost::posix_time::seconds(2)); //定时器,io_service作为构造函数的参数 两秒钟后定时器终止

	cout << t.expires_at() << endl; //查看终止时间的绝对时间

	t.wait(); //调用wait()同步等待

	cout << "hello asio" << endl; //输出一条消息

	system("pause");

	io_service ios2;

	deadline_timer t2(ios2, boost::posix_time::seconds(2)); //定时器
	
	t2.async_wait(print); //异步等待,传入回调函数,立即返回

	cout << "it show before t expired." << endl;

	ios2.run(); //很重要!异步IO必须!

	system("pause");
	
	return 0;
}