#include <iostream>
#include <vector>
using namespace std;

vector<int> heights;
vector<int> seg_min, seg_max;

void init(int left, int right, int node)
{
	if (left == right) {
		seg_min[node] = seg_max[node] = heights[left];
		return;
	}
	
	int mid = (left + right) / 2;
	init(left, mid, node * 2);
	init(mid+1, right, node * 2+1);

	seg_min[node] = min(seg_min[node * 2], seg_min[node * 2 + 1]);
	seg_max[node] = max(seg_max[node * 2], seg_max[node * 2 + 1]);
}

pair<int,int> query(int lo, int hi, int node, int left, int right)
{
	if (hi < left || right < lo)
		return { -1, 987654321 };
	else if (lo <= left && right <= hi)
		return { seg_max[node], seg_min[node] };

	int mid = (left + right) / 2;
	pair<int, int> a = query(lo, hi, node * 2, left, mid);
	pair<int, int> b = query(lo, hi, node * 2+1, mid+1, right);

	return { max(a.first,b.first), min(a.second, b.second) };
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
		heights = vector<int>(n);
		for (int i = 0; i < n; i++) cin >> heights[i];

		seg_min = seg_max = vector<int>(4 * n);
		init(0, n - 1, 1);

		for (int i = 0; i < q; i++) {
			int lo, hi;
			cin >> lo >> hi;

			pair<int,int> level = query(lo, hi, 1, 0, n - 1);
			cout << level.first - level.second << '\n';
		}
	}
	return 0;
}