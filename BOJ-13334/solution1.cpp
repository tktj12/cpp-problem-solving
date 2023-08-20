#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using ll = long long;

class Coord {
public:
	ll start, end;
	Coord(ll start = 0, ll end = 0) : start(start), end(end) {}

	bool operator<(const Coord& rhs) const {
		return start > rhs.start;
	}
};
vector<Coord> dat;

bool Cmp(const Coord& a, const Coord& b) {
	return a.end < b.end;
}

int Scan(ll l)
{
	ll l_start = -1000000000;
	ll l_end = l_start + l;

	sort(dat.begin(), dat.end(), Cmp);
	int n = dat.size();
	int ret = 0;
	priority_queue<Coord> q;
	for (int i = 0; i < n; i++) {
		if (dat[i].end - dat[i].start > l) continue;

		l_end = dat[i].end;
		l_start = l_end - l;
		while (!q.empty() && q.top().start < l_start) q.pop();
		
		q.push(dat[i]);

		ret = max<int>(ret, q.size());
	}

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	dat = vector<Coord>(n);
	for (int i = 0; i < n; i++) {
		cin >> dat[i].start >> dat[i].end;
		if (dat[i].start > dat[i].end) swap(dat[i].start, dat[i].end);
	}

	int l;
	cin >> l;
	cout << Scan(l);
	
	return 0;
}