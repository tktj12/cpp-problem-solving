#include <iostream>
#include <queue>
using namespace std;

bool visit[200001];
int GetFastestTime(int start, int goal)
{
	// ½Ã°£, ÁÂÇ¥ ½Ö
	priority_queue<pair<int, int>, vector<pair<int,int>>, greater<> > pq;
	pq.push({ 0, start });
	visit[start] = true;
	while (!pq.empty()) {
		int t = pq.top().first;
		int x = pq.top().second;
		pq.pop();
		if (x == goal) return t;

		if (0 < x && x < goal) {
			visit[2 * x] = true;
			pq.push({ t, 2 * x });
		}

		if (x < goal && visit[x + 1] == false) {
			visit[x + 1] = true;
			pq.push({ t + 1, x + 1 });
		}

		if (x > 0 && visit[x - 1] == false) {
			visit[x-1] = true;
			pq.push({ t + 1, x - 1 });
		}
	}

	return -1;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int x, goal;
	cin >> x >> goal;
	cout << GetFastestTime(x, goal);
}