#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MOD_NUM 1000000007

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int all_cases[101] = { 1,1,2, };
	for (int i = 3; i <= 100; ++i) 
		all_cases[i] = (all_cases[i - 1] + all_cases[i - 2]) % MOD_NUM;

	int tc;
	cin >> tc;
	while (tc--) {
		int n, symmetric_cases;
		cin >> n;
		if (n % 2 == 0) symmetric_cases = (all_cases[n/2] + all_cases[n/2 - 1]) % MOD_NUM;
		else symmetric_cases = all_cases[n/2];
		cout << (MOD_NUM + all_cases[n] - symmetric_cases) % MOD_NUM << '\n';
	}
	return 0;
}