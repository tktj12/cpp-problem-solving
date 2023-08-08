#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

// ���� ���°� now�� �ϳ����� �� ž�� idx�� ������ state�� ������� �ű�
// 0�� ����� ���� ����, 3�� ����� ���� ������ ���
inline int Set(int now, int idx, int state) {
	return (now & ~(3 << (2 * idx))) | (state << (2 * idx));
}

// ���°� now�� �ϳ����� �� ž�� idx�� ������ ��ġ�� ����� ����
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

// cache[state] : BFS�� �ϸ鼭 state���¸� �߰����� �� �������̸� +��ȣ, �������̸� -��ȣ�� �ش� ���±��� ���� ����
// �󸶳� ������������ ����
int cache[1 << (12 * 2)];
// ����� BFS�� �ϳ����� �� ž ���� �ذ�
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

		// ���� ��տ��� ���� ���� �ִ� ������ �������� ���
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
					// ��������� ������ ã��
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