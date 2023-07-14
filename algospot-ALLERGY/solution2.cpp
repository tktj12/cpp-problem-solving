#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
void search(int, int);

bool compare(const vector<int>& a, const vector<int>& b)
{
	return a.size() > b.size();
}

vector<vector<int>> table;
bool who_eat[50];
int best;
int person_size, food_size;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		cin >> person_size >> food_size;
		map<string, int> people_idx;
		for (int i = 0; i < person_size; ++i) {
			string person;
			cin >> person;
			people_idx[person] = i;
		}

		table.clear();
		table.resize(food_size);
		for (int i = 0; i < food_size; ++i) {
			int eatable_cnt;
			cin >> eatable_cnt;
			table[i].resize(eatable_cnt);
			for (int j = 0; j < eatable_cnt; ++j) {
				string person;
				cin >> person;
				//table[people_idx[person]][i] = true;
				table[i][j] = people_idx[person];
			}
		}
		sort(table.begin(), table.end(), compare);

		memset(who_eat, 0, sizeof(who_eat));
		best = 100;
		search(0, 0);
		cout << best << '\n';
	}
	return 0;
}

void search(int idx, int choose_cnt)
{
	// 가지치기
	if (choose_cnt >= best) return;

	// 이미 다 먹을 수 있는지 확인
	bool all_eat = true;
	for (int i = 0; i < person_size; ++i)
		if (who_eat[i] == false) {
			all_eat = false;
			break;
		}
	if (all_eat) {
		best = choose_cnt;
		return;
	}
	else if (idx == food_size) return;

	// 고르는 경우
	// 꼭 먹을 필요가 있는지 확인
	bool eat = false;
	vector<int> already_eat;
	for (int i = 0; i < table[idx].size(); ++i) {
		if (who_eat[table[idx][i]] == false) {
			eat = true;
			who_eat[table[idx][i]] = true;
		}
		else
			already_eat.push_back(table[idx][i]);
	}
	if (eat) {
		search(idx + 1, choose_cnt + 1);
		for (int i = 0; i < table[idx].size(); ++i)
			who_eat[table[idx][i]] = false;
		for (int i = 0; i < already_eat.size(); ++i)
			who_eat[already_eat[i]] = true;
	}

	// 고르지 않는 경우
	search(idx + 1, choose_cnt);
}