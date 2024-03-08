#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;

int NotOp(int n) {
	if (n % 2 == 0) return n + 1;
	else return n - 1;
}

int attend,judge,N;
vector<vector<int>> adj;
int lable[2010],discovered[2010];
int scc_cnt,discover_ord;
stack<int> st;

int SccDFS(int here) {
	int ret = discovered[here] = discover_ord++;
	st.push(here); // here의 자손들은 모두 스택에 here 위에 쌓인다.
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		if (discovered[there] == -1)
			ret = min(ret,SccDFS(there));

		// there이 이미 SCC로 묶였다는 건 there에서 here로 오는 간선이 없다는 의미이다.
		// 따라서 there이 SCC로 묶이지 않았을 때만 고려해야 한다.
		else if (lable[there] == -1)
			ret = min(ret,discovered[there]);
	}

	if (ret == discovered[here]) {
		// 다시 here로 오는 간선을 발견했다.
		// 즉, 현재 스택의 top 원소부터 here까지 같은 사이클에 존재한다.

		while (true) {
			int t = st.top(); st.pop();
			lable[t] = scc_cnt;
			if (t == here) break;
		}
		scc_cnt++;
	}

	return ret;
}

void Tarjan() {
	memset(lable,-1,sizeof(lable));
	memset(discovered,-1,sizeof(discovered));
	scc_cnt = discover_ord = 0;
	st = stack<int>();
	for (int i = 2; i < N; i++)
		if (discovered[i] == -1)
			SccDFS(i);
}

bool Solve() {
	Tarjan(); // lable 배열을 채운다.
	for (int i = 2; i < N; i += 2)
		if (lable[i] != -1 && lable[i] == lable[i + 1])
			return false;

	// (1번) 정점의 위상이 (not 1번) 정점보다 높다면
	// (1번)이 거짓일 때 2-SAT이 풀린다.
	if (lable[2] > lable[3])
		return false;
	else
		return true;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	while (cin >> attend) {
		cin >> judge;
		N = 2 * attend + 2;
		adj = vector<vector<int>>(N);

		int p1,p2;
		for (int i = 0; i < judge; i++) {
			cin >> p1 >> p2;
			p1 = p1 > 0 ? 2 * p1 : -2 * p1 + 1;
			p2 = p2 > 0 ? 2 * p2 : -2 * p2 + 1;
			adj[NotOp(p1)].push_back(p2);
			adj[NotOp(p2)].push_back(p1);
		}

		cout << (Solve() ? "yes\n" : "no\n");
	}

	return 0;
}