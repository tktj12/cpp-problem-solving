#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <cfloat>
#include <cmath>
using namespace std;
double DP(int, int);
void FindAnswer(int, int, vector<int>&);

map<string, int> find_word;
int M, Q, N;
char word[501][11], sentence[100][11];
double after[501][501], alt[501][501];
double cache[501][100];
int choice[501][100];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> M >> Q;
	for (int i = 1; i <= M; ++i) {
		cin >> word[i];
		find_word[word[i]] = i;
	}
	for (int i = 0; i <= M; ++i)
		for (int j = 1; j <= M; ++j) {
			cin >> after[i][j];
			after[i][j] = log(after[i][j]);
		}
	for (int i = 1; i <= M; ++i)
		for (int j = 1; j <= M; ++j) {
			cin >> alt[i][j];
			alt[i][j] = log(alt[i][j]);
		}

	while (Q--) {
		cin >> N;
		for (int i = 0; i < N; ++i) cin >> sentence[i];

		memset(cache, -1, sizeof(cache));
		DP(0, 0);
		vector<int> result;
		FindAnswer(0,0, result);
		for (int i = 0; i < result.size(); ++i)
			cout << word[result[i]] << ' ';
		cout << '\n';
	}

	return 0;
}

double DP(int before, int idx)
{
	if (idx == N) return 1.;
	double& ret = cache[before][idx];
	if (!std::isnan(ret)) return ret;
	
	ret = -INFINITY;
	int& choose = choice[before][idx];
	int cur_word = find_word[sentence[idx]];
	for (int i = 1; i <= M; ++i) {
		double pa = after[before][i];
		double pb = alt[i][cur_word];
		
		if (pa + pb == -INFINITY)
			continue;
		/*else if (pa == 0. || pb == 0.) {
			choose = i;
			return ret = DP(i, idx + 1);
		}*/
		else {
			double cand = pa + pb + DP(i, idx + 1);
			if (cand > ret) {
				ret = cand;
				choose = i;
			}
		}
	}

	return ret;
}

void FindAnswer(int before, int idx, vector<int>& result)
{
	if (idx == N) return;
	int choose = choice[before][idx];
	result.push_back(choose);
	FindAnswer(choose, idx + 1, result);
}