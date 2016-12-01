#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost::asio;

class a_timer
{
public:
	template<typename F> //模板类型,可以接受任意可调用物
	a_timer(io_service&ios, int x, F func) :
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
	deadline_timer t; //asio定时器对象
};

void print1()
{
	cout << "hello asio" << endl;
}

void print2()
{
	cout << "hello boost" << endl;
}


int main(int argc, char *argv[])
{
	io_service ios;

	a_timer at1(ios, 5, print1);
	a_timer at2(ios, 5, print2);

	ios.run();

	system("pause");
	
	return 0;
}