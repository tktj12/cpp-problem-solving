#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;

class Vec {
public:
	double x,y;
	explicit Vec(double x = 0,double y = 0) : x(x),y(y) {}
	Vec operator+(const Vec& rhs) const {
		return Vec(x + rhs.x,y + rhs.y);
	}
	Vec operator-(const Vec& rhs) const {
		return Vec(x - rhs.x,y - rhs.y);
	}
	Vec operator*(double n) const {
		return Vec(x * n,y * n);
	}
	bool operator==(const Vec& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	partial_ordering operator<=>(const Vec& rhs) const {
		if (x == rhs.x) return y <=> rhs.y;
		else return x <=> rhs.x;
	}
	// 외적, b가 a의 반시계방향에 있으면 양수, 시계방향에 있으면 음수, 평행하면 0 반환
	double Cross(const Vec& rhs) {
		return x * rhs.y - rhs.x * y;
	}
	double Norm() const { return hypot(x,y); }
};

// 점 p를 기준으로 점 b가 점 a의 반시계방향에 있으면 양수, 시계방향에 있으면 음수, 평행하면 0 반환
double CCW(const Vec p,const Vec a,const Vec b)
{
	return (a - p).Cross(b - p);
}

class Comparator {
public:
	Vec p;
	Comparator(Vec p) : p(p) {}

	// a가 b보다 우선인지
	bool operator()(const Vec& a,const Vec& b) {
		double ccw = CCW(p,a,b);
		if (ccw > 0) return true;
		else if (ccw < 0) return false;
		else return (a - p).Norm() > (b - p).Norm();
	}
};

void MakeConvexHull(vector<Vec>& points)
{
	int n = points.size();

	// 최하단, 최좌단 점을 시작으로
	Vec start(50000,50000);
	int i,s;
	for (i = 0; i < n; i++) {
		Vec& e = points[i];
		if (e.y < start.y) start = e,s = i;
		else if (e.y == start.y && e.x < start.x) start = e,s = i;
	}
	points.erase(points.begin() + s); n--;

	sort(points.begin(),points.end(),Comparator(start));
	vector<Vec> st;
	st.push_back(start);
	st.push_back(points[0]);
	for (int i = 1; i < n; i++) {
		Vec c = points[i];
		while (1) {
			Vec a = st[st.size() - 2];
			Vec b = st.back();

			double ccw = CCW(a,b,c);
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

	if (CCW(st[st.size() - 2],st.back(),start) == 0)
		st.pop_back();

	points = st;
}

double PointToLine(Vec p,Vec a,Vec b)
{
	if (a.x == b.x) {
		return abs(p.x - a.x);
	}
	else if (a.y == b.y) {
		return abs(p.y - a.y);
	}
	else {
		double k = (b.y - a.y) / (b.x - a.x);
		double m = k * a.x - a.y;
		double alpha = p.x + k * p.y;

		double x = (alpha + k * m) / (k * k + 1);
		double y = (k * alpha - m) / (k * k + 1);

		double x_dif = p.x - x;
		double y_dif = p.y - y;

		return sqrt(x_dif * x_dif + y_dif * y_dif);
	}
}

int N;

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << fixed;
	cout.precision(2);

	int tc = 1;
	while (true) {
		cin >> N;
		if (N == 0) break;
		vector<Vec> points(N);
		for (int i = 0; i < N; i++)
			cin >> points[i].x >> points[i].y;
		MakeConvexHull(points);

		N = points.size();
		double ans = INFINITY;
		for (int i = 0; i < N; i++) {
			Vec a = points[i];
			Vec b = points[(i + 1) % N];
			double max_dist = 0.;
			for (int j = (i + 2) %N; j != i; j = ++j %N) {
				Vec p = points[j];
				double dist = PointToLine(p,a,b);
				max_dist = max(max_dist,dist);
			}
			ans = min(ans,max_dist);
		}

		ans = ceil(ans * 100) / 100;

		cout << "Case " << tc++ << ": " << ans << '\n';
	}
	
	return 0;
}