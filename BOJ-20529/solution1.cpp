#include <iostream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

vector<string> MBTI;
int dist[16][16] = { 0, };

int ClosestThree(vector<int> appear)
{
	int ret = 20;
	for (int i = 0; i < appear.size(); i++)
		for (int j = i+1; j < appear.size(); j++)
			for (int k = j+1; k < appear.size(); k++) {
				int d = dist[appear[i]][appear[j]] + dist[appear[i]][appear[k]] + dist[appear[j]][appear[k]];
				ret = min(ret, d);
			}

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	char M[2] = { 'E', 'I' };
	char B[2] = { 'N', 'S' };
	char T[2] = { 'T', 'F' };
	char I[2] = { 'P', 'J' };

	for (int m = 0; m < 2; m++)
		for (int b = 0; b < 2; b++)
			for (int t = 0; t < 2; t++)
				for (int i = 0; i < 2; i++)
					MBTI.push_back({ M[m],B[b],T[t],I[i] });

	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			for (int k = 0; k < 4; k++)
				if (MBTI[i][k] != MBTI[j][k])
					dist[i][j]++;

	int tc;
	cin >> tc;
	while (tc--) {
		map<string, int> appear;
		int n;
		cin >> n;
		while (n--) {
			string mbti;
			cin >> mbti;
			appear[mbti]++;
		}

		vector<int> appeared_idx;
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < appear[MBTI[i]] && j < 3; j++)
				appeared_idx.push_back(i);
		}

		cout << ClosestThree(appeared_idx) << '\n';
	}
	return 0;
}