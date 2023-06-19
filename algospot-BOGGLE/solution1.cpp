#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool det(int y, int x, string cur_str, int cur_pos);

char map[7][7] = { 0, };
int d[3] = { 0,1,-1 };
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	for (int i = 1; i <= 5; ++i)
		cin >> map[i]+1;

	for (int test_case = 0; test_case < T; ++test_case)	{
		vector<string> case_input;
		vector<bool> isFound;
		int N;
		cin >> N;
		for (int i = 0; i < N; ++i) {
			string tp;
			cin >> tp;
			case_input.push_back(tp);
			isFound.push_back(false);
		}

		for (int i = 1; i <= 5; ++i) {
			for (int j = 1; j <= 5; ++j) {
				for (int k = 0; k < N; ++k) {
					if (isFound[k] == false)
						isFound[k] = det(i, j, case_input[k], 0);
				}
			}
		}

		for (int i = 0; i < N; ++i) {
			cout << case_input[i] << ' ';
			if (isFound[i]) cout << "YES\n";
			else cout << "NO\n";
		}
	}

	return 0;
}

bool det(int y, int x, string cur_str, int cur_pos)
{
	// base case
	if (map[y][x] <= 0 || cur_str[cur_pos] != map[y][x])
		return false;
	else if (cur_str.size()-1 == cur_pos) {
		return true;
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == 0 && j == 0) continue;

			if (det(y + d[i], x + d[j], cur_str, cur_pos + 1) == true)
				return true;
		}
	}
	return false;
}