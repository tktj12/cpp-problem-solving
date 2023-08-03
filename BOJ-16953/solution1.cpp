#include <iostream>
using namespace std;

int RecursiveFind(long long k, long long now, int depth)
{
	if (now > k) return -1;
	else if (now == k) return depth;

	int a = RecursiveFind(k, 2 * now, depth + 1);
	int b = RecursiveFind(k, 10 * now + 1, depth + 1);

	if (a != -1 && b != -1)
		return min(a, b);
	else if (a != -1)
		return a;
	else
		return b;
}

int main()
{
	long long a, b;
	cin >> a >> b;
	cout << RecursiveFind(b, a, 1);

	return 0;
}