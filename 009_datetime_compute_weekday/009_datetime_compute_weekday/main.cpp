#include <iostream>

#define BOOST_DATE_TIME_SOURCE
#include <libs/date_time/src/gregorian/greg_names.hpp>
#include <libs/date_time/src/gregorian/date_generators.cpp>
#include <libs/date_time/src/gregorian/greg_month.cpp>
#include <libs/date_time/src/gregorian/greg_weekday.cpp>
#include <libs/date_time/src/gregorian/gregorian_types.cpp>

using namespace std;
using namespace boost::gregorian;



int main(int argc, char *argv[])
{
	date d(2008, 11, 20);
	date d18years = d + years(18);
	cout << to_simple_string(d18years) << " is ";
	cout<< d18years.day_of_week() << endl;

	int count = 0;
	for (boost::gregorian::day_iterator d_iter(date(d18years.year(), 11, 1));d_iter != d18years.end_of_month();++d_iter)
	{
		if (d_iter->day_of_week() == Sunday) {
			++count;
		}
	}
	cout << "total " << count << " Sundays." << endl;

	count = 0;
	for (month_iterator m_iter(date(d18years.year(), 1, 1)); m_iter < date(d18years.year() + 1, 1, 1); ++m_iter)
	{
		count += m_iter->end_of_month().day();
	}
	cout << "total " << count << " days of years." << endl;
	
	system("pause");
	
	return 0;
}