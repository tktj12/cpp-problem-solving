#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

inline int ToNum(char c) {
	return c - 'A';
}

vector<string> map;
int dx[4] = { 0,0,1,-1 }, dy[4] = { 1,-1,0,0 };
int DFS(int state, int y, int x)
{
	if (map[y][x] == '0' || (state & (1 << ToNum(map[y][x]) ) ) ) return 0;
	state |= 1 << ToNum(map[y][x]);

	int ret = 0;
	for (int i = 0; i < 4; i++)
		ret = max(ret, DFS(state, y + dy[i], x + dx[i]) );

	return ret + 1;
}

int main()
{
	int r, c;
	cin >> r >> c;

	// map의 끝은 '0'이다.
	map = vector<string>(r+2);
	for(int i=0;i<22;i++)
		 map[0] += '0';
	map[r + 1] = map[0];

	for (int i = 1; i <= r; i++) {
		map[i] = '0';
		string s;
		cin >> s;
		map[i] += s;
		map[i] += '0';
	}

	cout << DFS(0, 1, 1);

	return 0;
}