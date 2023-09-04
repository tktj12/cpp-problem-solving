#include <iostream>
#include <vector>
using namespace std;

const long long MAXK = 1'000'000'001'000'000'010;
const int MAXN = 100'000;

class Node {
public:
	long long sum = 0;
	int lo, hi, mid;
	Node* left = nullptr, * right = nullptr;

	Node(int l = 0, int history = 0) : lo(l), hi(history) {
		mid = (lo + hi) / 2;
	}
}new_node[4 * MAXN];
int node_cnt;

inline Node* NewNode(int lo, int hi) {
	new_node[node_cnt] = Node(lo, hi);
	return &new_node[node_cnt++];
}

void InsertST(int idx, long long sum, Node* root)
{
	if (root->lo == root->hi) {
		root->sum = sum;
		return;
	}

	if (root->mid >= idx) {
		if (!root->left)
			root->left = NewNode(root->lo, root->mid);

		InsertST(idx, sum, root->left);
	}
	else {
		if (!root->right)
			root->right = NewNode(root->mid + 1, root->hi);

		InsertST(idx, sum, root->right);
	}

	long long ls, rs = 0;
	ls = root->left->sum;
	if (root->right) rs = root->right->sum;

	root->sum = min(ls + rs, MAXK);
}

long long GetSum(int lo, int hi, Node* root)
{
	if (lo <= root->lo && root->hi <= hi) return root->sum;
	else if (root->hi < lo || hi < root->lo) return 0;

	long long ret = GetSum(lo, hi, root->left);
	if (root->right) ret += GetSum(lo, hi, root->right);

	return ret = min(ret, MAXK);
}

struct Dat {
	int lo, hi, num;
	long long sum;
};

vector<Dat> history[MAXN];
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
	// history[idx][lo].num <= n < history[idx][hi].num
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (n >= history[idx][mid].num)
			lo = mid;
		else hi = mid;
	}
	return hi;
}

int RangeUpperBound(int lo, int hi, int idx, int n)
{
	// h[idx][lo].num <= n < h[idx][hi].num
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (n >= history[idx][mid].num)
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
	long long k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> arr[i];

	for (int i = n - 1; i >= 0; i--) {
		int idx = UnderBound(arr[i]);
		bool same = false;
		if (idx == lis_cnt) {
			lis[lis_cnt++] = arr[i];
		}
		else { //arr[i] >= lis[idx]
			if (lis[idx] == arr[i]) same = true;
			else lis[idx] = arr[i];
		}

		int hi = 0;
		if (idx > 0) hi = history[idx - 1].size() - 1;

		long long sum = 1;
		int lo = 0;
		if (idx > 0) {
			lo = UpperBound(arr[i], idx - 1);
			sum = GetSum(lo, history[idx - 1].size() - 1, segtree_root[idx - 1]);

			if (same) lo = history[idx].back().hi + 1;
		}

		history[idx].push_back({ lo,hi,arr[i],sum });
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

	vector<int> ans;
	ans.reserve(n);

	k--;
	int lo = 0, hi = history[lis_cnt - 1].size() - 1;
	long long mul = 1;
	for (int i = lis_cnt - 1; i >= 0; i--) {
		bool able = false;
		for (int j = lo; j <= hi; j++) {
			if (i == 0 && j > lo && history[i][j].num == history[i][j - 1].num) continue;

			long long same_cnt = RangeUpperBound(j, hi + 1, i, history[i][j].num) - j;
			long long sum = 1;
			if (i > 0)
				sum = GetSum(history[i][j].lo, history[i][j].hi, segtree_root[i - 1]);

			long long tp1;
			if (mul > MAXK / same_cnt) tp1 = MAXK;
			else tp1 = mul * same_cnt;

			long long tp2;
			if (sum > MAXK / tp1) tp2 = MAXK;
			else tp2 = sum * tp1;

			if (tp2 <= k) {
				k -= tp2;
			}
			else {
				ans.push_back(history[i][j].num);
				lo = history[i][j].lo;
				hi = history[i][j].hi;
				mul = tp1;
				able = true;
				break;
			}
		}

		if (!able) {
			cout << -1;
			return 0;
		}
	}

	for (int e : ans)
		cout << e << ' ';

	return 0;
}