#include <boost/timer.hpp>//timer��ͷ�ļ�
#include <iostream>//��׼���������


using namespace boost;//��booost���ֿռ�
using namespace std;//��std���ֿռ�

int main(int argc, char *argv[])
{

	timer t;//����һ����ʱ������,��ʼ��ʱ

	cout << "max timespan:" << t.elapsed_max() / 3600 << "h" << endl;//�ɶ��������ʱ��,��СʱΪ��λ
	cout << "min timespan:" << t.elapsed_min() << "s" << endl;//�ɶ�������Сʱ��,����Ϊ��λ
	
	//����Ѿ����ŵ�ʱ��
	cout << "now time elapsed:" << t.elapsed() << "s" << endl;
	

	system("pause");
	

	return 0;
}