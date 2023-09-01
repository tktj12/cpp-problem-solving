#include <iostream>
using namespace std;

const int UP = 1, DOWN = 2, RIGHT = 3, LEFT = 4;

struct Shark {
	int y, x;
	int speed, dir, size;
	bool catched = false;
}shark[10001];
int H, W;
int map[100][100];

int main()
{
	int m, ans = 0;
	cin >> H >> W >> m;
	for (int i = 1; i <= m; i++) {
		cin >> shark[i].y >> shark[i].x >> shark[i].speed >> shark[i].dir >> shark[i].size;
		shark[i].y--, shark[i].x--;
		map[shark[i].y][shark[i].x] = i;
	}

	for (int x = 0; x < W; x++) {
		for (int y = 0; y < H; y++) {
			int c = map[y][x];
			if (c > 0) {
				shark[c].catched = true;
				ans += shark[c].size;
				map[y][x] = 0;
				break;
			}
		}

		//MoveShark
		for (int i = 1; i <= m; i++) {
			Shark& sh = shark[i];
			if (sh.catched) continue;
			if (map[sh.y][sh.x] == i) map[sh.y][sh.x] = 0;

			if (sh.dir == UP) {
				int n = sh.y, s = sh.speed % (2 * H - 2);
				if (s < n) {
					sh.y -= s;
				}
				else if (s < H + n - 1) {
					sh.y = s - n;
					sh.dir = DOWN;
				}
				else {
					sh.y = H - 1 - (s - (n + H - 1));
				}
			}
			else if (sh.dir == DOWN) {
				int n = H - 1 - sh.y, s = sh.speed % (2 * H - 2);
				if (s < n) {
					sh.y += s;
				}
				else if (s < H + n - 1) {
					sh.y = H - 1 - (s - n);
					sh.dir = UP;
				}
				else {
					sh.y = s - (n + H - 1);
				}
			}
			else if (sh.dir == LEFT) {
				int n = sh.x, s = sh.speed % (2 * W - 2);
				if (s < n) {
					sh.x -= s;
				}
				else if (s < W + n - 1) {
					sh.x = s - n;
					sh.dir = RIGHT;
				}
				else {
					sh.x = W - 1 - (s - (n + W - 1));
				}
			}
			else {
				int n = W - 1 - sh.x, s = sh.speed % (2 * W - 2);
				if (s < n) {
					sh.x += s;
				}
				else if (s < W + n - 1) {
					sh.x = W - 1 - (s - n);
					sh.dir = LEFT;
				}
				else {
					sh.x = s - (n + W - 1);
				}
			}

			if (map[sh.y][sh.x] > 0 && map[sh.y][sh.x] < i) {
				int early = map[sh.y][sh.x];
				if (shark[early].size >= sh.size) {
					sh.catched = true;
				}
				else {
					shark[early].catched = true;
					map[sh.y][sh.x] = i;
				}
			}
			else
				map[sh.y][sh.x] = i;
		}
	}

	cout << ans;

	return 0;
}