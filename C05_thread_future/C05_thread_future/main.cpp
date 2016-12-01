#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

using namespace std;

int fab(int n)
{
		if (n==0||n==1)
		{
			return 1;
		}
		return fab(n - 1) + fab(n - 2);
}


int main(int argc, char *argv[])
{

	//���� packaged_task ����,��ģ�����ָ������ֵ����
	//packaged_task ֻ�����޲κ���,�����Ҫʹ��bind
	boost::packaged_task<int> pt(boost::bind(fab, 10));

	//����unique_future����,����packaged_task��futureֵ,
	//ͬ��Ҫ��ģ�����ָ������ֵ����
	boost::unique_future<int> uf = pt.get_future();

	//�����̼߳���,����ʹ��boost::move()��ת��packaged_task����
	//���packaged_task�ǲ��ɿ�����
	boost::thread(boost::move(pt));
	uf.wait(); //unique_future�ȴ�������
	assert(uf.is_ready() && uf.has_value());
	cout << uf.get() << endl; //��������� 89

	system("pause");

	return 0;
}