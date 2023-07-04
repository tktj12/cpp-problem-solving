#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
string MakeString(string&);

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int N, P, L;
		cin >> N >> P >> L;
		string str = "FX";
		for (int i = 1; i <= N; i++)
			str = MakeString(str);
		string result(str.begin()+(P-1), str.begin()+(P+L-1));
		cout << result << '\n';
	}
	return 0;
}

string MakeString(string& before)
{
	string ret;
	for (char e : before) {
		if (e == 'X') 
			ret += "X+YF";
		else if (e == 'Y') 
			ret += "FX-Y";
		else 
			ret.push_back(e);
	}
	return ret;
}