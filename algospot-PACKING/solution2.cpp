#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int Memoization(int, int);
void FindBest(int, int, vector<int>&);

int N, W;
int weight[100], value[100];
int cache[101][1001];
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
			cin >> weight[i] >> value[i];
		}
		memset(cache, -1, sizeof(cache));
		cout << Memoization(0, W) << ' ';
		vector<int> result;
		FindBest(0, W, result);
		cout << result.size() << '\n';
		for (int i = 0; i < result.size(); ++i)
			cout << baggage[result[i]] << '\n';
	}
	return 0;
}

int Memoization(int idx, int capacity)
{
	int& ret = cache[idx][capacity];
	if (idx == N || capacity == 0) return ret = 0;
	if (ret != -1) return ret;

	ret = Memoization(idx + 1, capacity);
	if (capacity >= weight[idx]) {
		int cand = Memoization(idx + 1, capacity - weight[idx]);
		if (cand + value[idx] > ret)
			ret = cand + value[idx];
	}

	return ret;
}

void FindBest(int idx, int capacity, vector<int>& result)
{
	if (idx == N || capacity == 0) return;

	if (capacity >= weight[idx] && 
		cache[idx + 1][capacity] < cache[idx + 1][capacity - weight[idx]] + value[idx])
	{
		result.push_back(idx);
		FindBest(idx + 1, capacity - weight[idx], result);
	}
	else
		FindBest(idx + 1, capacity, result);
}