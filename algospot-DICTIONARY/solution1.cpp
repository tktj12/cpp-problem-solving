#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int ALPHABET = 26;
inline int ToNum(char c) {
	return c - 'a';
}
inline char ToChar(int n) {
	return n + 'a';
}

bool dag[ALPHABET][ALPHABET]; // dag[u][v] : u에서 v로 가는 간선의 유무, 간선이 있다면 u가 v보다 앞선다는 의미이다.

// 사전순으로 q에 들어가있는 string들의 idx번째 알파벳의 순서 관계를 그래프에 옮김
void Search(int idx, queue<string>& q)
{
	if (q.size() <= 1) return;

	queue<string> next;

	char c_now = q.front()[idx];
	while (!q.empty()) {
		string now = q.front(); q.pop();
		if (now[idx] != c_now) {
			dag[ToNum(c_now)][ToNum(now[idx])] = true;
			c_now = now[idx];
			Search(idx + 1, next);
			next = queue<string>();
		}
		if(now.size() != idx + 1)
			next.push(now);
	}
	Search(idx + 1, next);
}

// a : 현재 알파벳, visited : 방문여부
// searching[i] : i번째 알파벳이 현재 DFS로 방문되서 아직 DFS함수가 끝나지 않았는지
// order : 알파벳들의 순서
// cycle이 없으면 true, 있으면 false를 반환
bool DFS(int a, vector<bool>& visited, vector<bool>& searching, vector<int>& order)
{
	if (searching[a]) return false;
	else if (visited[a]) return true;
	visited[a] = searching[a] = true;

	for (int i = 0; i < ALPHABET; i++)
		if (dag[a][i])
			if (DFS(i, visited, searching, order) == false)
				return false;

	searching[a] = false;
	order.push_back(a);
	return true;
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
		memset(dag, 0, sizeof(dag));
		queue<string> q;
		for (int i = 0; i < n; i++) {
			string str;
			cin >> str;
			q.push(str);
		}

		Search(0, q);

		vector<bool> visited(ALPHABET, 0);
		vector<bool> searching(ALPHABET, 0);
		vector<int> order;
		bool invalid = false;
		for (int i = 0; i < ALPHABET; i++) {
			if (DFS(i, visited, searching, order) == false) {
				invalid = true;
				break;
			}
		}

		if (invalid) cout << "INVALID HYPOTHESIS\n";
		else {
			for (int i = order.size()-1; i >= 0; i--)
				cout << ToChar(order[i]);
			cout << '\n';
		}
	}
	return 0;
}