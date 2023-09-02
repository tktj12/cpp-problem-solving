#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long MAXK = 1'000'000'001'000'000'010;
const int MAXN = 100'000;

class Node {
public:
	long long sum = 0;
	int lo, hi, mid;
	Node* left = nullptr, * right = nullptr;
};

Node* NewNode(Node* parent, int lo, int hi) {
	Node* ret = new Node;
	ret->lo = lo;
	ret->hi = hi;
	ret->mid = (ret->lo + ret->hi) / 2;
	return ret;
}

void InsertST(int idx, long long sum, Node* here)
{
	if (here->lo == here->hi) {
		here->sum = sum;
		return;
	}

	if (here->mid >= idx) {
		if (!here->left)
			here->left = NewNode(here, here->lo, here->mid);

		InsertST(idx, sum, here->left);
	}
	else {
		if (!here->right)
			here->right = NewNode(here, here->mid + 1, here->hi);

		InsertST(idx, sum, here->right);
	}

	long long ls, rs = 0;
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

struct Dat {
	int first, lo, hi, cnt=1;
	long long second;
	Dat(int a, int b, int c, long long d) : first(a), lo(b), hi(c), second(d) {}
};

vector<Dat> history[MAXN];
Node* segtree_root[100000];
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
	// history[idx][lo].first <= n < history[idx][hi].first
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (n >= history[idx][mid].first)
			lo = mid;
		else hi = mid;
	}
	return hi;
}

long long DP(int idx, int lo, int hi)
{
	long long ret = 0;
	if (idx == 0) {
		for (int i = lo; i <= hi; i++) {
			history[idx][i].second = 1;
			ret ++;
		}
		return ret;
	}

	for (int i = lo; i <= hi; i++) {
		if (history[idx][i].second == -1) {
			long long tp = DP(idx - 1, history[idx][i].lo, history[idx][i].hi);
			if (tp > MAXK / history[idx][i].cnt) history[idx][i].second = MAXK;
			else history[idx][i].second = tp * history[idx][i].cnt;
		}

		ret = min(ret + history[idx][i].second, MAXK);
	}

	return ret;
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
			lis[idx] = arr[i];
		}

		int hi = 0;
		if (idx > 0) hi = history[idx - 1].size() - 1;

		//long long sum = 1;
		long long sum = -1;
		int lo=0;
		if (idx > 0) {
			if (same) lo = history[idx].back().hi + 1;
			else lo = UpperBound(arr[i], idx - 1);
			//sum = GetSum(lo, hi, segtree_root[idx - 1]);
		}

		history[idx].push_back({ arr[i], lo, hi, sum });
		//int sz = history[idx].size() - 1;

		// 트리 키우기
		/*if (segtree_root[idx] == nullptr || segtree_root[idx]->hi < sz) {
			Node* new_head = new Node;
			new_head->lo = 0;
			if (sz == 0) new_head->hi = 0;
			else new_head->hi = sz * 2 - 1;
			new_head->mid = (new_head->lo + new_head->hi) / 2;
			new_head->left = segtree_root[idx];
			segtree_root[idx] = new_head;
		}
		InsertST(sz, sum, segtree_root[idx]);*/
	}

	for (int i = 0; i < lis_cnt; i++)
		for (int j = history[i].size() - 2; j >= 0; j--)
			if (history[i][j].first == history[i][j + 1].first)
				history[i][j].cnt += history[i][j + 1].cnt;

	
	int back = lis_cnt - 1;
	for (int i = 0; i < history[back].size(); i++) {
		if (back == 0) {
			history[back][i].second = 1;
			continue;
		}

		long long tp = DP(lis_cnt - 2, history[back][i].lo, history[back][i].hi);
		if (tp > MAXK / history[back][i].cnt) history[back][i].second = MAXK;
		else history[lis_cnt-1][i].second = tp * history[back][i].cnt;
	}

	vector<int> ans;
	ans.reserve(n);

	k--;
	int hi = history[back].size() - 1, lo=0;
	int prev = 0, mul=1;
	for (int i = back; i >= 0; i--) {
		bool able = false;
		for (int j = lo; j <= hi; j++) {
			Dat& now = history[i][j];

			long long tp = MAXK;
			if (now.second <= MAXK / mul) tp = now.second * mul;

			if (tp <= k) k -= tp;
			else {
				ans.push_back(now.first);
				hi = now.hi;
				lo = now.lo;
				prev = now.first;
				able = true;

				if (mul <= MAXK / now.cnt) mul *= now.cnt;
				else mul = MAXK;
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