

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

using namespace boost::asio; //��asio�����ռ�
using namespace std;

void print(const boost::system::error_code & /*e*/)
{
	cout << "hello asio" << endl;
}

int main(int argc, char *argv[])
{

	io_service ios; //����asio�������Ҫ��һ��io_service����
	deadline_timer t(ios, boost::posix_time::seconds(2)); //��ʱ��,io_service��Ϊ���캯���Ĳ��� �����Ӻ�ʱ����ֹ

	cout << t.expires_at() << endl; //�鿴��ֹʱ��ľ���ʱ��

	t.wait(); //����wait()ͬ���ȴ�

	cout << "hello asio" << endl; //���һ����Ϣ

	system("pause");

	io_service ios2;

	deadline_timer t2(ios2, boost::posix_time::seconds(2)); //��ʱ��
	
	t2.async_wait(print); //�첽�ȴ�,����ص�����,��������

	cout << "it show before t expired." << endl;

	ios2.run(); //����Ҫ!�첽IO����!

	system("pause");
	
	return 0;
}