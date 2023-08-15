#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class SuffixComparator {
public:
	int t;
	vector<int>& group;
	SuffixComparator(int t, vector<int>& group) : t(t), group(group) {}

	bool operator()(int a, int b) {
		if (group[a] != group[b]) return group[a] < group[b];
		else return group[a + t] < group[b + t];
	}
};

void CountingSort(vector<int>& perm, vector<int>& group, int t)
{
	int n = perm.size(), max_num = 100010;
	// i's first = perm[i], i's second = perm[i]+t 
	vector<int> result(n), it_has_sorted_idx_by_second(n), cnt(max_num, 0);
	for (int i = 0; i < n; i++) {
		int index_in_original_str = perm[i] + t;
		int group_num = group[index_in_original_str];
		cnt[group_num]++;
	}
	for (int i = 1; i < max_num; i++) cnt[i] += cnt[i - 1];
	for (int i = n - 1; i >= 0; i--) {
		int group_num = group[perm[i] + t]; // skip : index_in_original_str
		int order_of_second = --cnt[group_num];
		it_has_sorted_idx_by_second[order_of_second] = i;
	}

	cnt.assign(max_num, 0);
	for (int i = 0; i < n; i++) cnt[group[perm[i]]]++; // skip : group_num
	for (int i = 1; i < max_num; i++) cnt[i] += cnt[i - 1];
	for (int i = n - 1; i >= 0; i--) {
		int index_in_perm = it_has_sorted_idx_by_second[i];
		int index_in_original_str = perm[index_in_perm];
		int group_num = group[index_in_original_str];
		int order_of_first = --cnt[group_num];
		result[order_of_first] = perm[index_in_perm];
	}

	perm = result;
}

vector<int> perm;
void ManberMyers(string& str)
{
	int n = str.size();
	vector<int> group(2*n, 0);
	for (int i = 0; i < n; i++) group[i] = str[i];

	perm = vector<int>(n);
	for (int i = 0; i < n; i++) perm[i] = i;
	int t = 1;
	while (true) {
		SuffixComparator compare_using_2t(t, group);
		//sort(perm.begin(), perm.end(), compare_using_2t);
		CountingSort(perm, group, t);

		t *= 2;
		if (t >= n) break;

		vector<int> new_group(2*n, 0);

		new_group[perm[0]] = 1;
		for (int i = 1; i < n; i++) {
			if (compare_using_2t(perm[i - 1], perm[i])) {
				new_group[perm[i]] = new_group[perm[i - 1]] + 1;
			}
			else {
				new_group[perm[i]] = new_group[perm[i - 1]];
			}
		}
		group = new_group;
	}

	// return perm;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	string str;
	cin >> str;
	ManberMyers(str);

	for (int i : perm)
		cout << i << '\n';

	return 0;
}