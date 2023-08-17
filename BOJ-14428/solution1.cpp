#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Node {
public:
	int index, val;
	Node(int i = 0, int v = 0) : index(i), val(v) {}
	bool operator<(const Node& rhs) const {
		return val < rhs.val || (val == rhs.val && index < rhs.index);
	}
}segtree[400000];
vector<Node> arr;

void MakeSegTree(int lo, int hi, int node)
{
	if (lo == hi) {
		segtree[node] = arr[lo];
		return;
	}

	int mid = (lo + hi) / 2;
	MakeSegTree(lo, mid, 2 * node);
	MakeSegTree(mid + 1, hi, 2 * node + 1);

	segtree[node] = min(segtree[2 * node], segtree[2 * node + 1]);
}

Node GetMinNode(int lo, int hi, int node_left, int node_right, int node)
{
	if (node_right < lo || hi < node_left) return Node(1987654321, 1987654321);
	if (node_left <= lo && hi <= node_right) return segtree[node];

	int mid = (lo + hi) / 2;
	Node ret(1987654321, 1987654321);
	ret = min(ret, GetMinNode(lo, mid, node_left, node_right, 2 * node));
	ret = min(ret, GetMinNode(mid + 1, hi, node_left, node_right, 2 * node + 1));
	return ret;
}

void UpdateSegTree(int lo, int hi, int node, int index, int val)
{
	if (lo == hi) {
		segtree[node].val = val;
		return;
	}

	int mid = (lo + hi) / 2;
	if (index <= mid)
		UpdateSegTree(lo, mid, 2 * node, index, val);
	else
		UpdateSegTree(mid + 1, hi, 2 * node + 1, index, val);

	segtree[node] = min(segtree[2 * node], segtree[2 * node + 1]);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	arr = vector<Node>(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> arr[i].val;
		arr[i].index = i;
	}
	MakeSegTree(1, n, 1);

	int q;
	cin >> q;
	for (int query = 0; query < q; query++) {
		int a, i, v;
		cin >> a >> i >> v;
		if (a == 1)
			UpdateSegTree(1, n, 1, i, v);
		else
			cout << GetMinNode(1, n, i, v, 1).index << '\n';
	}

	return 0;
}