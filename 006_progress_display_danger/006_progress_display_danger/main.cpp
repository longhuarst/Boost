#include <iostream>
#include <fstream>
#include <vector>
#include <boost/progress.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
	vector<string> v(100,"aaa");//һ���ַ�������
	ofstream fs("text.txt");//�ļ������

	v[10] = "";
	v[23] = "";

							//����һ��progresss_display���󣬻�����v�Ĵ�С
	progress_display pd(v.size());

	//��ʼ������������,�����ַ���,д���ļ�
	vector<string>::iterator pos;
	for (pos = v.begin(); pos != v.end(); ++pos)
	{
		fs << *pos << endl;
		++pd;//���½�����ʾ

		if (pos->empty()) {
			cout << "null string # " << (pos - v.begin()) << endl;
		}
	}

	
	system("pause");


	return 0;
}