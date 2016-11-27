#include <iostream>
#include <fstream>
#include <vector>
#include <boost/progress.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
	vector<string> v(100);//一个字符串向量
	ofstream fs("text.txt");//文件输出流

	//申明一个progresss_display对象，基数是v的大小
	progress_display pd(v.size());

	//开始迭代遍历向量,处理字符串,写入文件
	vector<string>::iterator pos;
	for (pos=v.begin();pos!=v.end();++pos)
	{
		fs << *pos << endl;
		++pd;//更新进度显示
	}

	progress_display pd2(v.size(), cout, "%%%", "+++", "???");
	for (pos = v.begin(); pos != v.end(); ++pos)
	{
		fs << *pos << endl;
		++pd2;//更新进度显示
	}

	system("pause");


	return 0;
}