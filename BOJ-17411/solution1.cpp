#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1'000'000, MOD = 1'000'000'007;

class Node {
public:
	long long sum = 0;
	int lo, hi, mid;
	Node* left = nullptr, * right = nullptr;

	Node(int l = 0, int h = 0) : lo(l), hi(h) {
		mid = (lo + hi) / 2;
	}
}new_node[4 * MAXN];
int node_cnt;

Node* NewNode(int lo, int hi) {
	new_node[node_cnt] = Node(lo, hi);
	return &new_node[node_cnt++];
}

void InsertST(int idx, long long sum, Node* here)
{
	if (here->lo == here->hi) {
		here->sum = sum;
		return;
	}

	if (here->mid >= idx) {
		if (!here->left)
			here->left = NewNode(here->lo, here->mid);

		InsertST(idx, sum, here->left);
	}
	else {
		if (!here->right)
			here->right = NewNode(here->mid + 1, here->hi);

		InsertST(idx, sum, here->right);
	}

	long long ls, rs = 0;
	ls = here->left->sum;
	if (here->right) rs = here->right->sum;

	here->sum = (ls + rs) % MOD;
}

long long GetSum(int lo, int hi, Node* here)
{
	if (lo <= here->lo && here->hi <= hi) return here->sum;
	else if (here->hi < lo || hi < here->lo) return 0;

	long long ret = GetSum(lo, hi, here->left);
	if (here->right) ret += GetSum(lo, hi, here->right);

	return ret % MOD;
}

vector<int> history[MAXN];
Node* segtree_root[MAXN];
int arr[MAXN + 1], lis[MAXN];
int lis_cnt;

int UnderBound(int n)
{
	int lo = -1, hi = lis_cnt;
	// lis[lo] > n >= lis[hi]
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (n >= lis[mid])
			hi = mid;
		else lo = mid;
	}

	return hi;
}

int UpperBound(int n, int idx)
{
	int lo = -1, hi = history[idx].size();
	// history[idx][lo] <= n < history[idx][hi]
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (n >= history[idx][mid])
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

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];

	for (int i = n - 1; i >= 0; i--) {
		int idx = UnderBound(arr[i]);
		if (idx == lis_cnt) {
			lis[lis_cnt++] = arr[i];
		}
		else { //arr[i] >= lis[idx]
			lis[idx] = arr[i];
		}

		long long sum = 1;
		if (idx > 0) {
			int lo = UpperBound(arr[i], idx - 1);
			sum = GetSum(lo, history[idx-1].size()-1, segtree_root[idx - 1]);
		}

		history[idx].push_back(arr[i]);
		int sz = history[idx].size() - 1;

		// 트리 키우기
		if (segtree_root[idx] == nullptr || segtree_root[idx]->hi < sz) {
			int hi;
			if (sz == 0) hi = 0;
			else hi = sz * 2 - 1;
			Node* new_head = NewNode(0, hi);

			new_head->left = segtree_root[idx];
			segtree_root[idx] = new_head;
		}
		InsertST(sz, sum, segtree_root[idx]);
	}


	cout << lis_cnt << ' ' << segtree_root[lis_cnt - 1]->sum;
	return 0;
}