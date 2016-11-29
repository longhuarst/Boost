#include <boost/thread.hpp>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>



using namespace std;


boost::mutex mu_io; //io流是个共享资源，不是线程安全的需要锁定

namespace boost {
	template<typename T>
	class base_atom :noncopyable
	{
	public:
		base_atom(T x=T()):n(x) {} //构造函数
		T operator++() //前置式递增操作符
		{
			mutex_t::scoped_lock lock(mu); //锁定互斥量
			return ++n;
		}
		operator T() { return n;} //类型转换操作符定义
	protected:
	private:
		T n;
		typedef mutex mutex_t; //互斥量类型定义
		mutex_t mu;
	};
}

typedef boost::base_atom<int> atom_int;

void printing(atom_int &x, const string & str)
{
	for (int i=0;i<5;++i)
	{
		boost::mutex::scoped_lock lock(mu_io); //锁定IO操作
		cout << str << ++x << endl;
	}
}


int main(int argc, char *argv[])
{
	atom_int x; //原子操作的计数器

	//使用临时 thread 对象启动线程
	boost::thread(printing, boost::ref(x), "hello"); //向函数传递多个参数
	boost::thread(printing, boost::ref(x), "boost"); //使用ref库传递引用
	boost::thread(printing, boost::ref(x), "good");

	boost::this_thread::sleep(boost::posix_time::seconds(2));

	system("pause");


	boost::thread t1(printing, boost::ref(x), "hello"); //向函数传递多个参数
	boost::thread t2(printing, boost::ref(x), "boost"); //使用ref库传递引用
	boost::thread t3(printing, boost::ref(x), "good");

	t1.timed_join(boost::posix_time::seconds(1)); //最多等待1秒后返回
	t2.join(); //等待t2线程结束再返回，不管执行多少时间
	t3.join();

	system("pause");

	boost::thread t4(boost::bind(printing, boost::ref(x), "hello")); //bind表达式
	
	boost::function<void()> f1 = boost::bind(printing, boost::ref(x), "boost");

	boost::thread t5  = boost::thread(f1); //使用boost表达式


	system("pause");

	boost::thread t6(boost::bind(printing, boost::ref(x), "hello")); //创建两个线程对象
	boost::thread t7(boost::bind(printing, boost::ref(x), "boost"));
	cout << "t6 id = " << t6.get_id() << endl; //输出t6的id
	assert(t6 != t7); //比较两个线程对象
	t6.detach(); //分离t6代表的线程执行体,单线程仍然继续运行
	assert(t6.get_id() == boost::thread::id());//t6不再标志任何线程

	system("pause");

	boost::thread::sleep(boost::get_system_time() + boost::posix_time::seconds(1));
	cout << "cpu core = " << boost::thread::hardware_concurrency() << endl;
	system("pause");
	return 0;
}

