#include <iostream>
#include <vector>
using namespace std;

const long long MAXK = 1'000'000'000'000'000'010;
const int MAXN = 100'000;

class Node {
public:
	long long sum = 0;
	int lo, hi, mid;
	Node* left = nullptr , * right = nullptr;

	Node(int l = 0, int h = 0) : lo(l), hi(h) {
		mid = (lo + hi) / 2;
	}
}new_node[4 * MAXN];
int node_cnt;

inline Node* NewNode(int lo, int hi) {
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
			here->right = NewNode(here->mid+1, here->hi);

		InsertST(idx, sum, here->right);
	}

	long long ls, rs=0;
	ls = here->left->sum;
	if (here->right) rs = here->right->sum;

	here->sum = min(ls + rs, MAXK);
}

long long GetSum(int lo, int hi, Node* here)
{
	if (lo <= here->lo && here->hi <= hi) return here->sum;
	else if (here->hi < lo || hi < here->lo) return 0;

	long long ret = GetSum(lo, hi, here->left);
	if (here->right) ret += GetSum(lo, hi, here->right);

	return ret = min(ret, MAXK);
}

Node* segtree_root[MAXN];
int arr[MAXN+1], lis[MAXN], prv[MAXN+1];
long long DP[MAXN+1];
vector<int> history[MAXN];
int lis_cnt;

int UnderBound(int n)
{
	int lo = -1, hi = lis_cnt;
	// lis[lo] >= n > lis[hi]
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (n > lis[mid])
			hi = mid;
		else lo = mid;
	}

	return hi;
}

int LowerBound(int n, int idx)
{
	int lo = -1, hi = history[idx].size();
	// history[idx][lo] < n <= history[idx][hi]
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (n > history[idx][mid])
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

	for (int i = n-1; i >= 0; i--) {
		int idx = UnderBound(arr[i]);
		if (idx == lis_cnt) {
			lis[lis_cnt++] = arr[i];
		}
		else { //arr[i] > lis[idx]
			lis[idx] = arr[i];
		}

		if (idx > 0) prv[arr[i]] = history[idx-1].size()-1;

		long long sum=1;
		if(idx>0) {
			int lo = LowerBound(arr[i], idx - 1);
			sum = GetSum(lo, history[idx - 1].size() - 1, segtree_root[idx - 1]);
		}
		DP[arr[i]] = sum;

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

	vector<int> ans;
	ans.reserve(n);

	k--;
	int p = history[lis_cnt-1].size()-1;
	int prev = 0;
	for (int i = lis_cnt - 1; i >= 0; i--) {
		bool able = false;
		for (int j = 0; j <= p; j++) {
			if (history[i][j] < prev) continue;

			if (DP[history[i][j]] <= k) k -= DP[history[i][j]];
			else {
				ans.push_back(history[i][j]);
				p = prv[history[i][j]];
				prev = history[i][j];
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