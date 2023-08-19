//말이 있을 수 있는 위치는 모두 30개이다.

#include <iostream>
#include <cstring>
using namespace std;

const int DIAMOND = 0, HORIZEN = 1, VERTICAL = 2;
int seq[100000];

int main(int argc, char** argv)
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	int T, test_case;
	cin >> T;

	for (test_case = 0; test_case < T; test_case++)
	{
		long long answer = 0;
		int n, k;
		cin >> n >> k;
		for (int i = 0; i < n; i++) cin >> seq[i];

		int cache[3][21], cache_state[3][21], cache_pos[3][21];
		memset(cache, -1, sizeof(cache));

		int state = DIAMOND, pos = 0;
		for (int i = 0; i < k; i++) {
			int& res = cache[state][pos];
			int& c_state = cache_state[state][pos];
			int& c_pos = cache_pos[state][pos];

			if (res != -1) {
				answer += res;
				state = c_state;
				pos = c_pos;
				continue;
			}
			res = 0;

			for (int j = 0; j < n; j++) {
				pos += seq[j];
				switch (state) {
				case DIAMOND:
					if (pos == 5) {
						state = HORIZEN;
						pos = 0;
					}
					else if (pos == 10) {
						state = VERTICAL;
						pos = 0;
					}
					else if (pos > 20) {
						res++;
						pos = 0;
					}
					break;
				case HORIZEN:
					if (pos == 3) {
						state = VERTICAL;
						pos = 3;
					}
					else if (pos >= 6) {
						state = DIAMOND;
						pos = 15 + pos - 6;
					}
					break;
				case VERTICAL:
					if (pos > 6) {
						res++;
						state = DIAMOND;
						pos = 0;
					}
					break;
				}
			}
			
			answer += res;
			c_state = state;
			c_pos = pos;
		}

		cout << "Case #" << test_case + 1 << '\n';
		cout << answer << '\n';
	}

	return 0;
}