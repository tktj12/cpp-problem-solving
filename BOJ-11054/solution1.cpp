#include <iostream>
#include <vector>
#include <cstring>
#include <set>
using namespace std;

int n, seq[1000];

void UpdateLisArr(set<int>& lis_arr, vector<int>& len, vector<int>& top, int idx, int num, int prev)
{
	auto iter = lis_arr.lower_bound(num);
	if (iter == lis_arr.end()) { 
		// lis 길이 증가
		lis_arr.insert(num);
		top[idx] = num;
	}
	else if (*iter == num) {
		top[idx] = top[prev];
	}
	else if (*iter > num) {
		lis_arr.erase(iter);
		lis_arr.insert(num);
		top[idx] = top[prev];
	}

	len[idx] = lis_arr.size();
}

int GetLongestBitonicArr(int n)
{
	vector<int> right_len(n), right_top(n);
	vector<int> left_len(n), left_top(n);

	set<int> lis_arr;
	for (int i = 0; i < n; i++)
		UpdateLisArr(lis_arr, right_len, right_top, i, seq[i], i-1);

	lis_arr = set<int>();
	for (int i = n-1; i >= 0; i--)
		UpdateLisArr(lis_arr, left_len, left_top, i, seq[i], i+1);

	int ret = 0;
	for (int i = 0; i < n; i++) {
		int cand = right_len[i] + left_len[i];
		if (right_top[i] == left_top[i]) cand--;
		ret = max(ret, cand);
	}
	return ret;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++) cin >> seq[i];
	cout << GetLongestBitonicArr(n);

	return 0;
}