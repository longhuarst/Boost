#include <boost/thread.hpp>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>



using namespace std;


boost::mutex mu_io; //io���Ǹ�������Դ�������̰߳�ȫ����Ҫ����

namespace boost {
	template<typename T>
	class base_atom :noncopyable
	{
	public:
		base_atom(T x=T()):n(x) {} //���캯��
		T operator++() //ǰ��ʽ����������
		{
			mutex_t::scoped_lock lock(mu); //����������
			return ++n;
		}
		operator T() { return n;} //����ת������������
	protected:
	private:
		T n;
		typedef mutex mutex_t; //���������Ͷ���
		mutex_t mu;
	};
}

typedef boost::base_atom<int> atom_int;

void printing(atom_int &x, const string & str)
{
	for (int i=0;i<5;++i)
	{
		boost::mutex::scoped_lock lock(mu_io); //����IO����
		cout << str << ++x << endl;
	}
}


int main(int argc, char *argv[])
{
	atom_int x; //ԭ�Ӳ����ļ�����

	//ʹ����ʱ thread ���������߳�
	boost::thread(printing, boost::ref(x), "hello"); //�������ݶ������
	boost::thread(printing, boost::ref(x), "boost"); //ʹ��ref�⴫������
	boost::thread(printing, boost::ref(x), "good");

	boost::this_thread::sleep(boost::posix_time::seconds(2));

	system("pause");


	boost::thread t1(printing, boost::ref(x), "hello"); //�������ݶ������
	boost::thread t2(printing, boost::ref(x), "boost"); //ʹ��ref�⴫������
	boost::thread t3(printing, boost::ref(x), "good");

	t1.timed_join(boost::posix_time::seconds(1)); //���ȴ�1��󷵻�
	t2.join(); //�ȴ�t2�߳̽����ٷ��أ�����ִ�ж���ʱ��
	t3.join();

	system("pause");

	boost::thread t4(boost::bind(printing, boost::ref(x), "hello")); //bind���ʽ
	
	boost::function<void()> f1 = boost::bind(printing, boost::ref(x), "boost");

	boost::thread t5  = boost::thread(f1); //ʹ��boost���ʽ


	system("pause");

	boost::thread t6(boost::bind(printing, boost::ref(x), "hello")); //���������̶߳���
	boost::thread t7(boost::bind(printing, boost::ref(x), "boost"));
	cout << "t6 id = " << t6.get_id() << endl; //���t6��id
	assert(t6 != t7); //�Ƚ������̶߳���
	t6.detach(); //����t6������߳�ִ����,���߳���Ȼ��������
	assert(t6.get_id() == boost::thread::id());//t6���ٱ�־�κ��߳�

	system("pause");

	boost::thread::sleep(boost::get_system_time() + boost::posix_time::seconds(1));
	cout << "cpu core = " << boost::thread::hardware_concurrency() << endl;
	system("pause");
	return 0;
}

