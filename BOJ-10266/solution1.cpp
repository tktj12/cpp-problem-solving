#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXV = 360'000;
const long long MOD = 1'000'000'007,BASE = 1009;
int clock1[200000],clock2[200000];
int gap1[200000],gap2[200000];

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n; cin >> n;
	for (int i = 0; i < n; i++)	cin >> clock1[i];
	for (int i = 0; i < n; i++)	cin >> clock2[i];
	sort(clock1,clock1 + n);
	sort(clock2,clock2 + n);

	int np = n - 1;
	int key=0, hash=0;
	long long mul = 1;
	for (int i = 0; i < np; i++) {
		gap1[i] = clock1[i + 1] - clock1[i];
		gap2[i] = clock2[i + 1] - clock2[i];
		key = (key * BASE + gap1[i]) % MOD;
		hash = (hash * BASE + gap2[i]) % MOD;
		mul = (mul * BASE) % MOD;
	}
	gap1[np] = MAXV - clock1[np] + clock1[0];
	gap2[np] = MAXV - clock2[np] + clock2[0];
	key = (key * BASE + gap1[np]) % MOD;
	hash = (hash * BASE + gap2[np]) % MOD;

	for (int i = 0; i < n; i++) {
		if (key == hash) {
			int j = 0;
			for (; j < n; j++) {
				int k = (i + j) % n;
				if (gap1[j] != gap2[k])
					break;
			}
			if (j == n) {
				cout << "possible";
				return 0;
			}
		}

		hash = ((hash + MOD - (gap2[i] * mul) % MOD)*BASE + gap2[i]) % MOD;
	}

	cout << "impossible";

	return 0;
}