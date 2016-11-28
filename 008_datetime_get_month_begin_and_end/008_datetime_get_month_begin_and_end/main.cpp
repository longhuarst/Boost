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

	date d(2008, 11, 20);//实际运行时日期可从cin获得
	date d_start(d.year(), d.month(), 1);//当月的第一天
	date d_end = d.end_of_month();//当月最后一天


	
	for (boost::gregorian::day_iterator d_iter(d_start); d_iter != d_end; ++d_iter)//构造日期迭代器 循环结束条件
	{
		cout << (*d_iter).day()<< " "<< d_iter->day_of_week() << endl;//输出日期和星期
	}
	
	system("pause");
	
	return 0;
}