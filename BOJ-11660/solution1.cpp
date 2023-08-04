#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int psum[1025][1025];

inline int PartSum(int x1, int y1, int x2, int y2)
{
	return psum[x2][y2] - psum[x1-1][y2] - psum[x2][y1-1] + psum[x1 - 1][y1 - 1];
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int line_sum = 0;
		for (int j = 1; j <= n; j++) {
			int num;
			cin >> num;
			line_sum += num;
			psum[i][j] = line_sum + psum[i-1][j];
		}
	}

	for (int i = 0; i < m; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		cout << PartSum(x1, y1, x2, y2) << '\n';
	}

	return 0;
}