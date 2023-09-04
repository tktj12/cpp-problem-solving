#include <iostream>
#include <vector>
using namespace std;

bool lights[12][12];

int dy[4] = { 1,-1,0,0 }, dx[4] = { 0,0,1,-1 };
inline void SwitchClick(int y, int x)
{
	lights[y][x] = !lights[y][x];
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		lights[ny][nx] = !lights[ny][nx];
	}
}

int CanTurnOffAll() {
	int clicked = 0;
	vector<pair<int, int>> coord;
	for(int i=2;i<=10;i++)
		for (int j = 1; j <= 10; j++)
			if (lights[i - 1][j]) {
				SwitchClick(i, j);
				coord.push_back({ i,j });
				clicked++;
			}

	for(int j=1;j<=10;j++)
		if (lights[10][j]) {
			clicked = -1;
			break;
		}

	for(int i=0;i<coord.size();i++)
		SwitchClick(coord[i].first, coord[i].second);

	return clicked;
}

int FindAnswer()
{
	int ret = 987654321;
	for (int bit = 0; bit < 1024; bit++) {
		int clicked = 0;
		for (int i = 0; i < 10; i++)
			if (bit & (1<< i)) {
				SwitchClick(1, i + 1);
				clicked++;
			}

		int clicked_plus = CanTurnOffAll();
		if (clicked_plus != -1)
			ret = min(ret, clicked + clicked_plus);

		for (int i = 0; i < 10; i++)
			if (bit & (1 << i))
				SwitchClick(1, i + 1);
	}

	return ret;
}

int main()
{
	for (int i = 1; i <= 10; i++) {
		string line; cin >> line;
		for (int j = 0; j < 10; j++)
			if (line[j] == 'O')
				lights[i][j+1] = true;
	}

	int ans = FindAnswer();
	if (ans <= 100)
		cout << ans;
	else cout << -1;

	return 0;
}