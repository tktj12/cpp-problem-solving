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
int cache[CACHE_SZ];
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
		sort(sushis.begin(), sushis.end(), greater<>());
		for(int i=0;i<sushis.size();++i)
			for(int j=i+1;j<sushis.size();++j)
				if (sushis[j].price > sushis[i].price) {
					sushis.erase(sushis.begin() + j);
					--j;
				}

		int ans = 0;
		for (int budget = 1; budget <= m; ++budget)
			for (int i = 0; i < sushis.size(); ++i) {
				if (budget >= sushis[i].price)
					ans = max(ans, cache[(budget - sushis[i].price) % CACHE_SZ] + sushis[i].prefer);
				cache[budget % CACHE_SZ] = ans;
			}

		cout << ans << '\n';
	}
	return 0;
}