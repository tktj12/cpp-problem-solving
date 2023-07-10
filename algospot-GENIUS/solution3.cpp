#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Matrix {
public:
	vector<vector<double>> elements;
	int size;
	Matrix(int s) {
		size = s;
		elements = vector<vector<double>>(size);
		for (int i = 0; i < size; ++i)
			elements[i] = vector<double>(size,0.);
	}

	vector<double>& operator[](int n) {
		return elements[n];
	}

	Matrix operator*(Matrix& right) {
		Matrix ret(size);
		for(int i=0;i<size;++i)
			for (int j = 0; j < size; ++j)
				for (int k = 0; k < size; ++k)
					ret[i][j] += elements[i][k] * right[k][j];

		return ret;
	}

	Matrix operator^(int n) {
		if (n == 1) return *this;
		else if (n % 2 > 0) return (*this^(n - 1)) * (*this);
		Matrix ret = *this^(n / 2);
		return ret * ret;
	}
};

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << fixed;
	cout.precision(8);

	int tc;
	cin >> tc;
	while (tc--) {
		int N, K, M;
		vector<int> length;
		double T[50][50];

		cin >> N >> K >> M;
		length = vector<int>(N);
		for (int i = 0; i < N; ++i) cin >> length[i];
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				cin >> T[i][j];

		Matrix W(4*N);
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < N; ++j)
				W[i * N+j][(i + 1)*N + j] = 1.;

		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				W[3 * N + i][(4 - length[j]) * N + j] = T[j][i];

		Matrix S = W^K;

		for (int i = 0; i < M; ++i) {
			int query;
			cin >> query;
			double ans = 0.;
			for (int j = 0; j < length[query]; ++j)
				ans += S[(3 - j) * N + query][3 * N];

			cout << ans << ' ';
		}
		cout << '\n';
	}
	return 0;
}