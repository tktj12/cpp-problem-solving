#include <iostream>
#include <vector>
using namespace std;

int CountCaseOfFillingSpace(int y, int x, int h, int w, int cnt_white, char map[][22]);

int L_block_pos[4][2][2] = { { {0, 1},{1, 0} },   // ¡¸
							 { {0, 1},{1, 1} },   // ¤¡
							 { {1, 1},{0, 1} },   // ¤¤
							 { {1, 1},{0,-1} } }; // ¡¹
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);


	int tc;
	cin >> tc;
	for (int _tc = 0; _tc < tc; ++_tc)
	{
		char map[22][22] = { 0, };
		int height, width, cnt_white(0);
		cin >> height >> width;
		for (int i = 1; i <= height; ++i)
			for (int j = 1; j <= width; ++j) {
				cin >> map[i][j];
				if (map[i][j] == '.') ++cnt_white;
			}

		if (cnt_white % 3 > 0)
			cout << "0\n";
		else
			cout << CountCaseOfFillingSpace(1, 1, height, width, cnt_white, map) << '\n';
	}

	return 0;
}

int CountCaseOfFillingSpace(int y, int x, int h, int w, int cnt_white, char map[][22])
{
	if (cnt_white == 0) return 1;

	while (map[y][x] != '.') {
		if (++x <= w) continue;
		else if (++y < h) x = 1;
		else return 0;
	}

	int ret(0);
	for (int i = 0; i < 4; ++i) {
		int y1 = y + L_block_pos[i][0][0];
		int y2 = y + L_block_pos[i][0][1];
		int x1 = x + L_block_pos[i][1][0];
		int x2 = x + L_block_pos[i][1][1];

		if (map[y1][x1] == '.' && map[y2][x2] == '.') {
			map[y][x] = map[y1][x1] = map[y2][x2] = 1; //fill space
			ret += CountCaseOfFillingSpace(y, x + 1, h, w, cnt_white - 3, map);
			map[y][x] = map[y1][x1] = map[y2][x2] = '.'; //recover space
		}
	}

	return ret;
}