#include <iostream>
using namespace std;

const long long MOD_NUM = 1000000007;

class FibMatrix {
public:
	long long e[2][2] = { 0, 1, 1, 1 };

	FibMatrix operator*(const FibMatrix& mat) const {
		FibMatrix ret;
		ret.e[0][0] = ( e[0][0]*mat.e[0][0] + e[0][1]*mat.e[1][0] ) % MOD_NUM;
		ret.e[0][1] = ( e[0][0]*mat.e[0][1] + e[0][1]*mat.e[1][1] ) % MOD_NUM;
		ret.e[1][0] = ( e[1][0]*mat.e[0][0] + e[1][1]*mat.e[1][0] ) % MOD_NUM;
		ret.e[1][1] = ( e[1][0]*mat.e[0][1] + e[1][1]*mat.e[1][1] ) % MOD_NUM;
		return ret;
	}
};

FibMatrix MatPow(const FibMatrix& mat, long long n)
{
	if (n == 1) return mat;

	if (n % 2 > 0) return MatPow(mat, n - 1) * mat;
	else {
		FibMatrix ret = MatPow(mat, n / 2);
		return ret * ret;
	}
}

int main()
{
	long long n;
	cin >> n;

	if (n == 1) cout << '1';
	else cout << MatPow(FibMatrix(), n-1).e[1][1];

	return 0;
}