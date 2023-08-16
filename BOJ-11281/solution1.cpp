#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> scc_id, discovered;
stack<int> st, topol_sort;
int scc_cnt, discover_cnt;

int GroupScc(int node, vector<vector<int> >& edge)
{
	int ret = discovered[node] = discover_cnt++;

	st.push(node);
	for (int e : edge[node]) {
		if (discovered[e] == -1)
			ret = min(ret, GroupScc(e, edge));
		else if (scc_id[e] == -1)
			ret = min(ret, discovered[e]);
	}

	if (ret == discovered[node]) {
		while (1) {
			int t = st.top(); st.pop();
			scc_id[t] = scc_cnt;
			topol_sort.push(t);
			if (t == node) break;
		}
		scc_cnt++;
	}

	return ret;
}

bool Determine(vector<vector<int> >& edge, vector<bool>& ans)
{
	int n = edge.size();
	scc_id = discovered = vector<int>(n, -1);
	scc_cnt = discover_cnt = 0;
	for (int i = 2; i < n; i++)
		if (discovered[i] == -1)
			GroupScc(i, edge);

	for (int i = 2; i < n; i += 2)
		if (scc_id[i] == scc_id[i + 1])
			return false;

	vector<bool> is_true(n);
	while (!topol_sort.empty()) {
		int t = topol_sort.top(); // 명제 A를 표현하는 t가 처음 나왔다면 t는 거짓이고 !t가 참임
		topol_sort.pop();
		if (is_true[t] == false) {
			int not_t = t % 2 ? t - 1 : t + 1;
			is_true[not_t] = true;
		}
	}

	for (int i = 1; i < ans.size(); i++)
		ans[i] = is_true[2 * i];

	return true;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	// A = edge[2*A], !A = edge[2*A+1]
	vector<vector<int> > edge(2 * n + 2);
	for (int i = 0; i < m; i++) {
		int a, b, not_a, not_b;
		cin >> a >> b;

		if (a < 0) {
			a = 2 * (-a) + 1;
			not_a = a - 1;
		}
		else {
			a = 2 * a;
			not_a = a + 1;
		}

		if (b < 0) {
			b = 2 * (-b) + 1;
			not_b = b - 1;
		}
		else {
			b = 2 * b;
			not_b = b + 1;
		}

		edge[not_a].push_back(b);
		edge[not_b].push_back(a);
	}

	vector<bool> ans(n + 1);
	if (Determine(edge, ans)) {
		cout << 1 << '\n';
		for (int i = 1; i < ans.size(); i++)
			cout << ans[i] << ' ';
	}
	else cout << 0;

	return 0;
}