#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1'000'000'007;

class SquareMatrix {
public:
	int m[8][8] = { 0, };

	int* operator[](int n) {
		return m[n];
	}

	SquareMatrix operator*(SquareMatrix& rhs) const {
		SquareMatrix ret;

		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				for (int k = 0; k < 8; k++)
					ret[i][j] = (ret[i][j] + ((long long)m[i][k] * rhs[k][j])) % MOD;

		return ret;
	}

	SquareMatrix operator^(int e) {
		if (e == 1) return *this;
		if (e % 2 > 0) return ((*this) ^ (e - 1)) * (*this);

		SquareMatrix ret = (*this) ^ (e / 2);
		return ret * ret;
	}
};

int main()
{
	int D; cin >> D;
	SquareMatrix mat;

	vector<int> adj[8] = { {1,2},{0,2,3},{0,1,3,4},{1,2,4,5},{2,3,5,7},{3,4,6},{5,7},{4,6} };
	for (int i = 0; i < 8; i++)
		for (int j : adj[i])
			mat[i][j] = mat[j][i] = 1;

	mat = mat ^ D;

	cout << mat[0][0];

	return 0;
}