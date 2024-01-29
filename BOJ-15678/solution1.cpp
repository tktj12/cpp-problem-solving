#include <iostream>
#include <cstring>
using namespace std;

int N, D;
int score[100000];
long long seg_tree[300000];
const long long NEGATIVE_INF = 0x8000000000000000LL;

void Add(int node, int left, int right, int pos, long long val)
{
	if (left == right) {
		seg_tree[node] = val;
		return;
	}

	int mid = (left + right) / 2;
	int next_node = 2*node;
	if (pos <= mid) 
		Add(next_node, left, mid, pos, val);
	else
		Add(++next_node, mid+1, right, pos, val);
	
	seg_tree[node] = max(seg_tree[node], seg_tree[next_node]);
}

long long Query(int node, int node_left, int node_right, int left, int right)
{
	if (node_right < left || right < node_left)
		return NEGATIVE_INF;
	else if (left <= node_left && node_right <= right)
		return seg_tree[node];

	int mid = (node_left + node_right) / 2;
	long long l = Query(2*node, node_left, mid, left, right);
	long long r = Query(2*node+1, mid+1, node_right, left, right);
	
	return max(l, r);
}

long long DP(int pos)
{
	long long ret = score[pos];

	if (pos > 0) {
		int left = pos - D, right = pos - 1;
		if (left < 0) left = 0;

		long long max_benefit = Query(1,0,N-1, left, right);

		if (max_benefit > 0) ret += max_benefit;
	}

	Add(1, 0, N - 1, pos, ret);

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	memset(seg_tree, 0x81, sizeof(seg_tree));

	cin >> N >> D;
	for (int i = 0; i < N; i++)
		cin >> score[i];

	long long max = score[0];
	for (int i = 0; i < N; i++) {
		long long tp = DP(i);
		if (tp > max)
			max = tp;
	}

	cout << max; 
	
	return 0;
}