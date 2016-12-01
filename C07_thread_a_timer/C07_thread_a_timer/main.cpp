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
	template<typename F> //ģ������,���Խ�������ɵ�����
	a_timer(io_service&ios, int x, F func) :
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
	deadline_timer t; //asio��ʱ������
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