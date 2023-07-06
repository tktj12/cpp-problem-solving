#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int solve(int);
inline void preCalc();
inline int cell(int y, int x) { return 1 << (5 *(4-y) + 4-x); }

char cache[1 << 25];
vector<int> moves;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	
	memset(cache, -1, sizeof(cache));
	preCalc();

	int tc;
	cin >> tc;
	while (tc--) {
		int state = 0;
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 5; ++j) {
				char b;
				cin >> b;
				if (b == '#') state |= cell(i, j);
			}
		cout << (solve(state) ? "WINNING" : "LOSING") << '\n';
	}
	return 0;
}

void preCalc()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j) {
			vector<int> cells;
			for (int dy = 0; dy < 2; ++dy)
				for (int dx = 0; dx < 2; ++dx)
					cells.push_back(cell(i + dy, j + dx));
			int square = cells[0] + cells[1] + cells[2] + cells[3];
			for(int i=0;i<4;++i)
				moves.push_back(square - cells[i]);
		}

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 4; ++j) {
			moves.push_back(cell(i, j) + cell(i, j + 1));
			moves.push_back(cell(j, i) + cell(j + 1, i));
		}
}

int solve(int state)
{
	char& ret = cache[state];
	if (ret != -1) return ret;

	// 가능한 경우 탐색
	ret = 0;
	for (int i = 0; i < moves.size(); ++i) {
		if (state & moves[i]) continue;
		if (solve(state | moves[i]) == 0) {
			ret = 1;
			break;
		}
	}

	return ret;
}