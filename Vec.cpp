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

	// 길이
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
	// x축 양의 방향과 반시계 방향으로 몇 도 차이나는지
	double polar() const {
		return fmod(atan2(x, y) + 2. * PI, 2. * PI);
	}
	// this를 rhs로 사영한 벡터
	Vec project(const Vec rhs) const {
		Vec unit = rhs.normalize();
		return unit * unit.dot(*this);
	}
};