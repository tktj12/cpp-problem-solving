#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
void Morse(int front_space, int backs, int& cnt);

vector<int> result;
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

		result.clear();
		Morse(n, m-1, k);
		int cnt = n + m;
		for (int i = result.size()-1; i >= 0; --i) {
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

void Morse(int front_space, int dits, int& cnt)
{
	if (dits == -1) {
		--cnt;
		return;
	}

	for (int i = 0; i <= front_space; ++i) {
		Morse(i, dits - 1, cnt);
		if (cnt == 0) {
			result.push_back(front_space - i);
			return;
		}
	}
}