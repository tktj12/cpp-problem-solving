#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Vec {
public:
	int x, y;
	explicit Vec(int x = 0, int y = 0) : x(x), y(y) {}

	Vec operator-(const Vec& rhs) const {
		return Vec(x - rhs.x, y - rhs.y);
	}
	int Cross(const Vec& rhs) const {
		return x * rhs.y - rhs.x * y;
	}
	double Norm() {
		return hypot(x, y);
	}
};

int CCW(const Vec& p, const Vec& a, const Vec& b) {
	return (a - p).Cross(b - p);
}

class Comparator {
public:
	Vec p;
	Comparator(Vec& p) : p(p) {}

	// a가 우선인지
	bool operator()(const pair<Vec, int>& p1, const pair<Vec, int>& p2) {
		const Vec& a = p1.first;
		const Vec& b = p2.first;
		int ccw = CCW(p, a, b);
		if (ccw > 0) return true;
		else if (ccw < 0) return false;
		else return (a - p).Norm() < (b - p).Norm();
	}
};

int MakeSimplePolygon(vector<pair<Vec, int>>& points)
{
	int n = points.size();
	pair<Vec, int> start(Vec(20000, 20000), -1);
	for (int i = 0; i < n; i++) {
		Vec& now = points[i].first;
		if (points[i].first.y < start.first.y) start = points[i];
		else if (points[i].first.y == start.first.y &&
			points[i].first.x < start.first.x) start = points[i];
	}
	points.erase(points.begin() + start.second);
	sort(points.begin(), points.end(), Comparator(start.first));

	// reverse last line
	int begin = points.size() - 2;
	while (CCW(start.first, points.back().first, points[begin].first) == 0)
		begin--;
	reverse(points.begin() + begin + 1, points.end());

	return start.second;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		vector<pair<Vec, int> > points(n);
		for (int i = 0; i < n; i++) {
			cin >> points[i].first.x >> points[i].first.y;
			points[i].second = i;
		}
		int start = MakeSimplePolygon(points);
		n--;

		cout << start << ' ';
		for (int i = 0; i < n; i++)
			cout << points[i].second << ' ';
		cout << '\n';
	}
	return 0;
}