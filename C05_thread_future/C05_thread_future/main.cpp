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

	//声明 packaged_task 对象,用模板参数指明返回值类型
	//packaged_task 只接受无参函数,因此需要使用bind
	boost::packaged_task<int> pt(boost::bind(fab, 10));

	//声明unique_future对象,接受packaged_task的future值,
	//同样要用模板参数指明返回值类型
	boost::unique_future<int> uf = pt.get_future();

	//启动线程计算,必须使用boost::move()来转移packaged_task对象
	//因此packaged_task是不可拷贝的
	boost::thread(boost::move(pt));
	uf.wait(); //unique_future等待计算结果
	assert(uf.is_ready() && uf.has_value());
	cout << uf.get() << endl; //输出计算结果 89

	system("pause");

	return 0;
}