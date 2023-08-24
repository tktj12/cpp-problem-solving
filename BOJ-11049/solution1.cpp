#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int r = 0, c = 1;
int M[500][2], cache[500][500];

int DP(int left, int right) {
	if (left == right) return 0;

	int& ret = cache[left][right];
	if (ret > 0) return ret;
	ret = 0x7FFFFFFF;

	int tp = M[left][r] * M[right][c];
	for(int i=left;i<right;i++)
		ret = min(ret, DP(left, i) + DP(i + 1, right) + tp*M[i][c]);

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> M[i][r] >> M[i][c];
	cout << DP(0, n - 1);

	return 0;
}