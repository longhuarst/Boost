#include <boost/array.hpp>
#include <iostream>
#include <boost/typeof/typeof.hpp>

using namespace std;

int main(int argc, char *argv[])
{

	boost::array<int, 10> ar;

	ar[0] = 1;
	ar.back() = 10;

	assert(ar[ar.max_size() - 1] == 10);

	ar.assign(777);

	for (BOOST_AUTO(pos, ar.begin()); pos != ar.end(); ++pos)
	{
		cout << *pos << ",";
	}
	
	int *p = ar.c_array();
	*(p + 5) = 253;

	cout << ar[5] << endl;

	ar.at(8) = 666;
	sort(ar.begin(), ar.end());

	system("pause");
	return 0;
}