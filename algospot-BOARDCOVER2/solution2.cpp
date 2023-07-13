#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void InputAndPreprocess();
vector<string> Rotate90(vector<string>&);
void search(int);

int H, W;
vector<vector<pair<int, int> > > rotations;
int board[10][10];
int block_size;
int remaining_space;
int best;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		best = 0;
		InputAndPreprocess();
		search(0);
		cout << best << '\n';
	}
	return 0;
}

bool set(int y, int x, vector<pair<int, int>>& block, int mode)
{
	if (mode > 0) {
		for (pair<int, int>& e : block) {
			int seek_y = y + e.first, seek_x = x + e.second;
			if (seek_y <0 || seek_y>=H || seek_x<0 || seek_x>=W)
				return false;

			if (board[seek_y][seek_x] == 1)
				return false;
		}

		for (pair<int, int> e : block)
			board[y + e.first][x + e.second] = 1;
		remaining_space -= block_size;
		return true;
	}
	else {
		for (pair<int, int> e : block)
			board[y + e.first][x + e.second] = 0;
		remaining_space += block_size;
		return false;
	}
}

void search(int placed)
{
	if (placed + remaining_space / block_size <= best)
		return;

	int y = -1, x = -1;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j)
			if (board[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		if (y != -1) break;
	}
	if (y == -1) {
		best = max(best, placed);
		return;
	}

	for (vector<pair<int,int>>& block : rotations) {
		if (set(y, x, block, 1)) {
			search(placed + 1);
			set(y, x, block, -1);
		}
	}

	board[y][x] = 1;
	remaining_space -= 1;
	search(placed);
	board[y][x] = 0;
	remaining_space += 1;
}

void InputAndPreprocess()
{
	int block_h, block_w;
	cin >> H >> W >> block_h >> block_w;
	remaining_space = 0;
	for (int i=0;i<H;++i)
		for (int j = 0; j < W; ++j) {
			char tp;
			cin >> tp;
			board[i][j] = (tp == '#');
			if (tp == '.') ++remaining_space;
		}

	vector<string> block(block_h);
	for (int i = 0; i < block_h;++i)
		cin >> block[i];

	rotations.clear();
	rotations.resize(4);
	for (int r = 0; r < 4; ++r) {
		int origin_x = -1, origin_y = -1;
		for (int i = 0; i < block.size(); ++i) {
			for (int j = 0; j < block[0].size(); ++j) {
				if (block[i][j] != '#') continue;
				if (origin_y == -1) {
					origin_y = i;
					origin_x = j;
				}
				rotations[r].push_back({ i - origin_y,j - origin_x });
			}
		}
		block = Rotate90(block);
	}

	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	block_size = rotations[0].size();
}

vector<string> Rotate90(vector<string>& block)
{
	vector<string> ret(block[0].size());
	for (int i = 0; i < ret.size(); ++i)
		ret[i] = string(block.size(), ' ');

	for(int i=0;i<block.size();++i)
		for (int j = 0; j < block[0].size(); ++j)
			ret[j][ret[0].size() - 1 - i] = block[i][j];

	return ret;
}