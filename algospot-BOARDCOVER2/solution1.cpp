#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
void InputAndPreprocess();
int AllSearch(int y, int x);

int H, W;
vector<vector<vector<bool>>> block;
int board[12][12];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	for (int i = 0; i < 12; ++i)
		board[0][i] = board[i][0] = 1;

	int tc;
	cin >> tc;
	while (tc--) {
		InputAndPreprocess();

		cout << AllSearch(1, 1) << '\n';
	}
	return 0;
}

void InputAndPreprocess()
{
	int block_h, block_w;
	cin >> H >> W >> block_h >> block_w;

	// 게임판 입력
	for (int i = 1; i <= H; ++i) {
		board[i][W + 1] = 1;
		for (int j = 1; j <= W; ++j) {
			char tp;
			cin >> tp;
			board[i][j] = (tp == '#');
			board[H + 1][j] = 1;
		}
	}

	// block 입력
	block = vector<vector<vector<bool>>>(4);
	for (int i = 0; i < block_h; ++i) {
		block[0].push_back({});
		block[0][i] = vector<bool>(block_w);
		for (int j = 0; j < block_w; ++j) {
			char tp;
			cin >> tp;
			block[0][i][j] = (tp == '#');
		}
	}

	// block 전처리, 필요없는 행 제거
	for (int i = 0; i < block[0].size(); ++i) {
		bool appear = false;
		for (int j = 0; j < block[0][i].size(); ++j) {
			if (block[0][i][j]) {
				appear = true;
				break;
			}
		}
		if (!appear)
			block[0].erase(block[0].begin() + i--);
	}

	// block 전처리, 필요없는 열 제거
	for (int i = 0; i < block[0][0].size(); ++i) {
		bool appear = false;
		for (int j = 0; j < block[0].size(); ++j) {
			if (block[0][j][i]) {
				appear = true;
				break;
			}
		}
		if (!appear) {
			for (int j = 0; j < block[0].size(); ++j)
				block[0][j].erase(block[0][j].begin() + i);
			--i;
		}
	}

	// block 돌리기
	block[1] = block[3] = vector<vector<bool>>(block[0][0].size());
	for (int i = 0; i < block[1].size(); ++i)
		block[1][i] = block[3][i] = vector < bool > (block[0].size());

	block[2] = vector<vector<bool>>(block[0].size());
	for (int i = 0; i < block[2].size(); ++i)
		block[2][i] = vector<bool>(block[0][0].size());

	for(int i=0;i<block[0].size();++i)
		for (int j = 0; j < block[0][0].size(); ++j) {
			block[1][j][block[1][0].size() - 1 - i] = block[0][i][j];
			block[2][block[2].size()-1-i][block[2][0].size()-1-j] = block[0][i][j];
			block[3][block[3].size() - 1 - j][i] = block[0][i][j];
		}

	// 같은 block 없애기
	for(int i=0;i<block.size()-1;++i)
		for (int j = i + 1; j < block.size(); ++j) {
			if (block[i].size() != block[j].size()) continue;

			bool same = true;
			for (int y = 0; y < block[i].size(); ++y) {
				for (int x = 0; x < block[i][0].size(); ++x) {
					if (block[i][y][x] != block[j][y][x]) {
						same = false;
						break;
					}
				}
				if (!same) break;
			}
			if (same) block.erase(block.begin() + j--);
		}
}

inline bool CanPut(int y, int x, int idx)
{
	if (y + block[idx].size() - 1 > H || x + block[idx][0].size() - 1 > W) return false;

	for (int i = 0; i < block[idx].size(); ++i)
		for (int j = 0; j < block[idx][0].size(); ++j)
			if (block[idx][i][j] & board[y + i][x + j])
				return false;

	return true;
}

inline void Put(int y, int x, int idx)
{
	for (int i = 0; i < block[idx].size(); ++i)
		for (int j = 0; j < block[idx][0].size(); ++j)
			if(block[idx][i][j])
				board[y + i][x + j] = 1;
}

inline void Remove(int y, int x, int idx)
{
	for (int i = 0; i < block[idx].size(); ++i)
		for (int j = 0; j < block[idx][0].size(); ++j)
			if(block[idx][i][j])
				board[y + i][x + j] = 0;
}

int AllSearch(int y, int x)
{
	if (y > H) return 0;
	if (x > W) return AllSearch(y + 1, 1);

	int ret = AllSearch(y, x + 1);
	for (int i = 0; i < block.size(); ++i) {
		if (!CanPut(y, x, i)) continue;
		Put(y, x, i);
		ret = max(ret, 1+AllSearch(y, x + 1));
		Remove(y, x, i);
	}
	return ret;
}