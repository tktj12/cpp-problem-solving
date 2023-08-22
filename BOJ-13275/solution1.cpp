#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int M[200000];
int Manacher(string& S)
{
	int ret = 1, n = S.size();
	int r = 0, p = 0;
	for (int i = 1; i < n; i++) {
		if (i >= r) {
			p = i;
			r = i + 1;
			while (r < n && r <= 2 * p && S[2 * p - r] == S[r]) r++;
			M[i] = r - p-1;
		}
		else {
			int j = 2 * p - i;
			if (M[j] < r - i - 1)
				M[i] = M[j];
			else if (M[j] > r - i - 1)
				M[i] = r - i-1;
			else {
				p = i;
				while (r < n && r <= 2 * p && S[2 * p - r] == S[r]) r++;
				M[i] = r - p-1;
			}
		}

		ret = max(ret, M[i]);
	}

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	string tp, S;
	cin >> tp;
	int n = tp.size();
	S.reserve(2*n);
	for (int i = 0; i < n; i++) {
		S.push_back('.');
		S.push_back(tp[i]);
	}
	S.push_back('.');
	cout << Manacher(S);
	return 0;
}