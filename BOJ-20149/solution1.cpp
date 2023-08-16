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
	// ����, b�� a�� �ݽð���⿡ ������ ���, �ð���⿡ ������ ����, �����ϸ� 0 ��ȯ
	long double Cross(const Vec& rhs) { 
		return x * rhs.y - rhs.x * y;
	}
};

// �� p�� �������� �� b�� �� a�� �ݽð���⿡ ������ ���, �ð���⿡ ������ ����, �����ϸ� 0 ��ȯ
long double CCW(const Vec p, const Vec a, const Vec b)
{
	return (a - p).Cross(b - p);
}

// (a, b)�� (c,d)�� ������ �� ������ �� �̵��� �� ������ ��ġ���� Ȯ���Ѵ�.
bool ParallelSegments(Vec a, Vec b, Vec c, Vec d, Vec& p)
{
	if (CCW(a,b,c) != 0. || b < c || d < a) return false;

	if (b == c) p = b;
	else if (d == a) p = d;
	else p = Vec(NAN, NAN); // ������ ��ġ�� ���

	return true;
}

// ���� (a,b), (c,d)�� �������� �ִ���, �ִٸ� p�� ��ȯ
bool LineIntersect(Vec a, Vec b, Vec c, Vec d, Vec& p)
{
	long double det = (b - a).Cross(d - c);
	if (det == 0) return false;

	long double x = (c - a).Cross(d - c) / det;
	p = a + (b - a) * x;
	return true;
}

// ���� (a, b)�� (c,d)�� �����ϴ���
// p�� ������ ����, ������ ��ģ�ٸ� p�� nan �� ����
bool LineIntersection(Vec a, Vec b, Vec c, Vec d, Vec& p)
{
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	
	if (LineIntersect(a, b, c, d, p))
		return a <= p && p <= b && c <= p && p <= d;

	else // �� ������ �������� �ʴ´ٸ� ������ ����
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