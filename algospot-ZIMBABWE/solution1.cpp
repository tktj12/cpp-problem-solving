#include <iostream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;
int solve(vector<int>);
long long convert(vector<int>);

vector<int> now;
int M;
long long now_num;
const int MOD = 1000000007;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		now.clear();

		char tp = 0;
		while (tp < '0' || '9' < tp)
			cin.get(tp);
		while ('0' <= tp && tp <= '9') {
			now.push_back(tp - '0');
			cin.get(tp);
		}
		cin >> M;

		now_num = 0;
		for (int i = 0; i < now.size(); ++i) {
			now_num *= 10;
			now_num += now[i];
		}

		cout << solve({}) << '\n';
	}
	return 0;
}

int solve(vector<int> select)
{
	if (select.size() == now.size()) {
		long long cand = convert(select);
		if (cand < now_num && cand % M == 0) return 1;
		else return 0;
	}

	int ret(0);
	bool cont;
	vector<bool> selected(10, false);
	for (int i = 0; i < now.size(); i++) {
		cont = false;
		for (int j = 0; j < select.size(); j++)
			if (i == select[j]) {
				cont = true;
				break;
			}
		if (cont) continue;

		if (selected[now[i]] == true) continue;
		else selected[now[i]] = true;

		vector<int> next = select;
		next.push_back(i);
		ret = (ret + solve(next)) % MOD;
	}
	return ret;
}

long long convert(vector<int> select)
{
	long long ret = 0;
	for (int i = 0; i < select.size(); i++) {
		ret *= 10;
		ret += now[select[i]];
	}
	return ret;
}