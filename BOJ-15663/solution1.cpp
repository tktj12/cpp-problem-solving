#include <iostream>
#include <vector>
#include <set>
using namespace std;

int N, M;
set<vector<int> > s;
void MakeSequence(vector<int>& seq, int idx, vector<int> nums)
{
	if (idx == M) {
		s.insert(seq);
		return;
	}

	for (int i = 0; i < nums.size(); i++) {
		vector<int> next_seq = seq;
		vector<int> next_nums = nums;
		next_seq.push_back(nums[i]);
		next_nums.erase(next_nums.begin() + i);
		MakeSequence(next_seq, idx + 1, next_nums);
	}
}

int main()
{
	vector<int> nums;

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		nums.push_back(num);
	}
	vector<int> v;
	MakeSequence(v, 0, nums);

	for (auto iter = s.begin(); iter != s.end(); iter++) {
		for (int i = 0; i < iter->size(); i++) {
			cout << iter->at(i) << ' ';
		}
		cout << '\n';
	}

	return 0;
}