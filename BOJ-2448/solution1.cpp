#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

void Put(int line, vector<string>& ans)
{
	ans[line]   += "  *  ";
	ans[line+1] += " * * ";
	ans[line+2] += "*****";
}

void Make(int n, int line, vector<string>& ans)
{
	if (n == 3) {Put(line, ans); return;}
	n /= 2;

	string blanks;
	for (int i = 0; i < n; i++) blanks += ' ';
	for (int i = 0; i < n; i++)
		ans[line + i] += blanks;

	Make(n, line, ans);
	for (int i = 0; i < n; i++)
		ans[line + i] += blanks;

	Make(n, line + n, ans);
	for (int i = 0; i < n; i++)
		ans[line + n + i] += ' ';
	Make(n, line + n, ans);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;

	vector<string> ans(n);
	Make(n, 0, ans);

	string real_ans;
	real_ans.reserve(4 * n * n);
	for (int i = 0; i < n; i++) {
		real_ans += ans[i];
		real_ans += '\n';
	}
	cout << real_ans;

	return 0;
}