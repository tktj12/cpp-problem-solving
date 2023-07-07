#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
int AllSearch(int budget, int idx);

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
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
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

		cout << AllSearch(m, 0) << '\n';
	}
	return 0;
}

int AllSearch(int budget, int idx)
{
	if (idx == sushis.size()) return 0;
	Sushi& now = sushis[idx];

	int ret = 0, sum = 0;
	ret = AllSearch(budget, idx+1);
	while (now.price <= budget) {
		budget -= now.price;
		sum += now.prefer;
		ret = max(ret, AllSearch(budget, idx + 1) + sum);
	}
	return ret;
}