#include <boost/thread.hpp>
#include <iostream>


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




	return 0;
}
