#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int arr[100000], a_to_b[500001], b_to_a[500001], lis[100000], immed_surb[500001];
int N, lis_cnt;

void Sort()
{
	int idx = 0;
	for (int i = 1; i <= 500000; i++)
		if (a_to_b[i]) arr[idx++] = a_to_b[i];
}

int LowerBound(int n)
{
	int lo = -1, hi = lis_cnt;
	// lis[lo] < lis[mid] <= lis[hi]
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (n > lis[mid])
			lo = mid;
		else hi = mid;
	}

	return hi;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int a, b;
		cin >> a >> b;
		a_to_b[a] = b;
		b_to_a[b] = a;
	}

	Sort();

	for (int i = 0; i < N; i++) {
		int idx = LowerBound(arr[i]);
		if (idx == lis_cnt) {
			lis[lis_cnt++] = arr[i];
		}
		else { //arr[i] < lis[idx]
			lis[idx] = arr[i];
		}
		if (idx > 0) immed_surb[arr[i]] = lis[idx - 1];
	}

	int b = lis[lis_cnt - 1];
	a_to_b[b_to_a[b]] = 0;
	for (int i = 0; i < lis_cnt-1; i++) {
		b = immed_surb[b];
		int a = b_to_a[b];
		a_to_b[a] = 0;
	}

	cout << N - lis_cnt << '\n';
	for (int i = 1; i <= 500000; i++)
		if (a_to_b[i]) cout << i << '\n';

	return 0;
}