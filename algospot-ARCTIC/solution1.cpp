#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
double solve(double, double);
bool check_connection(double);

double station[100][2];
double dist[100][100];
int N;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << fixed;
	cout.precision(2);

	int tc;
	cin >> tc;
	while (tc--) {
		cin >> N;
		for (int i = 0; i < N; ++i)
			cin >> station[i][0] >> station[i][1];

		// 거리 미리 구하기
		double max_dist = 0., min_dist = 2000.;
		for (int i = 0; i < N - 1; ++i)
			for (int j = i + 1; j < N; ++j) {
				dist[i][j] = dist[j][i] =
					sqrt(pow(station[i][0] - station[j][0], 2) + pow(station[i][1] - station[j][1], 2));
				if (dist[i][j] > max_dist)
					max_dist = dist[i][j];
				if (dist[i][j] < min_dist)
					min_dist = dist[i][j];
			}

		cout << solve(min_dist, max_dist + 0.00001) << '\n';
	}
	return 0;
}

// 구간 [lo, hi]에서 최소를 찾음
double solve(double lo, double hi)
{
	for (int i = 0; i < 100; ++i) {
		double mid = (lo + hi) / 2.;
		if (check_connection(mid))
			hi = mid;
		else
			lo = mid;
	}

	return hi;
}

// BFS 방식으로 모든 기지가 연결되는지 확인
bool check_connection(double d) {
	queue<int> q;
	vector<bool> visited(N,0);
	visited[0] = true;
	q.push(0);
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (int i = 0; i < N; ++i) {
			if (!visited[i] && dist[now][i] <= d) {
				visited[i] = true;
				q.push(i);
			}
		}
	}

	return find(visited.begin(), visited.end(), false) == visited.end();
}