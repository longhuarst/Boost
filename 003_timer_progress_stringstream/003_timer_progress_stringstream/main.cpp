#include <iostream>
#include <boost/progress.hpp>
#include <sstream>

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
	stringstream ss;

	{
		progress_timer pt(ss);
		//do something ...
	}

	cout << ss.str() << endl;
	system("pause");
	
	return 0;
}
