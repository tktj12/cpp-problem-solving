#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int Morse(int, int);
void FindAnswer(int, int, int&, vector<int>&);

int cache[100][100];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, m, k;
		cin >> n >> m >> k;

		memset(cache, 0, sizeof(cache));
		Morse(n, m-1);
		vector<int> result;
		FindAnswer(n, m - 1, k, result);


		int cnt = n + m;
		for (int i = result.size() - 1; i >= 0; --i) {
			for (int j = 0; j < result[i]; ++j) {
				cout << '-';
				--cnt;
			}
			cout << 'o';
			--cnt;
		}
		for (int i = 0; i < cnt; ++i)
			cout << '-';
		cout << '\n';
	}
	return 0;
}

int Morse(int front_dahs, int dits)
{
	int& ret = cache[front_dahs][dits];
	if (ret > 0) return ret;
	if (dits == -1) return ret = 1;

	for (int i = 0; i <= front_dahs; ++i)
		ret = min(1000000100, ret+ Morse(i, dits - 1));

	return ret;
}

void FindAnswer(int front_dahs, int dits, int& cnt, vector<int>& result)
{
	if (cache[front_dahs][dits] < cnt) {
		cnt -= cache[front_dahs][dits];
		return;
	}

	if (dits == -1) {
		--cnt;
		return;
	}

	for (int i = 0; i <= front_dahs; ++i) {
		FindAnswer(i, dits - 1, cnt, result);
		if (cnt == 0) {
			result.push_back(front_dahs - i);
			return;
		}
	}
}