#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int ES(int idx, int capacity, vector<int>& result);

int N, W;
int weights[100], values[100];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		vector<string> baggage;
		cin >> N >> W;
		for (int i = 0; i < N; ++i) {
			string thing;
			cin >> thing;
			baggage.push_back(thing);
			cin >> weights[i] >> values[i];
		}
		vector<int> result;
		cout << ES(0, W, result) << ' ';
		cout << result.size() << '\n';
		for (int i = 0; i < result.size(); ++i)
			cout << baggage[result[i]] << '\n';
	}
	return 0;
}

int ES(int idx, int capacity, vector<int>& result)
{
	if (idx == N || capacity == 0) return 0;
	vector<int> case2 = result;
	int ret = ES(idx + 1, capacity, result);

	if (weights[idx] <= capacity) {
		case2.push_back(idx);
		int cand = ES(idx + 1, capacity - weights[idx], case2);
		if (cand + values[idx] > ret) {
			ret = cand + values[idx];
			result = case2;
		}
	}

	return ret;
}