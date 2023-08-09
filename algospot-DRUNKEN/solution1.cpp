#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

inline int Max3(int a, int b, int c) {
	return max(a, max(b,c) );
}

const int INF = 987654321;
int delay[501][501]; // delay[u][v] : ���ݱ��� ã�� u���� v�� ���� ����� �ִ� �ܼ� �ð�
int w[501][501]; // w[u][v] : u���� v�� ���� ����� �ҿ�ð�, �� ã�Ҵٸ� INF

void Floyd(int vertex_size)
{
	for(int k=1;k<=vertex_size;k++)
		for (int i = 1; i <= vertex_size; i++) {
			if (w[i][k] == INF) continue;
			for (int j = 1; j <= vertex_size; j++) {
				if (i == j) continue;
				int max_delay = Max3(delay[i][k], delay[k][j], delay[k][k]);
				if (w[i][j] + delay[i][j] > w[i][k] + w[k][j] + max_delay) {
					w[i][j] = w[i][k] + w[k][j];
					delay[i][j] = max_delay;
				}
			}
		}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int vertex_size, edge_size;
	cin >> vertex_size >> edge_size;
	for (int u = 1; u <= vertex_size; u++) {
		cin >> delay[u][u];
		for (int v = 1; v <= vertex_size; v++)
			w[u][v] = INF;
		w[u][u] = 0;
	}

	for (int i = 0; i < edge_size; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		w[u][v] = w[v][u] = cost;
	}
	Floyd(vertex_size);

	int tc;
	cin >> tc;
	while (tc--) {
		int u, v;
		cin >> u >> v;
		int ans = w[u][v];
		if (u != v) ans += delay[u][v];
		cout << ans << '\n';
	}
	return 0;
}