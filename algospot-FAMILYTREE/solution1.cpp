#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct Node {
	int depth=0, idx;
	vector<int> children;
};

vector<Node> node;
vector<int> inorder_result;
void InorderSearch(int node_idx, int depth)
{
	Node& now = node[node_idx];
	now.depth = depth;

	inorder_result.push_back(node_idx);
	now.idx = inorder_result.size() - 1;
	for (int child = 0; child + 1 < now.children.size();child++) {
		InorderSearch(now.children[child], depth + 1);
		inorder_result.push_back(node_idx);
		now.idx = inorder_result.size() - 1;
	}
	if (!now.children.empty()) InorderSearch(now.children.back(), depth+1);
}

vector<int> lca_segment_tree;
void init(int left, int right, int idx)
{
	if (left == right) {
		lca_segment_tree[idx] = node[inorder_result[left]].depth;
		return;
	}

	int mid = (left + right) / 2;
	init(left, mid, idx * 2);
	init(mid+1, right, idx * 2+1);

	lca_segment_tree[idx] = min(lca_segment_tree[idx * 2], lca_segment_tree[idx * 2 + 1]);
}

int query(int lo, int hi, int idx, int left, int right)
{
	if (hi < left || right < lo) return 987654321;
	if (lo <= left && right <= hi) return lca_segment_tree[idx];

	int mid = (left + right) / 2;
	return min(query(lo, hi, idx * 2, left, mid), query(lo, hi, idx * 2 + 1, mid + 1, right));
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, q;
		cin >> n >> q;
		node = vector<Node>(n);
		for (int i = 1; i < n; i++) {
			int parent;
			cin >> parent;
			node[parent].children.push_back(i);
		}
		
		inorder_result.clear();
		inorder_result.reserve(2 * n);
		InorderSearch(0,0);

		lca_segment_tree = vector<int>(4*inorder_result.size());
		init(0, inorder_result.size() - 1, 1);

		for (int i = 0; i < q; i++) {
			int a, b;
			cin >> a >> b;
			int lo = min(node[a].idx, node[b].idx);
			int hi = max(node[a].idx, node[b].idx);
			int lca_depth = query(lo, hi, 1, 0, inorder_result.size() - 1);
			cout << (node[a].depth + node[b].depth - 2 * lca_depth) << '\n';
		}
	}
	return 0;
}