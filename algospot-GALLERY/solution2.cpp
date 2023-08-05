#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int INSTALLED = 1, MARKED = 2, VISIT = 3;
vector<int> vertex_state;
// �ڽ� ������ ���� Ž�� �� �ڽ��� ���¸� ����
void DFS(int node, vector<vector<int> >& edge, int& install)
{
	vertex_state[node] = VISIT;
	for (int child : edge[node])
		if (vertex_state[child] != VISIT)
			DFS(child, edge, install);

	vertex_state[node] = !INSTALLED;

	for (int child : edge[node]) {
		if (vertex_state[child] == INSTALLED && vertex_state[node] == !INSTALLED) {
			vertex_state[node] = MARKED;
		}
		else if (vertex_state[child] == !INSTALLED) {
			vertex_state[child] = MARKED;
			if (vertex_state[node] != INSTALLED) {
				vertex_state[node] = INSTALLED;
				install++;
			}
		}
	}
}

//�ּҷ� ��ġ�ؾ��ϴ� ���� ī�޶��� ���� ��ȯ
int CalcMinInstall(int g, vector<vector<int> >& edge)
{
	vertex_state = vector<int>(g, 0);
	int install = 0;
	for (int i = 0; i < g; i++)
		if (vertex_state[i] == !INSTALLED) {
			DFS(i, edge, install);
			if (vertex_state[i] == !INSTALLED) {
				vertex_state[i] = INSTALLED;
				install++;
			}
		}
	
	return install;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int g, h;
		cin >> g >> h;
		vector<vector<int> > edge(g);
		for (int i = 0; i < h; i++) {
			int u, v;
			cin >> u >> v;
			edge[u].push_back(v);
			edge[v].push_back(u);
		}

		cout << CalcMinInstall(g, edge) << '\n';
	}
	return 0;
}