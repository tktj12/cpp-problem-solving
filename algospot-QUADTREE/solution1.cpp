#include <iostream>
#include <string>

using namespace std;
string InvertData(string& data, int first);

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--)
	{
		string data;
		cin >> data;
		cout << InvertData(data, 0) << '\n';
	}

	return 0;
}

string InvertData(string& data, int first)
{
	if (data[first] != 'x') return string(1,data[first]);

	string a, b, c, d;
	a = InvertData(data, first + 1);
	b = InvertData(data, first + 1 + a.size());
	c = InvertData(data, first + 1 + a.size() + b.size());
	d = InvertData(data, first + 1 + a.size() + b.size() + c.size());

	return 'x' + c + d + a + b;
}