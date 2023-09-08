#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// n이하의 소수들의 제곱수들의 배열을 만듦
void CalcDivisibleSquares(vector<long long>& S, long long n) {
	int sqrtn = sqrt(n);
	vector<bool> not_prime(sqrtn + 1);
	for (int i = 2; i <= sqrtn; i++) {
		if (not_prime[i]) continue;
		S.push_back((long long)i * i);
		for (int j = i; j <= sqrtn; j += i)
			not_prime[j] = true;
	}
}

// inclusion ans exclusion
void F(vector<long long>& S, int sz, int depth, int choose, long long square_mul, long long& res, long long n)
{
	if (depth == sz || square_mul > n / S[depth]) {
		if (choose > 0) {
			long long tp = n / square_mul;
			if (choose % 2 > 0) res += tp;
			else res -= tp;
		}
		return;
	}

	F(S, sz, depth + 1, choose, square_mul, res, n);
	F(S, sz, depth + 1, choose + 1, square_mul * S[depth], res, n);
}

// binary search
int UpperBound(vector<long long>& v, long long n)
{
	int lo = -1, hi = v.size();
	// v[lo] <= n < v[hi]
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (n >= v[mid])
			lo = mid;
		else
			hi = mid;
	}
	return hi;
}

int main()
{
	long long K;
	cin >> K;

	vector<long long> sqr_factor;
	sqr_factor.reserve(sqrt(26'000'000'000));
	CalcDivisibleSquares(sqr_factor, 26'000'000'000);

	long long lo = 0, hi = 26'000'000'000;
	//F(lo) < K <= F(hi)
	while (lo + 1 < hi) {
		long long mid = lo + (hi - lo) / 2;

		long long cnt = 0;
		F(sqr_factor, UpperBound(sqr_factor, mid), 0, 0, 1, cnt, mid);
		if (K > cnt)
			lo = mid;
		else
			hi = mid;
	}

	cout << hi;

	return 0;
}