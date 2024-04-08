#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

long long tree[300'000];
int arr[100000];
void Init(int node,int begin,int end) {
	if (begin == end) {
		tree[node] = arr[begin];
		return;
	}

	int child = node * 2,mid = (begin + end) / 2;
	Init(child,begin,mid);
	Init(child+1,mid+1,end);
	tree[node] = tree[child] + tree[child + 1];
}

void Update(int node,int begin,int end,int idx,int v) {
	if (idx < begin || end < idx) return;
	if (end == begin) {
		tree[node] = v;
		return;
	}

	int child = node * 2,mid = (begin + end) / 2;
	Update(child,begin,mid,idx,v);
	Update(child+1,mid+1,end,idx,v);
	tree[node] = tree[child] + tree[child + 1];
}

long long Query(int node,int begin,int end,int left,int right) {
	if (right < begin || end < left) return 0;
	if (left <= begin && end <= right) {
		return tree[node];
	}

	int child = node * 2,mid = (begin + end) / 2;
	return Query(child,begin,mid,left,right) + Query(child + 1,mid + 1,end,left,right);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int N; cin >> N;
	for (int i = 0; i < N; i++) cin >> arr[i];
	Init(1,0,N - 1);

	vector<tuple<int,int,int,int>> queries;
	vector<pair<int,int>> changes;
	int M; cin >> M;
	int idx = 0;
	while (M--) {
		int what; cin >> what;
		if (what == 1) {
			int i,v; cin >> i >> v;
			changes.push_back({ i-1,v });
		}
		else {
			int k,i,j; cin >> k >> i >> j;
			queries.push_back({ k,i-1,j-1,idx++ });
		}
	}
	sort(queries.begin(),queries.end());

	int change_idx = 0;
	long long answer[100000] = {};
	for (tuple<int,int,int,int>& q : queries) {
		int k,i,j,ans_idx;
		tie(k,i,j,ans_idx) = q;
		while (change_idx < k) {
			Update(1,0,N - 1,changes[change_idx].first,changes[change_idx].second);
			change_idx++;
		}
		answer[ans_idx] = Query(1,0,N - 1,i,j);
	}
	
	for (int i = 0; i < idx; i++)
		cout << answer[i] << '\n';
	
	return 0;
}