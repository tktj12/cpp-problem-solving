#include <iostream>
#include <vector>

using namespace std;

int FindMinumumSwitchClick(int cur_switch_num, vector<int>& clocks, vector<vector<int>>& switches);
bool isAllNoon(vector<int>& clocks);

const int kINF = -1;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	vector<vector<int>> switches = { 
		{0,1,2},
		{3,7,9,11},
		{4,10,14,15},
		{0,4,5,6,7},
		{6,7,8,10,12},
		{0,2,14,15},
		{3,14,15},
		{4,5,7,14,15},
		{1,2,3,4,5},
		{3,4,5,9,13}
	};

	int tc;
	cin >> tc;
	while (tc--)
	{
		vector<int> clocks;
		for (int i = 0; i < 16; ++i) {
			int time;
			cin >> time;
			clocks.push_back(time);
		}
		cout << FindMinumumSwitchClick(0, clocks, switches) << '\n';
	}
	return 0;
}

int FindMinumumSwitchClick(int cur_switch_num, vector<int>& clocks, vector<vector<int>>& switches)
{
	if (cur_switch_num > 9) return kINF;

	int min = kINF, candidate;
	for (int i = 0; i < 4; ++i) {
		vector<int>& cur_switch = switches[cur_switch_num];
		for (int j = 0; j < cur_switch.size(); ++j)
			clocks[cur_switch[j]] += 3 * i;

		if (isAllNoon(clocks)) return i;
		else candidate = FindMinumumSwitchClick(cur_switch_num + 1, clocks, switches);

		for (int j = 0; j < cur_switch.size(); ++j)
			clocks[cur_switch[j]] -= 3 * i;

		if (candidate != kINF) candidate += i;
		if (min == kINF) min = candidate;
		else if (candidate != kINF && min > candidate) min = candidate;
	}
	return min;
}

bool isAllNoon(vector<int>& clocks)
{
	for (int i = 0; i < 16; ++i)
		if (clocks[i] % 12 > 0) return false;
	return true;
}