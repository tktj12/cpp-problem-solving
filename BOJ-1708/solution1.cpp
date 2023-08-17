#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;

class Vec {
public:
	long long x, y;
	explicit Vec(long long x = 0, long long y = 0) : x(x), y(y) {}
	Vec operator+(const Vec& rhs) const {
		return Vec(x + rhs.x, y + rhs.y);
	}
	Vec operator-(const Vec& rhs) const {
		return Vec(x - rhs.x, y - rhs.y);
	}
	Vec operator*(long long n) const {
		return Vec(x * n, y * n);
	}
	bool operator==(const Vec& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	partial_ordering operator<=>(const Vec& rhs) const {
		if (x == rhs.x) return y <=> rhs.y;
		else return x <=> rhs.x;
	}
	// 외적, b가 a의 반시계방향에 있으면 양수, 시계방향에 있으면 음수, 평행하면 0 반환
	long long Cross(const Vec& rhs) {
		return x * rhs.y - rhs.x * y;
	}
	double Norm() const { return hypot(x, y); }
};

// 점 p를 기준으로 점 b가 점 a의 반시계방향에 있으면 양수, 시계방향에 있으면 음수, 평행하면 0 반환
long long CCW(const Vec p, const Vec a, const Vec b)
{
	return (a - p).Cross(b - p);
}

class Comparator {
public:
	Vec p;
	Comparator(Vec p) : p(p) {}

	// a가 b보다 우선인지
	bool operator()(const Vec& a, const Vec& b) {
		long long ccw = CCW(p, a, b);
		if (ccw > 0) return true;
		else if (ccw < 0) return false;
		else return (a - p).Norm() > (b - p).Norm();
	}
};

int MakeConvexHull(vector<Vec>& points)
{
	int n = points.size();

	// 최하단, 최좌단 점을 시작으로
	Vec start(50000,50000);
	int i, s;
	for (i = 0; i < n;i++) {
		Vec& e = points[i];
		if (e.y < start.y) start = e, s = i;
		else if (e.y == start.y && e.x < start.x) start = e, s = i;
	}
	points.erase(points.begin() + s); n--;

	sort(points.begin(), points.end(), Comparator(start));
	vector<Vec> st;
	st.push_back(start);
	st.push_back(points[0]);
	for (int i = 1; i < n; i++) {
		Vec c = points[i];
		while(1) {
			Vec a = st[st.size() - 2];
			Vec b = st.back();

			long long ccw = CCW(a, b, c);
			if (ccw < 0) st.pop_back();
			else if (ccw == 0) {
				if ((b - a).Norm() < (c - a).Norm()) {
					st.pop_back();
					st.push_back(c);
					break;
				}
				else break;
			}
			else {
				st.push_back(c);
				break;
			}
		}
	}

	if (CCW(st[st.size() - 2], st.back(), start) == 0)
		st.pop_back();

	return st.size();
}

int main()
{
	int n;
	cin >> n;
	vector<Vec> points(n);
	for (int i = 0; i < n; i++)
		cin >> points[i].x >> points[i].y;

	cout << MakeConvexHull(points);

	return 0;
}