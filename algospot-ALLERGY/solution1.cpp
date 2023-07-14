#include <iostream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;
void search(int, int);

vector<vector<int>> table;
bool who_eat[50];
int best;
int N, M;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		cin >> N >> M;
		map<string, int> people_idx;
		for (int i = 0; i < N; ++i) {
			string person;
			cin >> person;
			people_idx[person] = i;
		}

		table.clear();
		table.resize(M);
		for (int i = 0; i < M; ++i) {
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

		memset(who_eat, 0, sizeof(who_eat));
		best = 100;
		search(0, 0);
		cout << best << '\n';
	}
	return 0;
}

void search(int idx, int choose_cnt)
{
	// ����ġ��
	if (choose_cnt >= best) return;

	// �̹� �� ���� �� �ִ��� Ȯ��
	bool all_eat = true;
	for (int i = 0; i < N; ++i) 
		if (who_eat[i] == false) { 
			all_eat = false;
			break; 
		}
	if (all_eat) {
		best = choose_cnt;
		return;
	}
	else if (idx == M) return;

	// ���� ���
	// �� ���� �ʿ䰡 �ִ��� Ȯ��
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

	// ���� �ʴ� ���
	search(idx + 1, choose_cnt);
}