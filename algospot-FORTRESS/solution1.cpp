#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class node {
public:
	int x, y, r;
	int depth =0;
	vector<node> children;

	node(int x, int y, int r) : x(x), y(y), r(r) {}

	bool operator<(const node& rhs) const {
		return depth > rhs.depth; // 내림차순 정렬
	}
};

inline int square(int n) {
	return n * n;
}

void MakeTree(node& parent, int x, int y, int r)
{
	// 자식 노드의 자손으로 들어가는 경우
	for (node& child : parent.children) {
		int sqr_dist = square(x - child.x) + square(y - child.y);
		if (child.r > r &&  sqr_dist < square(child.r)) {
			MakeTree(child, x, y, r);
			parent.depth = max(parent.depth, child.depth + 1);
			return;
		}
	}

	// 자식 노드인 경우
	parent.children.push_back(node(x, y, r));
	if (parent.depth == 0) parent.depth = 1;
}

int Solve(node& root)
{
	sort(root.children.begin(), root.children.end());
	int ret = 0;
	for (int i = 0; i < 2 && i < root.children.size(); i++)
		ret += root.children[i].depth+1;

	for (auto& e : root.children)
		ret = max(ret, Solve(e));

	return ret;
}

bool compare(const node& a, const node& b) {
	return a.r > b.r;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		int x, y, r;
		cin >> x >> y >> r;
		node root(x, y, r);

		vector<node> circles(n - 1, {0,0,0});

		for (int i = 0; i < circles.size(); i++) {
			cin >> x >> y >> r;
			circles[i] = node(x, y, r);
		}
		sort(circles.begin(), circles.end(), compare);

		for(node& e : circles)
			MakeTree(root, e.x, e.y, e.r);

		cout << Solve(root) << '\n';
	}
	return 0;
}