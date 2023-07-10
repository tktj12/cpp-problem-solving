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
		for(int i=0;i<N;++i)
			for (int j = 0; j < N; ++j)
				cin >> T[i][j];

		vector<int> query(M);
		for (int i = 0; i < M; ++i)
			cin >> query[i];

		for (int favorite : query) {
			double cache[10][50] = { 0, }; // cache[남은 시간][노래 번호]
			for (int remaining_time = 0; remaining_time <= K; ++remaining_time) {
				for (int i = 0; i < N; ++i) {
					double& memo = cache[remaining_time % CACHE_SIZE][i];
					memo = 0.;
					if (length[i] > remaining_time) {
						if (i == favorite) memo = 1.;
						continue;
					}

					int next_song_start = (remaining_time - length[i])%CACHE_SIZE;
					for (int next = 0; next < N; ++next) 
						memo += cache[next_song_start][next] * T[i][next];
				}
			}
			cout << cache[K % CACHE_SIZE][0] << ' ';
		}
		cout << '\n';
	}
	return 0;
}