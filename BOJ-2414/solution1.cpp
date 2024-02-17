#include <iostream>
#include <vector>
using namespace std;

int N,M;
char map[52][52];
// A는 가로줄 그룹, B는 세로줄
int group_num_A[52][52],group_num_B[52][52];
int A_cnt,B_cnt;
int A_match[2500],B_match[2500];
vector<vector<int>> edge(1);
vector<bool> visited;

bool DFS(int a)
{
	if (visited[a]) return false;
	visited[a] = true;

	for (int& b : edge[a]) {
		if (B_match[b] == 0 || DFS(B_match[b])) {
			A_match[a] = b;
			B_match[b] = a;
			return true;
		}
	}
	return false;
}

int Bipartite_Matching()
{
	int size = 0, a=1;
	for(int i=1;i<=N;i++)
		for (int j = 1; j <= M; j++) {
			if (map[i][j] != '*' || group_num_A[i][j] != a) continue;
			visited = vector<bool>(A_cnt+1);

			if (DFS(a++))
				++size;
		}
	return size;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> map[i][j];

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) {
			if (map[i][j] != '*') continue;

			if (group_num_A[i][j] == 0) {
				++A_cnt;
				int k = j;
				while (map[i][k] == '*')
					group_num_A[i][k++] = A_cnt;
				edge.push_back({});
			}
			if (group_num_B[i][j] == 0) {
				++B_cnt;
				int k = i;
				while (map[k][j] == '*')
					group_num_B[k++][j] = B_cnt;
			}

			edge[group_num_A[i][j]].push_back(group_num_B[i][j]);
		}
	cout << Bipartite_Matching();

	return 0;
}