#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

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
		return fmod(atan2(x, y) + 2.*PI, 2.*PI);
	}
	// this를 rhs로 사영한 벡터
	Vec project(const Vec rhs) const {
		Vec unit = rhs.normalize();
		return unit * unit.dot(*this);
	}
};

vector<Vec> circle;
int radius[100];
double sq(double x) // 제곱
{
	return x * x;
}

// 중심이 p, 반지름이 1인 볼이 d 방향으로 진행할 때 중심이 o이고 반지름이 r인 장애물과 부딫히는지 반환
// 부딫힌다면 좌표를 coord에 반환
bool Collide(Vec p, Vec d, Vec o, double r, Vec& coord)
{
	Vec beta = o - p;
	if (beta.dot(d) <= 0) return false;

	// 근의 공식 적용
	double a = sq(d.x) + sq(d.y);
	double b = -2 * (d.x * beta.x + d.y * beta.y);
	double c = sq(beta.x) + sq(beta.y) - sq(r) - 2 * r - 1;

	if (sq(b) < 4 * a * c) return false;
	double k = (-b - sqrt(sq(b) - 4 * a * c)) / (2 * a);
	coord = p + d * k;
	return true;
}

// 볼의 좌표 p와 방향 d, 중심이 o인 원과 충돌점 col이 있을 때
// 부딫힌 후 핀볼의 방향을 계산해서 반환
Vec reflect(Vec p, Vec d, Vec o, Vec col)
{
	// o에서 col로 향하는 방향
	Vec oc = col - o;
	// d를 뒤집은 것
	Vec d_prime = d * -1.;
	// d_prime을 oc에 사영한 벡터
	Vec l = d_prime.project(oc);
	return d_prime + (l - d_prime) * 2.;
}

// 핀볼의 좌표와 방향이 있을 때 다음에 충돌하는지 여부를 반환
// 충돌한다면 충돌 직후로 좌표와 방향을 갱신하고 collided에 충돌한 장애물 번호 반환
bool CheckCollision(Vec& p, Vec& d, int& collided)
{
	Vec col(0, 0);
	double best = 987654321.;
	int choice = -1;
	for (int i = 0; i < circle.size(); ++i) {
		if (i == collided) continue;

		Vec coord(0, 0); // 충돌점
		if (!Collide(p, d, circle[i], radius[i], coord)) continue;
		double distance = (p - coord).norm();
		if (distance < best) {
			best = distance;
			choice = i;
			col = coord;
		}
	}
	if (choice == -1) return false;

	d = reflect(p, d, circle[choice], col);
	p = col;
	collided = choice;
	return true;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		Vec p(0,0), d(0,0);
		int n;
		cin >> p.x >> p.y >> d.x >> d.y >> n;
		circle.clear();
		for (int i = 0; i < n; ++i) {
			int x, y;
			cin >> x >> y >> radius[i];
			circle.push_back(Vec(x, y));
		}

		int o = -1;
		for (int i = 0; i < 100; ++i) {
			if (CheckCollision(p, d, o))
				cout << o << ' ';
			else {
				cout << '\n';
				break;
			}
		}
	}
	return 0;
}