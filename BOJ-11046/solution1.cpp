#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int arr[2000001], M[2000001];
void Manacher(int n)
{
	int p = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i >= r) {
			p = i;
			r = i + 1;
			while (r < n && r <= 2 * p && arr[r] == arr[2 * p - r]) r++;
			M[i] = r - p - 1;
		}
		else {
			int j = 2 * p - i;
			if (M[j] < r - i - 1)
				M[i] = M[j];
			else if (M[j] > r - i - 1)
				M[i] = r - i - 1;
			else {
				p = i;
				while (r < n && r <= 2 * p && arr[r] == arr[2 * p - r]) r++;
				M[i] = r - p - 1;
			}
		}
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[2 * i + 1];
	}
	Manacher(2 * n + 1);

	int m,s,e;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> s >> e;
		cout << (M[s + e-1] >= e - s+1) << '\n';
	}
	return 0;
}