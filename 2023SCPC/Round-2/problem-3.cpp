#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;


int ear[5000];
bool is_known[2][20];
bool picked[20];
int SolveNaive(int n, int m, int t, int pick_cnt)
{
	if (pick_cnt == m) {
		int ret = m;
		for (int i = 0; i < n; i++) {
			is_known[0][i] = picked[i];
			is_known[1][i] = 0;
		}

		for (int time = 0; time < t; time++) {
			bool now = time % 2, next = !now;
			for (int i = 0; i < n; i++) {
				if (is_known[now][i]) {
					is_known[next][i] = true;
					continue;
				}

				bool known_left = 0, known_right = 0;
				if (i > 0) known_left = is_known[now][i - 1];
				if (i < n - 1) known_right = is_known[now][i + 1];

				if (ear[i] == 1)
					is_known[next][i] = (known_left || known_right);
				else
					is_known[next][i] = (known_left && known_right);
				if (is_known[next][i]) ret++;
			}
		}
		return ret;
	}

	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (picked[i]) continue;
		picked[i] = true;
		ret = max(ret, SolveNaive(n, m, t, pick_cnt + 1));
		picked[i] = false;
	}
	return ret;
}

int main(int argc, char** argv)
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	int T, test_case;
	cin >> T;

	for (test_case = 0; test_case < T; test_case++)
	{
		memset(is_known, 0, sizeof(is_known));

		int n;
		cin >> n;
		for (int i = 0; i < n; i++) cin >> ear[i];

		int m, t;
		cin >> m >> t;
		
		cout << "Case #" << test_case + 1 << '\n';
		if (n > 20)
			cout << 0 << '\n';
		else
			cout << SolveNaive(n,m,t,0) << '\n';
	}

	return 0;
}