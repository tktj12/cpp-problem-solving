#include <iostream>
#include <vector>
using namespace std;

int board[9][9];
vector<bool> Possible(int y, int x)
{
	vector<bool> ret(10, true);
	for (int i = 0; i < 9; i++)
		ret[board[i][x]] = ret[board[y][i]] = false;

	int _y = (y / 3)*3;
	int _x = (x / 3)*3;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			ret[board[_y + i][_x + j]] = false;

	return ret;
}

bool FillBoard(int y, int x)
{
	while (board[y][x] > 0) {
		x++;
		if (x == 9) {
			y++, x = 0;
			if (y == 9) return true;
		}
	}

	vector<bool> possible = Possible(y, x);
	for (int i = 1; i <= 9; i++) {
		if (possible[i]) {
			board[y][x] = i;
			if (FillBoard(y, x)) return true;
			board[y][x] = 0;
		}
	}

	return false;
}

int main()
{
	string s;
	for (int i = 0; i < 9; i++) {
		cin >> s;
		for (int j = 0; j < 9; j++)
			board[i][j] = s[j] - '0';
	}
	 
	FillBoard(0, 0);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			cout << board[i][j];
		cout << '\n';
	}
	
	return 0;
}