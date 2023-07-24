#include <cmath>

const double PI = cos(0) * 2.;
class Vec {
public:
	double x;
	double y;

	explicit Vec(double _x, double _y) : x(_x), y(_y) {}

	Vec operator+(const Vec rhs) const {
		return Vec(x + rhs.x, y + rhs.y);
	}
	Vec operator-(const Vec rhs) const {
		return Vec(x - rhs.x, y - rhs.y);
	}
	bool operator==(const Vec rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator<(const Vec rhs) const {
		if (x == rhs.x) return y < rhs.y;
		return x < rhs.x;
	}
	Vec operator*(double scalar) const {
		return Vec(scalar * x, scalar * y);
	}

	// ����
	double norm() const {
		return hypot(x, y);
	}
	// ���� ����
	Vec normalize() const {
		return Vec(x / norm(), y / norm());
	}
	// ����, ��Į�� ��ȯ
	double dot(const Vec rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	// ����, ��Į�� ��ȯ
	// ��ȯ���� ������ rhs�� �ݽð� ���� 180�� �ȿ� ��ġ�ϰ�, ������� rhs�� �ð���� 180�� �ȿ� ��ġ
	double cross(const Vec rhs) const {
		return x * rhs.y - rhs.x * y;
	}
	// x�� ���� ����� �ݽð� �������� �� �� ���̳�����
	double polar() const {
		return fmod(atan2(x, y) + 2. * PI, 2. * PI);
	}
	// this�� rhs�� �翵�� ����
	Vec project(const Vec rhs) const {
		Vec unit = rhs.normalize();
		return unit * unit.dot(*this);
	}
};