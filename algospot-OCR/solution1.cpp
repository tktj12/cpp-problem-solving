#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
using namespace std;
double ES(int before, int idx, vector<int>& head);

map<string, int> find_word;
int M, Q, N;
char word[501][11], sentence[100][11];
double after[501][501], alt[501][501];
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
		for (int j = 1; j <= M; ++j)
			cin >> after[i][j];
	for (int i = 1; i <= M; ++i)
		for (int j = 1; j <= M; ++j)
			cin >> alt[i][j];

	while (Q--) {
		cin >> N;
		for (int i = 0; i < N; ++i) cin >> sentence[i];
		vector<int> result;
		ES(0, 0, result);
 		for (int i = 0; i < N; ++i)
			cout << word[result[i]] << ' ';
		cout << '\n';
	}

	return 0;
}

double ES(int before, int idx, vector<int>& head)
{
	if (idx == N) return 1.;

	double ret = 0.;
	int cur_word = find_word[sentence[idx]];
	vector<int>  tail;
	for (int i = 1; i <= M; ++i) {
		double pa = after[before][i];
		double pb = alt[i][cur_word];

		if (pa * pb == 0.) continue;
		else if (pa == 1. || pb == 1.) {
			tail.push_back(i);
			ret = pa * pb * ES(i, idx + 1, tail);
			break;
		}
		vector<int> cand = { i };
		double tp = pa * pb * ES(i, idx + 1, cand);
		if (tp > ret) {
			ret = tp;
			tail = cand;
		}
	}


	for (int i = 0; i < tail.size(); ++i)
		head.push_back(tail[i]);

	return ret;
}