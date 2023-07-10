#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int CACHE_SIZE = 10;

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << fixed;
	cout.precision(8);

	int tc;
	cin >> tc;
	while (tc--) {
		int N, K, M;
		vector<int> length;
		double T[50][50];

		cin >> N >> K >> M;
		length = vector<int>(N);
		for (int i = 0; i < N; ++i) cin >> length[i];
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				cin >> T[i][j];

		double cache[10][50] = { 1., }; // cache[남은 시간][노래 번호], 0분에 0번은 100% 확률로 시작

		for (int time = 1; time <= K; ++time) {
			for (int song = 0; song < N; ++song) {
				double& prob = cache[time % CACHE_SIZE][song];
				prob = 0;
				for (int prev = 0; prev < N; ++prev)
					prob += cache[(time - length[prev] + CACHE_SIZE)%CACHE_SIZE][prev] * T[prev][song];
			}
		}

		for (int i = 0; i < M; ++i) {
			int query;
			cin >> query;
			double ans = 0;
			for (int j = 0; j < length[query]; ++j)
				ans += cache[(K - j + CACHE_SIZE) % CACHE_SIZE][query];
			cout << ans << ' ';
		}
		cout << '\n';
	}
	return 0;
}