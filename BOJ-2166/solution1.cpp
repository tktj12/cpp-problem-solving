#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using ll = long long;

class Vec {
public:
	ll x, y;
};

double Area(const vector<Vec>& p)
{
	ll ret = 0;
	int n = p.size();
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		ret += p[i].x * p[j].y - p[j].x * p[i].y;
	}
	return ret / 2.;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<Vec> p(n);
	for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;

	cout << fixed;
	cout.precision(1);
	cout << fabs(Area(p));
	
	return 0;
}