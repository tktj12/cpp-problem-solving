#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int cache[250000];
char R[250000], P[250000];
int m;
vector<int> pa;
int KmpMemoize(int idx, int match)
{
	int& ret = cache[idx];
	if (ret > 0) return ret;
	ret = 0;

	int begin = idx;
	while (begin + match < m) {
		if (R[begin + match] == P[match]) {
			match++;
		}
		else {
			if (match == 0) return ret = 987654321;
			else
				ret = min(KmpMemoize(begin + match, 0),
						KmpMemoize(begin + match - pa[match - 1], pa[match - 1]));
			break;
		}
	}
	return ++ret;
}

vector<int> GetPartialArray()
{
	int n = strlen(P);
	vector<int> ret(n,0);
	int begin = 1, match = 0;
	while (begin + match < n) {
		if (P[begin + match] == P[match]) {
			match++;
			ret[begin + match - 1] = max(ret[begin + match - 1], match);
		}
		else {
			if (match == 0) begin++;
			else {
				begin += match - ret[match - 1];
				match = ret[match - 1];
			}
		}
	}
	return ret;
}

int Solve(int idx) {
	pa = GetPartialArray();
	return KmpMemoize(0, 0);
}

int SolveNaive(int begin)
{
	int& ret = cache[begin];
	if (ret > 0) return ret;
	ret = 987654321;

	int match = 0;
	while (begin + match < m) {
		if (R[begin + match] == P[match]) {
			match++;
			ret = min(ret, SolveNaive(begin + match));
		}
		else {
			if (match == 0) return ret = 987654321;
			ret = min(ret, SolveNaive(begin + match));
			break;
		}
	}
	if (begin + match == m) return 1;
	else
		return ++ret;
}

int main(int argc, char** argv)
{
	cin.tie(nullptr), cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int T, test_case;
	cin >> T;
	//T = 12;
	for (test_case = 0; test_case < T; test_case++)
	{
		//freopen("C:\\Users\\123au\\cpp-problem-solving\\2023SCPC\\Round-1\\input.txt", "r", stdin);

		memset(cache, 0, sizeof(cache));
		//cin.getline(R, 250010);
		//cin.getline(P, 250010);
		cin >> R >> P;
		m = strlen(R);
		int ans = Solve(0);
		cout << "Case #" << test_case + 1 << '\n';
		cout << (ans < 987654320 ? ans : -1) << '\n';
	}

	return 0;
}