#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


void CalcDivisibleSquares(vector<int>& S, int n) {
	int sqrtn = sqrt(n);
	vector<bool> not_prime(sqrtn+1);
	for (int i = 2; i <= sqrtn; i++) {
		if (not_prime[i]) continue;
		S.push_back(i * i);
		for (int j = i; j <= sqrtn; j += i)
			not_prime[j] = true;
	}
}

void F(vector<int>& S, int depth, int choose, long long square_mul, int& res, int n)
{
	if (depth == S.size()) {
		if (choose > 0) {
			int tp = n / square_mul;
			if (choose % 2 > 0) res += tp;
			else res -= tp;
		}
		return;
	}
	if (square_mul * S[depth] > n) {
		if (choose > 0) {
			int tp = n / square_mul;
			if (choose % 2 > 0) res += tp;
			else res -= tp;
		}
		return;
	}

	F(S,depth + 1, choose, square_mul, res, n);
	F(S, depth + 1, choose + 1, square_mul * S[depth],res,n);
}

int main()
{
	int K;
	cin >> K;

	int lo = 0, hi = 2'000'000'000;
	//F(lo) < K <= F(hi)
	while (lo + 1 < hi) {
		int mid = lo + (hi-lo) / 2;
		vector<int> S;
		S.reserve(sqrt(mid));
		CalcDivisibleSquares(S, mid);

		int cnt = 0;
		F(S, 0, 0, 1, cnt, mid);
		cnt = mid - cnt;
		if (K > cnt)
			lo = mid;
		else
			hi = mid;
	}
	
	cout << hi;
	
	return 0;
}