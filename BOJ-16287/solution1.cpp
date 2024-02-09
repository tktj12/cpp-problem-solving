#include <iostream>
using namespace std;

int weight[5000];
bool left_cache[400000];
int main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);

	int W, N;
	cin >> W >> N;
	for (int i = 0; i < N; i++) cin >> weight[i];

	for (int i = 2; i < N - 1; i++) {
		for (int j = 0; j < i - 1; j++)
			left_cache[weight[i - 1] + weight[j]] = true;

		for (int j = i + 1; j < N; j++) {
			int remainder = W - weight[i] - weight[j];
			if (remainder < 3 || 400000 <= remainder)
				continue;

			if (left_cache[remainder]) {
				cout << "YES";
				return 0;
			}
		}
	}

	cout << "NO";
	return 0;
}