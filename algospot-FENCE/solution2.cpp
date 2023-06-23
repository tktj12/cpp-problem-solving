#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
	int min;
	int idx;
	int left;
	int right;
	int mid;
}segment_tree[65537];  // 2^16+1

struct Pair
{
	int h;
	int idx;
};

void MakeSegmentTree(vector<int>&, int, int, int);
int CalculateMaxArea(int, int);
Pair GetMinHeight(int, int, int);

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	
	vector<int> fence(20000, 0); 
	while (tc--)
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i) 
			cin >> fence[i];
		MakeSegmentTree(fence, 0, n-1, 1);
		cout << CalculateMaxArea(0,n-1) << '\n';
	}
	return 0;
}

void MakeSegmentTree(vector<int>& fence, int left, int right, int node_idx)
{
	TreeNode& now = segment_tree[node_idx];
	if (left == right) {
		now.idx = now.left = now.right = left;
		now.min = fence[left];
		return;
	}

	now.left = left;
	now.right = right;
	now.mid = (left + right) / 2;

	int child = 2 * node_idx;
	MakeSegmentTree(fence, left, now.mid, child);
	MakeSegmentTree(fence, now.mid+1, right, child+1);

	if (segment_tree[child].min > segment_tree[child+1].min) ++child;

	now.min = segment_tree[child].min;
	now.idx = segment_tree[child].idx;
}

int CalculateMaxArea(int left, int right)
{
	if (left > right) return 0;

	Pair min = GetMinHeight(left, right, 1);
	int ret = min.h * (right - left + 1);

	int left_area = CalculateMaxArea(left, min.idx-1);
	int right_area = CalculateMaxArea(min.idx+1, right);

	return max(ret, max(left_area, right_area));
}

Pair GetMinHeight(int left, int right, int parent)
{
	TreeNode& now = segment_tree[parent];
	int child = 2 * parent;
	if (now.left == left && now.right == right) return { now.min, now.idx };
	else if (right <= now.mid) return GetMinHeight(left, right, child);
	else if (left > now.mid) return GetMinHeight(left, right, child + 1);

	Pair left_child = GetMinHeight(left, now.mid, child);
	Pair right_child = GetMinHeight(now.mid + 1, right, child + 1);

	return left_child.h <= right_child.h ? left_child : right_child;
}