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

	// ĳ�̵� �� �ִٸ�
	if (ret != -1)
		return ret;

	// W�� ������ Ȯ��������
	else if (w == W.size())	
		return ret = (s == S.size());

	// S�� ���� �����ٸ�
	else if (s == S.size())
		return ret = 0;

	// ���� W�� S�� ���ڰ� �����ϰ� ��ġ�ȴٸ�
	else if (W[w] == '?' || W[w] == S[s])
		return ret = matchMemoized(w + 1, s + 1);

	// '*'�� ������ S�� ���� ���ڿ��� '*'�� ������� ���� �ƴ� ��츦 Ȯ������ �� true�� �޾Ҵٸ�
	else if (W[w] == '*' && (matchMemoized(w + 1, s) || matchMemoized(w, s + 1)))
		return ret = 1;

	else return ret = 0;
}