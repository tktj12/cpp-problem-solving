#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

using pii = pair<int,int>;

bool Compare(const pair<pii,int>& a,const pair<pii,int>& b) {
	return a.first.second < b.first.second;
}

int N,r,block_size,arr[100000];
int cnt[1'000'001],answers[100000];
vector<pair<pii,int>> mo[320];

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N;
	block_size = (int)sqrt(N);
	r = N / block_size;
	if (N % block_size > 0)r++;

	for (int i = 0; i < N; i++) cin >> arr[i];
	int Q; cin >> Q;
	for(int q=0;q<Q;q++) {
		int i,j; cin >> i >> j;
		i--,j--;
		mo[i / block_size].push_back({ {i,j}, q });
	}
	for (int i = 0; i < r; i++)
		sort(mo[i].begin(),mo[i].end(),Compare);

	int start = 0,end = -1, ans=0;
	for (int cur = 0; cur < r; cur++) {
		for (pair<pii,int>& q : mo[cur]) {
			int i = q.first.first;
			int j = q.first.second;

			int it;
			while (end < j) {
				it = arr[++end];
				if (++cnt[it] == 1) ans++;
			}
			while (end > j) {
				it = arr[end--];
				if (--cnt[it] == 0) ans--;
			}

			while (start < i) {
				it = arr[start++];
				if (--cnt[it] == 0) ans--;
			}
			while (start > i) {
				it = arr[--start];
				if (++cnt[it] == 1) ans++;
			}

			answers[q.second] = ans;
		}
	}
	
	for (int i = 0; i < Q; i++)
		cout << answers[i] << '\n';

	return 0;
}