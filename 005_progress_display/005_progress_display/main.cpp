#include <iostream>
#include <fstream>
#include <vector>
#include <boost/progress.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
	vector<string> v(100);//һ���ַ�������
	ofstream fs("text.txt");//�ļ������

	//����һ��progresss_display���󣬻�����v�Ĵ�С
	progress_display pd(v.size());

	//��ʼ������������,�����ַ���,д���ļ�
	vector<string>::iterator pos;
	for (pos=v.begin();pos!=v.end();++pos)
	{
		fs << *pos << endl;
		++pd;//���½�����ʾ
	}

	progress_display pd2(v.size(), cout, "%%%", "+++", "???");
	for (pos = v.begin(); pos != v.end(); ++pos)
	{
		fs << *pos << endl;
		++pd2;//���½�����ʾ
	}

	system("pause");


	return 0;
}