#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> a(12, 0);
	vector<int> b(a.begin() + 12, a.end());
	cout << b.size();
	return 0;
}