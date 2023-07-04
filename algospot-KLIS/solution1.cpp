#include <iostream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;
inline void FillHistory();
int BinarySearch(int, int, int);
int Memoization(int, int);
vector<int> FindAnswer(int, int);

struct Data {
	int n;
	int order;
};

int N, skip;
int sequence[500], cache[501][500];
vector<vector<Data>> history;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		cin >> N >> skip;
		for (int i = 0; i < N; ++i)
			cin >> sequence[i];

		FillHistory();

		memset(cache, -1, sizeof(cache));
		Memoization(0, 0);

		skip--;
		vector<int> result = FindAnswer(0, 0);

		cout << result.size() << '\n';
		for (int i = 0; i < result.size(); i++)
			cout << result[i] << ' ';
		cout << '\n';
	}
	return 0;
}
inline void FillHistory()
{
	history.clear();

	for (int i = 0; i < N; ++i) {
		int pos = BinarySearch(sequence[i], 0, history.size() - 1);
		if (pos == history.size())	history.push_back({});
		history[pos].push_back({ sequence[i], i });
	}
}
int BinarySearch(int n, int left, int right)
{
	if (left > right) return left;

	int mid = left + (right - left) / 2;
	if (n < history[mid].back().n)
		return BinarySearch(n, left, mid - 1);
	else
		return BinarySearch(n, mid + 1, right);
}
int Memoization(int cur_len, int vec_idx)
{
	int& ret = cache[cur_len][vec_idx];
	if (ret != -1) return ret;
	if (cur_len == history.size())
		return ret = 1;

	int this_num, this_order;
	if (cur_len == 0) this_num = this_order = -1;
	else {
		this_num = history[cur_len - 1][vec_idx].n;
		this_order = history[cur_len - 1][vec_idx].order;
	}

	int i;
	for (i = 0; i < history[cur_len].size(); i++)
		if (this_order < history[cur_len][i].order)
			break;
	
	ret = 0;
	for (; i < history[cur_len].size(); i++)
		if (history[cur_len][i].n > this_num) {
			ret += Memoization(cur_len + 1, i);
			if (ret < 0) ret = 0x7FFFFFFF;
		}

	return ret;
}
vector<int> FindAnswer(int cur_len, int vec_idx)
{
	if (cur_len == history.size())
		return { history[cur_len - 1][vec_idx].n };

	int this_num, this_order;
	if (cur_len == 0) this_num = this_order = -1;
	else {
		this_num = history[cur_len - 1][vec_idx].n;
		this_order = history[cur_len - 1][vec_idx].order;
	}

	int i;
	for (i = 0; i < history[cur_len].size(); i++)
		if (this_order < history[cur_len][i].order)
			break;
	for (int j = history[cur_len].size() - 1; j >= i; j--) {
		if (history[cur_len][j].n > this_num) {
			if (skip >= cache[cur_len + 1][j])
				skip -= cache[cur_len + 1][j];
			else {
				vector<int> ret;
				if (cur_len > 0)
					ret.push_back(history[cur_len - 1][vec_idx].n);
				vector<int> tail = FindAnswer(cur_len + 1, j);
				ret.insert(ret.end(), tail.begin(), tail.end());
				return ret;
			}
		}
	}

	cout << "error\n";
	return {};
}