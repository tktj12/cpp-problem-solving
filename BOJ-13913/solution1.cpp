#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 100000;

int Edge(int here, int i)
{
	switch (i) {
	case 0: return here - 1;
	case 1: return here + 1;
	case 2: return 2 * here;
	}
	return -1;
}

vector<int> BFS(int start, int dest)
{
	// parent[i] : 좌표 i로 최단거리로 오기 위해 방문해야 하는 바로 이전 정점
	vector<int> parent(MAXN + 1, -1);
	parent[start] = start;

	queue<int> q;
	q.push(start);
	while (!q.empty()) {
		int here = q.front(); q.pop();

		for (int i = 0; i < 3; i++) {
			int there = Edge(here, i);
			if (0 <= there && there <= MAXN && parent[there] == -1) {
				parent[there] = here;
				q.push(there);

				if (there == dest) {
					q = queue<int>(); // clear queue
					break;
				}
			}
		}
	}

	if (parent[dest] == -1) {
		cout << "error\n";
		return {};
	}

	vector<int> ret;
	ret.push_back(dest);
	int p = dest;
	while (parent[p] != p) {
		p = parent[p];
		ret.push_back(p);
	}
	return ret;
}


int main()
{
	int n, k;
	cin >> n >> k;
	vector<int> reversed_path = BFS(n, k);
	cout << reversed_path.size() - 1 << '\n';
	for (int i = reversed_path.size() - 1; i >= 0; i--)
		cout << reversed_path[i] << ' ';

	return 0;
}