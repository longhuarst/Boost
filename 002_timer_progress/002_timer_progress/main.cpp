#include <boost/progress.hpp>

int main(int argc, char *argv[])
{
	{
		boost::progress_timer t;//声明对象开始计时
		//do something ...
	}//退出作用域，调用progress_timer的析构函数

	system("pause");
	return 0;
}
