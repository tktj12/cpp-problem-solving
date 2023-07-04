#include <iostream>
#include <vector>
using namespace std;
void solve(int);

int skip, print_len;
int cache[51] = { 2, };
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	for (int i = 1; i <= 50; i++)
		cache[i] = (int)min( (1LL << (i-1)) *3 +cache[i-1], 1234567890LL );

	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n >> skip >> print_len;
		skip--;
		solve(n);
		cout << '\n';
	}
	return 0;
}

void solve(int gen)
{
	if (gen == 0) {
		string str = "FX";
		for (int i = 0; i < 2; i++) {
			if (skip == 0) {
				if (print_len) {
					print_len--;
					cout << str[i];
				}
			}
			else skip--;
		}
		return;
	}

	for (int i = gen - 1; i >= 0 && print_len; i--) {
		if (skip >= cache[i])
			skip -= cache[i];
		else solve(i);

		if (skip == 0) {
			if (print_len) {
				print_len--;
				if (i == gen - 1) cout << '+';
				else cout << '-';
			}
		}
		else skip--;
	}

	string str = "YF";
	for (int i = 0; i < 2; i++) {
		if (skip == 0) {
			if (print_len) {
				print_len--;
				cout << str[i];
			}
		}
		else skip--;
	}
}