#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 200000;

int Edge(int here, int i)
{
	switch (i) {
	case 0: return here - 1;
	case 1: return here + 1;
	case 2: return 2 * here;
	}
	return -1;
}

pair<int,int> BFS(int start, int dest)
{
	if (start == dest) return { 0,1 };

	vector<int> dist(MAXN + 1, -1);
	dist[start] = 0;
	pair<int, int> ret(987654321, 0); // 최단 경로의 길이, 최단 경로의 개수

	queue<pair<int,int> > q; // 좌표, 거리 쌍
	q.push({ start,0 });
	while (!q.empty()) {
		int here = q.front().first; 
		int d = q.front().second + 1;
		q.pop();
		
		if (d > ret.first) break;

		for (int i = 0; i < 3; i++) {
			int there = Edge(here, i);
			if (there < 0 || MAXN < there) continue;

			if (dist[there] == -1 || dist[there] == d) {
				dist[there] = d;
				q.push({ there,d });

				if (there == dest) {
					ret.first = d;
					ret.second++;
				}
			}
		}
	}

	return ret;
}


int main()
{
	int n, k;
	cin >> n >> k;
	pair<int,int> ans = BFS(n, k);
	cout << ans.first << '\n' << ans.second;

	return 0;
}