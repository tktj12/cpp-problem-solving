#include <iostream>
#include <vector>

using namespace std;

int SearchMates(int student, const vector<int>& remaining_students, const vector<vector<bool>>& is_friend);

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	vector<vector<bool>> is_friend;
	for (int i = 0; i < 10; ++i) {
		is_friend.push_back({});
		for (int j = 0; j < 10; ++j)
			is_friend[i].push_back(false);
	}

	int tc;
	cin >> tc;
	for (int tc_ = 0; tc_ < tc; ++tc_) {
		vector<int> remaining_students;
		int n, m, cnt(0);

		cin >> n >> m;
		for (int i = 1; i < n; ++i) 
			remaining_students.push_back(i);

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				is_friend[i][j] = false;
		}

		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			is_friend[a][b] = is_friend[b][a] = true;
		}

		cout << SearchMates(0, remaining_students, is_friend) << '\n';
	}

	return 0;
}

int SearchMates(int student, const vector<int>& remaining_students, const vector<vector<bool>>& is_friend)
{
	if (remaining_students.size() == 1) {
		if (is_friend[student][remaining_students.front()]) return 1;
		else return 0;
	}

	int ret = 0;
	for (int i = 0; i < remaining_students.size();++i) {
		int choice = remaining_students[i];
		if (!is_friend[student][choice]) continue;

		vector<int> other_students = remaining_students;
		other_students.erase(other_students.begin() + i);
		int next = other_students.front();
		other_students.erase(other_students.begin());

		ret += SearchMates(next, other_students, is_friend);
	}
	return ret;
}