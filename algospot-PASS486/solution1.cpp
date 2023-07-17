#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;
void eratosthenes();
int CntFactor(int);

const int MAXN = 10000000;
int min_factor[MAXN+1];	// min_factor[i] : 자연수 i의 가장 작은 소인수를 저장
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	eratosthenes();
	

	int tc;
	cin >> tc;
	while (tc--) {
		int k, lo, hi;
		cin >> k >> lo >> hi;
		int ans = 0;
		for (int i = lo; i <= hi; ++i)
			if (CntFactor(i) == k) ++ans;
		cout << ans << '\n';
	}
	return 0;
}

void eratosthenes()
{
	for (int i = 1; i <= MAXN; i+=2) min_factor[i] = i;
	for (int i = 2; i <= MAXN; i+=2) min_factor[i] = 2;

	int sqrtn = int(sqrt(MAXN));
	for (int i = 3; i <= sqrtn; ++i) {
		if (min_factor[i] != i) continue;
		for (int j = i * i; j <= MAXN; j += i) {
			if (min_factor[j] == j) {
				min_factor[j] = i;
			}
		}
	}
}
// 자연수 n의 소인수 개수 계산
int CntFactor(int n)
{
	if (n == 1) return 1;

	int res = 1;
	int prev = -1, succession=0;
	while (n > 1) {
		if (min_factor[n] == prev) {
			++succession;
		}
		else {
			res *= succession+1;
			prev = min_factor[n];
			succession = 1;
		}
		n /= min_factor[n];
	}
	return res * (succession+1);
}