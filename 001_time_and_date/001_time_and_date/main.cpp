#include <boost/timer.hpp>//timer的头文件
#include <iostream>//标准输入输出流


using namespace boost;//打开booost名字空间
using namespace std;//打开std名字空间

int main(int argc, char *argv[])
{

	timer t;//声明一个计时器对象,开始计时

	cout << "max timespan:" << t.elapsed_max() / 3600 << "h" << endl;//可度量的最大时间,以小时为单位
	cout << "min timespan:" << t.elapsed_min() << "s" << endl;//可度量的最小时间,以秒为单位
	
	//输出已经流逝的时间
	cout << "now time elapsed:" << t.elapsed() << "s" << endl;
	

	system("pause");
	

	return 0;
}