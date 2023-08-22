#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

bool palindrome[2001][2001];
int arr[2001];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		palindrome[i][i] = true;
	}

	for (int i = 1; i < n; i++) {
		int s = i - 1, e = i + 1;
		while (0 < s && e <= n) {
			if (arr[s] != arr[e]) break;
			palindrome[s--][e++] = true;
		}
		s = i, e = i + 1;
		while (0 < s && e <= n) {
			if (arr[s] != arr[e]) break;
			palindrome[s--][e++] = true;
		}
	}

	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int s, e;
		cin >> s >> e;
		cout << palindrome[s][e] << '\n';
	}

	return 0;
}