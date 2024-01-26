#include <iostream>
using namespace std;

string S;
int cache[1002][1002];

int Search(int begin, int end)
{
	int& ret = cache[begin][end];
	if (ret > 0) return ret;

	ret = end - begin;
	if (begin + 1 == end) return ret;

	for (int left = begin + 1; left < end; left++)
		for (int right = left + 1; right < end; right++)
			if (S[left] == S[right])
				ret = (ret + Search(left, right)) % 10007;

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> S;
	S = '.' + S;
	Search(0, S.size());

	cout << cache[0][S.size()] - 1;

	return 0;
}