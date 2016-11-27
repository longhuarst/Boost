#include <iostream>
#include <fstream>
#include <vector>
#include <boost/progress.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
	vector<string> v(100,"aaa");//一个字符串向量
	ofstream fs("text.txt");//文件输出流

	v[10] = "";
	v[23] = "";

							//申明一个progresss_display对象，基数是v的大小
	progress_display pd(v.size());

	//开始迭代遍历向量,处理字符串,写入文件
	vector<string>::iterator pos;
	for (pos = v.begin(); pos != v.end(); ++pos)
	{
		fs << *pos << endl;
		++pd;//更新进度显示

		if (pos->empty()) {
			cout << "null string # " << (pos - v.begin()) << endl;
		}
	}

	
	system("pause");


	return 0;
}