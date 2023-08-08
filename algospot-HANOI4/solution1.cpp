#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

// 현재 상태가 now인 하노이의 네 탑의 idx번 원반을 state번 기둥으로 옮김
// 0번 기둥이 가장 왼쪽, 3번 기둥이 가장 오른쪽 기둥
inline int Set(int now, int idx, int state) {
	return (now & ~(3 << (2 * idx))) | (state << (2 * idx));
}

// 상태가 now인 하노이의 네 탑의 idx번 원반이 위치한 기둥을 구함
inline int Get(int now, int idx) {
	return (now >> (2 * idx)) & 3;
}

inline bool IsPositive(int n) {
	return n > 0;
}

inline int incr(int n) {
	if (IsPositive(n)) return n + 1;
	else return n - 1;
}

// cache[state] : BFS를 하면서 state상태를 발견했을 때 정방향이면 +부호, 역방향이면 -부호로 해당 상태까지 오기 위해
// 얼마나 움직였는지를 저장
int cache[1 << (12 * 2)];
// 양방향 BFS로 하노이의 네 탑 문제 해결
int BiDirBfsHanoiMinMove(int start, int n)
{
	int end=0;
	for (int i = 0; i < n; i++) {
		end <<= 2;
		end |= 3;
	}
	if (start == end) return 0;
	memset(cache, 0, sizeof(cache));
	cache[start] = 1;
	cache[end] = -1;
	
	queue<int> q;
	q.push(start);
	q.push(end);
	while (!q.empty()) {
		int here = q.front(); q.pop();
		int dist = incr(cache[here]);

		// 현재 기둥에서 제일 위에 있는 원반이 무엇인지 계산
		int top[4] = { -1,-1,-1,-1 };
		for (int i = n - 1; i >= 0; i--)
			top[Get(here, i)] = i;

		for (int i = 0; i < 4; i++) {
			if (top[i] == -1) continue;

			for (int j = 0; j < 4; j++) {
				if (top[j] == -1 || top[j] > top[i]) {
					int there = Set(here, top[i], j);
					if (cache[there] == 0) {
						cache[there] = dist;
						q.push(there);
					}
					// 양방향으로 정답을 찾음
					else if (IsPositive(dist) != IsPositive(cache[there])) {
						return abs(dist - cache[there]) - 2;
					}
				}
			}
		}
	}
	return -1;
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
		int start = 0;
		for (int i = 0; i < 4; i++) {
			int rings;
			cin >> rings;
			for (int j = 0; j < rings; j++) {
				int idx;
				cin >> idx;
				start = Set(start, idx-1, i);
			}
		}

		cout << BiDirBfsHanoiMinMove(start, n) << '\n';
	}
	return 0;
}