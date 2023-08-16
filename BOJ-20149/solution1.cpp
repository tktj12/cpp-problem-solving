#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Vec {
public:
	long double x, y;
	explicit Vec(long double x = 0, long double y = 0) : x(x), y(y) {}
	Vec operator+(const Vec& rhs) const {
		return Vec(x + rhs.x, y + rhs.y);
	}
	Vec operator-(const Vec& rhs) const {
		return Vec(x - rhs.x, y - rhs.y);
	}
	Vec operator*(long double n) const {
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
	long double Cross(const Vec& rhs) { 
		return x * rhs.y - rhs.x * y;
	}
};

// 점 p를 기준으로 점 b가 점 a의 반시계방향에 있으면 양수, 시계방향에 있으면 음수, 평행하면 0 반환
long double CCW(const Vec p, const Vec a, const Vec b)
{
	return (a - p).Cross(b - p);
}

// (a, b)와 (c,d)가 평행한 두 선분일 때 이들이 한 점에서 겹치는지 확인한다.
bool ParallelSegments(Vec a, Vec b, Vec c, Vec d, Vec& p)
{
	if (CCW(a,b,c) != 0. || b < c || d < a) return false;

	if (b == c) p = b;
	else if (d == a) p = d;
	else p = Vec(NAN, NAN); // 선분이 겹치는 경우

	return true;
}

// 직선 (a,b), (c,d)의 교차점이 있는지, 있다면 p에 반환
bool LineIntersect(Vec a, Vec b, Vec c, Vec d, Vec& p)
{
	long double det = (b - a).Cross(d - c);
	if (det == 0) return false;

	long double x = (c - a).Cross(d - c) / det;
	p = a + (b - a) * x;
	return true;
}

// 선분 (a, b)와 (c,d)가 교차하는지
// p에 교차점 저장, 선분이 겹친다면 p에 nan 값 저장
bool LineIntersection(Vec a, Vec b, Vec c, Vec d, Vec& p)
{
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	
	if (LineIntersect(a, b, c, d, p))
		return a <= p && p <= b && c <= p && p <= d;

	else // 두 직선이 교차하지 않는다면 평행한 것임
		return ParallelSegments(a, b, c, d, p);
}

int main()
{
	cout << fixed;
	cout.precision(10);

	Vec a, b, c, d, p;
	cin >> a.x >> a.y;
	cin >> b.x >> b.y;
	cin >> c.x >> c.y;
	cin >> d.x >> d.y;

	if (LineIntersection(a, b, c, d, p)) {
		cout << 1;
		if (!isnan(p.x))
			cout << '\n' << p.x << ' ' << p.y;
	}
	else cout << 0;

	return 0;
}