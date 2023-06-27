#include <iostream>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

bool matchMemoized(int, int);

string W, S;
int cache[101][101];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		set<string> answer;
		cin >> W;
		int n;
		cin >> n;
		while (n--) {
			cin >> S;
			memset(cache, -1, 4*101*101);
			if (matchMemoized(0, 0)) answer.insert(S);
		}
		for (auto& e : answer) cout << e << '\n';
	}

	return 0;
}

bool matchMemoized(int w, int s)
{
	int& ret = cache[w][s];

	// 캐싱된 게 있다면
	if (ret != -1)
		return ret;

	// W의 끝까지 확인했으면
	else if (w == W.size())	
		return ret = (s == S.size());

	// S가 먼저 끝났다면
	else if (s == S.size())
		return ret = 0;

	// 현재 W와 S의 문자가 적절하게 매치된다면
	else if (W[w] == '?' || W[w] == S[s])
		return ret = matchMemoized(w + 1, s + 1);

	// '*'을 만났고 S의 현재 문자에서 '*'이 사라지는 경우와 아닌 경우를 확인했을 때 true를 받았다면
	else if (W[w] == '*' && (matchMemoized(w + 1, s) || matchMemoized(w, s + 1)))
		return ret = 1;

	else return ret = 0;
}