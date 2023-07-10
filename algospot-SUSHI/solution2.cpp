#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

class Sushi {
public:
	int prefer;
	int price;
	double value;

	bool operator>(const Sushi& operand) const {
		if (value == operand.value)
			return price < operand.price;

		return value > operand.value;
	}
};

vector<Sushi> sushis;
const int CACHE_SZ = 201;
int cache[21][CACHE_SZ];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		memset(cache, 0, sizeof(cache));

		int n, m;
		cin >> n >> m;
		m /= 100;

		sushis = vector<Sushi>(n);
		for (int i = 0; i < n; ++i) {
			cin >> sushis[i].price >> sushis[i].prefer;
			sushis[i].price /= 100;
			sushis[i].value = (double)sushis[i].prefer / sushis[i].price;
		}

		sushis.insert(sushis.begin(), Sushi());
		for (int budget = 1; budget <= m; ++budget) {
			for (int i = 1; i < sushis.size(); ++i) {
				int cand1 = cache[i - 1][budget % CACHE_SZ];
				if (budget == 3821 || sushis.size() > 3) {
					int a = 1;
				}
				int cand2 = 0;
				if (budget >= sushis[i].price)
					cand2 = cache[i][(budget - sushis[i].price) % CACHE_SZ] + sushis[i].prefer;
				cache[i][budget % CACHE_SZ] = max(cand1, cand2);
			}
		}

		cout << cache[sushis.size() - 1][m % CACHE_SZ] << '\n';
	}
	return 0;
}