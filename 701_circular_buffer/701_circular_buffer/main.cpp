#include <boost/circular_buffer.hpp>
#include <iostream>
#include <boost/typeof/typeof.hpp>

using namespace std;


int main(int argc, char *argv[])
{
	boost::circular_buffer<int> cb(5);
	assert(cb.empty());

	cb.push_back(1);
	cb.push_front(2);

	assert(cb.front() == 2);
	cb.insert(cb.begin(), 3);

	for (BOOST_AUTO(pos, cb.begin()); pos != cb.end(); ++pos)
	{
	cout << *pos << ",";
	}
	cout << endl;

	cb.pop_front();
	assert(cb.size() == 2);
	cb.push_back();
	assert(cb[0] == 2);
	

	system("pause");


	return 0;
}