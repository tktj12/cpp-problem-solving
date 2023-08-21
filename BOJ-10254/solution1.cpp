#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;

const double PI = cos(0) * 2.;
class Vec {
public:
	double x;
	double y;

	explicit Vec(double _x=0, double _y=0) : x(_x), y(_y) {}

	Vec operator+(const Vec rhs) const {
		return Vec(x + rhs.x, y + rhs.y);
	}
	Vec operator-(const Vec rhs) const {
		return Vec(x - rhs.x, y - rhs.y);
	}
	Vec operator-() const {
		return Vec(-x, -y);
	}
	bool operator==(const Vec rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	partial_ordering operator<=>(const Vec rhs) const {
		if (x == rhs.x) return y <=> rhs.y;
		return x <=> rhs.x;
	}
	Vec operator*(double scalar) const {
		return Vec(scalar * x, scalar * y);
	}

	// 길이
	double normSquare() const {
		return x * x + y * y;
	}
	double norm() const {
		return hypot(x, y);
	}
	// 단위 벡터
	Vec normalize() const {
		return Vec(x / norm(), y / norm());
	}
	// 내적, 스칼라 반환
	double dot(const Vec rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	// 외적, 스칼라만 반환
	// 반환값이 양수라면 rhs가 반시계 방향 180도 안에 위치하고, 음수라면 rhs가 시계방향 180도 안에 위치
	double cross(const Vec rhs) const {
		return x * rhs.y - rhs.x * y;
	}
};

double CCW(const Vec& p, const Vec& a, const Vec& b) {
	return (a - p).cross(b - p);
}

class Comparator {
public:
	Vec p;
	Comparator(Vec p) : p(p) {}

	// a가 더 우선인지
	bool operator()(const Vec& a, const Vec& b) {
		double ccw = CCW(p, a, b);
		if (ccw > 0) return true;
		else if (ccw < 0) return false;
		else return (a - p).normSquare() > (b - p).normSquare();
	}
};

Vec points[200010], poly[200010];
int poly_sz;
bool GrahamScan(int n)
{
	Vec p(987654321., 987654321.);
	int s = 0;
	for (int i = 0; i < n; i++)
		if (points[i] < p) {
			p = points[i];
			s = i;
		}
	swap(points[s], points[n - 1]);
	n--;
	sort(points, points + n, Comparator(p));

	poly[0] = p;
	poly[1] = points[0];
	poly_sz = 2;
	for (int i = 1; i < n; i++) {
		Vec c = points[i];
		while (1) {
			Vec a = poly[poly_sz - 2];
			Vec b = poly[poly_sz - 1];
			double ccw = CCW(a, b, c);
			if (ccw > 0) {
				poly[poly_sz++] = c;
				break;
			}
			else if (ccw < 0) poly_sz--;
			else {
				if ((b - a).normSquare() < (c - a).normSquare())
					poly[poly_sz-1] = c;
				break;
			}
		}
	}

	if (poly_sz > 2 && CCW(poly[poly_sz - 2], poly[poly_sz - 1], p) == 0) poly_sz--;
	if (poly_sz == 2) return false;
	return true;
}

Vec to_next[200010];
pair<Vec,Vec> Diameter()
{
	int n = poly_sz;
	int left = min_element(poly, poly + n) - poly;
	int right = max_element(poly, poly + n) - poly;

	Vec calipers_a(0, -1);
	double max_dist = (poly[left] - poly[right]).norm();

	for (int i = 0; i < n; i++)
		to_next[i] = (poly[(i + 1) % n] - poly[i]);

	int a = left, b = right;
	int ret_a = a, ret_b = b;
 	while(a != right || b != left) {
		double cos_theta_a = calipers_a.dot(to_next[a])/to_next[a].norm();
		double cos_theta_b = (-calipers_a).dot(to_next[b])/to_next[b].norm();

		if (cos_theta_a > cos_theta_b) { // theta a < theta b
			calipers_a = to_next[a];
			a = (a + 1) % n;
		}
		else {
			calipers_a = -to_next[b];
			b = (b + 1) % n;
		}

		double dist = (poly[a] - poly[b]).norm();
		if (dist > max_dist) {
			max_dist = dist;
			ret_a = a;
			ret_b = b;
		}
	}

	return { poly[ret_a], poly[ret_b] };
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;

		for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;
		if (GrahamScan(n) == false) {
			cout << (int)poly[0].x << ' ' << (int)poly[0].y << ' ' << (int)poly[1].x << ' ' << (int)poly[1].y;
			cout << '\n';
			continue;
		}
		pair<Vec, Vec> ans = Diameter();
		cout << (int)ans.first.x << ' ' << (int)ans.first.y << ' ' << (int)ans.second.x << ' ' << (int)ans.second.y;
		cout << '\n';
	}

	return 0;
}