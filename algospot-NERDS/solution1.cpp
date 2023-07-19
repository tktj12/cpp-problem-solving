#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

const double PI = acos(0) * 2.;
class Vec {
public:
	double x;
	double y;

	explicit Vec(double _x, double _y) : x(_x), y(_y) {}

	Vec operator+(const Vec& rhs) const {
		return Vec(x + rhs.x, y + rhs.y);
	}
	Vec operator-(const Vec& rhs) const {
		return Vec(x - rhs.x, y - rhs.y);
	}
	bool operator==(const Vec& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator<(const Vec& rhs) const {
		if (x == rhs.x) return y < rhs.y;
		return x < rhs.x;
	}
	Vec operator*(double scalar) const {
		return Vec(scalar * x, scalar * y);
	}

	// 길이
	double norm() const {
		return hypot(x, y);
	}
	// 단위 벡터
	Vec normalize() const {
		return Vec(x / norm(), y / norm());
	}
	// 내적, 스칼라 반환
	double dot(const Vec& rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	// 외적, 스칼라만 반환
	// 반환값이 양수라면 rhs가 반시계 방향 180도 안에 위치하고, 음수라면 rhs가 시계방향 180도 안에 위치
	double cross(const Vec& rhs) const {
		return x * rhs.y - rhs.x * y;
	}
	// x축 양의 방향과 반시계 방향으로 몇 도 차이나는지
	double polar() const {
		return fmod(atan2(y, x) + 2. * PI, 2. * PI);
	}
	// this를 rhs로 사영한 벡터
	Vec project(const Vec& rhs) const {
		Vec unit = rhs.normalize();
		return unit * unit.dot(*this);
	}
};

// 벡터 b가 벡터 a를 기준으로 반시계방향에 있으면 양수, 시계방향에 있으면 음수 반환
double ccw(Vec a, Vec b) {
	return a.cross(b);
}

//벡터 a-p를 기준으로 점 b가 반시계방향에 있으면 양수, 시계방향에 있으면 음수 반환
double ccw(Vec p, Vec a, Vec b) {
	return ccw(a - p, b - p);
}

// 벡터 a를 기준으로 벡터 b의 각도
double GetBetweenAngle(Vec a, Vec b)
{
	return acos(a.dot(b) / a.norm() / b.norm());
}

vector<Vec> BuildConvex(vector<Vec>& p)
{
	int start = -1;
	double lowest = 987654321.;
	for (int i = 0; i < p.size(); ++i) {
		if (p[i].y < lowest) {
			lowest = p[i].y;
			start = i;
		}
	}

	vector<Vec> convex;
	convex.push_back(p[start]);
	vector<bool> taken(p.size(), false);

	lowest = 987654321.;
	int choice = -1;
	for (int i = 0; i < p.size(); ++i) {
		if (i == start) continue;
		double angle = (p[i] - p[start]).polar();
		if (angle < lowest) {
			lowest = angle;
			choice = i;
		}
	}
	convex.push_back(p[choice]);
	taken[choice] = true;

	while (1) {
		Vec a = convex[convex.size() - 2];
		Vec b = convex[convex.size() - 1];
		int choice = -1;
		lowest = 987654321.;
		for (int i = 0; i < p.size(); ++i) {
			if (taken[i] || a == p[i] || b == p[i]) continue;

			double angle = GetBetweenAngle(b - a, p[i] - b);
			if (angle < lowest) {
				lowest = angle;
				choice = i;
			}
		}
		if (choice == start)
			break;

		convex.push_back(p[choice]);
		taken[choice] = true;
	}

	return convex;
}

double GetIntersection(double n, Vec a, Vec b)
{
	return a.x + (b.x - a.x) * (a.y - n) / (a.y - b.y);
}

const double EPSILON = 1e-7;
bool IsInside(const Vec p, const vector<Vec>& poly)
{
	int crosses = 0;
	int loop = poly.size();
	for (int i = 0; i < loop; ++i) {
		int j = (i + 1)%poly.size();
		if (poly[i] == p) return true;
		if ((poly[i].y > p.y) != (poly[j].y > p.y)) {
			double at_x = GetIntersection(p.y, poly[i], poly[j]);
			if (fabs(p.x - at_x) < EPSILON) return true;
			if (at_x > p.x) crosses++;
		}
	}

	return crosses % 2 == 1;
}

vector<Vec> giftWrap(const vector<Vec>& points)
{
	int n = points.size();
	vector<Vec> hull;
	//Vec pivot = *min_element(points.begin(), points.end());
	Vec pivot(99999,99999);
	for (int i = 0; i < n; ++i) {
		if (points[i] < pivot)
			pivot = points[i];
	}

	hull.push_back(pivot);
	while (1) {
		Vec ph = hull.back(), next = points[0];
		for (int i = 1; i < n; ++i) {
			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() - (points[i] - ph).norm();
			if (cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}
		if (next == pivot) break;
		hull.push_back(next);
	}
	return hull;
}

bool segmentIntersects(Vec a, Vec b, Vec c, Vec d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c,d,a) * ccw(c, d,b);
	if (ab == 0 && cd == 0) {
		if (b < a)swap(a, b);
		if (d<c)swap(c,d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

bool polygonIntersects(const vector<Vec>& p, const vector<Vec>& q) {
	int n = p.size(), m = q.size();
	if (IsInside(p[0], q) || IsInside(q[0], p)) return true;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (segmentIntersects(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]))
				return true;
	return false;
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
		vector<Vec> nerds, not_nerds;
		while (n--) {
			int is_nerd, x, y;
			cin >> is_nerd >> x >> y;

			if (is_nerd) nerds.push_back(Vec(x, y));
			else not_nerds.push_back(Vec(x, y));
		}
		vector<Vec> nerd_convex = BuildConvex(nerds);
		vector<Vec> not_nerd_convex = BuildConvex(not_nerds);
		//vector<Vec> nerd_convex = giftWrap(nerds);
		//vector<Vec> not_nerd_convex = giftWrap(not_nerds);

		//nerd_convex.push_back(nerd_convex[0]);
		bool separable = true;
		//bool separable = !polygonIntersects(nerd_convex, not_nerd_convex);
		for (auto not_nerd : not_nerd_convex) {
			if (IsInside(not_nerd, nerd_convex)) {
				separable = false;
				break;
			}
		}

		cout << (separable ? "THEORY HOLDS" : "THEORY IS INVALID") << '\n';
	}

	return 0;
}