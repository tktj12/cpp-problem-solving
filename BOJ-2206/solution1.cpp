#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Data {
	int y, x;
	bool crashed_wall;
	Data(int y, int x, bool b) : y(y), x(x), crashed_wall(b) {}
};

vector<string> map;
int visit[1000][1000][2]; // 세 번째 인덱스는 벽 부수기 소진 여부
int N, M;

int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };
int BfsFindFastestWay()
{
	queue<Data> q;
	q.push(Data(0, 0, 0));
	visit[0][0][0] = true;
	int step = 1;
	if (N == 1 && M == 1) return 1;

	while (1) {
		queue<Data> next;
		while (!q.empty()) {
			Data now = q.front(); q.pop();

			for (int i = 0; i < 4; i++) {
				int y = now.y + dy[i];
				int x = now.x + dx[i];
				if (y == N - 1 && x == M - 1) return step + 1;
				if (y < 0 || N <= y || x < 0 || M <= x || visit[y][x][0] || visit[y][x][now.crashed_wall]) continue;
				visit[y][x][now.crashed_wall] = true;

				if (map[y][x] == '0') {
					next.push(Data(y, x, now.crashed_wall));
				}
				else {
					if (now.crashed_wall) continue;
					else next.push(Data(y, x, true));
				}
			}
		}

		if (next.empty())
			return -1;
		else {
			q = next;
			step++;
		}
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N >> M;
	map = vector<string>(N);
	for (int i = 0; i < N; i++)
		cin >> map[i];
	
	cout << BfsFindFastestWay();
	
	return 0;
}