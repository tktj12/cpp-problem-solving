#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX_A = 25,INF=987654321, NIL = MAX_A;
vector<int> a_match,b_match, a_adj[MAX_A], level;

// BFS로 레벨 그래프를 만든다
bool BuildLevelGraph(int a_size, int b_size, int remove_a) {
	queue<int> q;
	for (int a = 0; a < a_size; a++) {
		if (a_match[a] == NIL) {
			level[a] = 0;
			q.push(a);
		}
		else
			level[a] = INF;
	}
	level[remove_a] = INF-2;
	level[NIL] = INF;
	while (!q.empty()) {
		int a = q.front(); q.pop();
		for (int b : a_adj[a]) {
			if (level[b_match[b]] == INF) {
				level[b_match[b]] = level[a] + 1;
				q.push(b_match[b]);
				if (b_match[b] == NIL)
					return true;
			}
		}
	}
	return false;
}

vector<bool> a_visited;
bool DFS(int a) {
	if (a == NIL) return true;
	if (a_visited[a]) return false;
	a_visited[a] = true;

	for (int b : a_adj[a]) {
		if (level[b_match[b]] == level[a] + 1 && DFS(b_match[b])) {
			a_match[a] = b;
			b_match[b] = a;
			return true;
		}
	}
	return false;
}

int HopKarpBipartiteMatching(int a_size,int b_size, int remove_a, int remove_b) {
	a_match = vector<int>(a_size,NIL);
	b_match = vector<int>(b_size,NIL);
	level = vector<int>(NIL+1,INF);
	
	a_match[remove_a] = remove_b;
	b_match[remove_b] = remove_a;

	int matching = 0;
	while (BuildLevelGraph(a_size,b_size, remove_a)) {
		a_visited = vector<bool>(a_size,false);
		for (int a = 0; a < a_size; a++)
			if (a_match[a] == NIL && DFS(a))
				matching++;
	}
	return matching;
}


int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	vector<bool> is_prime(2000,true);
	int sqrtn = (int)sqrt(2000);
	for (int i = 2; i <= sqrtn; i++) {
		if (is_prime[i] == false) continue;
		for (int j = i*i; j < 2000; j += i)
			is_prime[j] = false;
	}

	vector<int> nums[2];
	int n; cin >> n;
	int first = -1;
	for(int i=0;i<n;i++) {
		int num; cin >> num;
		if (first == -1) first = num;
		nums[num % 2].push_back(num);
	}
	if (nums[0].size() != nums[1].size()) {
		cout << -1;
		return 0;
	}

	int a = first % 2,b = (a + 1) % 2;
	for (int i = 0; i < nums[a].size();i++)
		for (int j = 0; j < nums[b].size();j++)
			if (is_prime[nums[a][i] + nums[b][j]])
				a_adj[i].push_back(j);

	vector<int> ans;
	int sz = n / 2;
	for (int i = 0; i < a_adj[0].size(); i++) {
		if (HopKarpBipartiteMatching(sz,sz,0,a_adj[0][i]) == sz - 1)
			ans.push_back(nums[b][a_adj[0][i]]);
	}
	sort(ans.begin(),ans.end());
	if (ans.empty())
		cout << -1;
	else
		for (int e : ans)
			cout << e << ' ';
	
	return 0;
}