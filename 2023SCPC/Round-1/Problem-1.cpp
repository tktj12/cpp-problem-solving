#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	//setbuf(stdout, NULL);
	cin.tie(nullptr), cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int T, test_case;

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		int n, a, b, ans(0);
		cin >> n >> a >> b;
		if (a > b) swap(a, b);

		ans = n / a;
		int remain = n % a;

		while (remain) {
			int alpha = b - remain;

			ans -= alpha / a - 1;
			alpha %= a;
			if (alpha == 0)	break;

			remain = a - alpha;
			ans--;
		}
		
		cout << "Case #" << test_case + 1 << '\n';
		cout << ans << '\n';
	}

	return 0;
}