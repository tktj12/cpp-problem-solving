#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

const double INF = INFINITY;
const int MIN = 0, MAX = 1;
bool compare(double a, double b, int mode) {
	if (mode == MIN)
		return a < b;
	else
		return a > b;
}

// 벨만-포드 알고리즘
// mode에 따라 최단경로 혹은 최대경로를 찾아서 dist에 저장함
// 경로 상에 사이클이 있으면 false를 반환
// 0에서 시작
vector<double> upper;
bool BellmanFord(int mode, vector<vector<pair<int, double> > >& adj)
{
	int V = adj.size();

	bool updated = false;
	for (int i = 0; i < V; i++) {
		updated = false;
		for (int here = 0; here < V; here++) {
			for (pair<int, double>& e : adj[here]) {
				int there = e.first;
				double w = e.second;

				if (compare(upper[here] + w, upper[there], mode)) {
					updated = true;
					upper[there] = upper[here] + w;
				}
			}
		}

		if (!updated) break;
	}

	if (updated) return false;
	else return true;
}

// mode에 따라 0에서 1로 가는 최단 혹은 최대 경로를 res에 반환, 무한대로 발산하면 inf값 반환
// 경로가 없으면 NAN 반환
double Determine(int mode, vector<vector<pair<int,double> > >& adj)
{
	if(mode == MIN)
		upper = vector<double>(100, INF);
	else
		upper = vector<double>(100, -INF);

	upper[0] = 0;
	if (BellmanFord(mode, adj) == true) {
		if (upper[1] == INF || upper[1] == -INF) return NAN;
		else return upper[1];
	}
	if (upper[1] == INF || upper[1] == -INF) return NAN;

	double history = upper[1];
	BellmanFord(mode, adj);
	if (history != upper[1])
		return INF;
	else return upper[1];
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int vertex_size, edge_size;
		cin >> vertex_size >> edge_size;
		vector<vector<pair<int, double> > > adj(vertex_size);
		
		for (int i = 0; i < edge_size; i++) {
			int u, v;
			double w;
			cin >> u >> v >> w;
			adj[u].push_back({ v,w });
		}

		double res = Determine(MIN, adj);
		if (std::isnan(res)) {
			cout << "UNREACHABLE\n";
			continue;
		}
		else if (res == INF)
			cout << "INFINITY ";
		else
			cout << res << ' ';

		res = Determine(MAX, adj);
		if (res == INF)
			cout << "INFINITY\n";
		else
			cout << res << '\n';
		cout << '\n';
	}
	return 0;
}