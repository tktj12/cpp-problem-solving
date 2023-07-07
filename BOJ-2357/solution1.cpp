#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
	int left;
	int right;
	int mid;
	int v;
}max_segment_tree[(1<<18)+1], min_segment_tree[(1 << 18) + 1];

int MakeSegmentTree(Node*, int, int, int, int);
int FindAnswer(Node*, int, int, int, int);

vector<int> arr(100000);
int N,M;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N >> M;
	for (int i = 0; i < N; ++i) cin >> arr[i];

	MakeSegmentTree(max_segment_tree, 1, 0, N - 1, 0);
	MakeSegmentTree(min_segment_tree, 1, 0, N - 1, 1);

	while (M--) {
		int left, right;
		cin >> left >> right;
		cout << FindAnswer(min_segment_tree, 1, left - 1, right - 1, 1) << ' ';
		cout << FindAnswer(max_segment_tree, 1, left - 1, right - 1, 0) << '\n';
	}

	return 0;
}

inline int evaluate(int lval, int rval, int mode) {
	if (mode == 0)
		return lval > rval ? lval : rval;
	else
		return lval < rval ? lval : rval;
}

int MakeSegmentTree(Node* tree, int idx, int left, int right, int mode)
{
	Node& node = tree[idx];
	node.left = left;
	node.right = right;
	if (left == right) return node.v = arr[left];

	node.mid = left + (right - left) / 2;

	int lval = MakeSegmentTree(tree, 2*idx, left, node.mid,mode);
	int rval = MakeSegmentTree(tree, 2*idx+1, node.mid+1, right,mode);

	return node.v = evaluate(lval, rval, mode);
}

int FindAnswer(Node* tree, int idx, int left, int right, int mode)
{
	Node& node = tree[idx];

	if (left == node.left && right == node.right) return node.v;
	else if (right <= node.mid) return FindAnswer(tree, 2 * idx, left, right, mode);
	else if (node.mid < left) return FindAnswer(tree, 2 * idx + 1, left, right, mode);

	int lval = FindAnswer(tree, 2 * idx, left, node.mid, mode);
	int rval = FindAnswer(tree, 2 * idx + 1, node.mid + 1, right, mode);
	return evaluate(lval, rval, mode);
}