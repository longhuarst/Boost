#include <iostream>


#define BOOST_DATE_TIME_SOURCE

#include <libs/date_time/src/gregorian/greg_names.hpp>
#include <libs/date_time/src/gregorian/date_generators.cpp>
#include <libs/date_time/src/gregorian/greg_month.cpp>
#include <libs/date_time/src/gregorian/greg_weekday.cpp>
#include <libs/date_time/src/gregorian/gregorian_types.cpp>



using namespace boost::gregorian;
using namespace std;


int main(int argc, char *argv[])
{

	date d(2008, 11, 20);//ʵ������ʱ���ڿɴ�cin���
	date d_start(d.year(), d.month(), 1);//���µĵ�һ��
	date d_end = d.end_of_month();//�������һ��


	
	for (boost::gregorian::day_iterator d_iter(d_start); d_iter != d_end; ++d_iter)//�������ڵ����� ѭ����������
	{
		cout << (*d_iter).day()<< " "<< d_iter->day_of_week() << endl;//������ں�����
	}
	
	system("pause");
	
	return 0;
}