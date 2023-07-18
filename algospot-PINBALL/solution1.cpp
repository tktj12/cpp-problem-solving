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
		return fmod(atan2(x, y) + 2.*PI, 2.*PI);
	}
	// this�� rhs�� �翵�� ����
	Vec project(const Vec rhs) const {
		Vec unit = rhs.normalize();
		return unit * unit.dot(*this);
	}
};

vector<Vec> circle;
int radius[100];
double sq(double x) // ����
{
	return x * x;
}

// �߽��� p, �������� 1�� ���� d �������� ������ �� �߽��� o�̰� �������� r�� ��ֹ��� �΋H������ ��ȯ
// �΋H���ٸ� ��ǥ�� coord�� ��ȯ
bool Collide(Vec p, Vec d, Vec o, double r, Vec& coord)
{
	Vec beta = o - p;
	if (beta.dot(d) <= 0) return false;

	// ���� ���� ����
	double a = sq(d.x) + sq(d.y);
	double b = -2 * (d.x * beta.x + d.y * beta.y);
	double c = sq(beta.x) + sq(beta.y) - sq(r) - 2 * r - 1;

	if (sq(b) < 4 * a * c) return false;
	double k = (-b - sqrt(sq(b) - 4 * a * c)) / (2 * a);
	coord = p + d * k;
	return true;
}

// ���� ��ǥ p�� ���� d, �߽��� o�� ���� �浹�� col�� ���� ��
// �΋H�� �� �ɺ��� ������ ����ؼ� ��ȯ
Vec reflect(Vec p, Vec d, Vec o, Vec col)
{
	// o���� col�� ���ϴ� ����
	Vec oc = col - o;
	// d�� ������ ��
	Vec d_prime = d * -1.;
	// d_prime�� oc�� �翵�� ����
	Vec l = d_prime.project(oc);
	return d_prime + (l - d_prime) * 2.;
}

// �ɺ��� ��ǥ�� ������ ���� �� ������ �浹�ϴ��� ���θ� ��ȯ
// �浹�Ѵٸ� �浹 ���ķ� ��ǥ�� ������ �����ϰ� collided�� �浹�� ��ֹ� ��ȣ ��ȯ
bool CheckCollision(Vec& p, Vec& d, int& collided)
{
	Vec col(0, 0);
	double best = 987654321.;
	int choice = -1;
	for (int i = 0; i < circle.size(); ++i) {
		if (i == collided) continue;

		Vec coord(0, 0); // �浹��
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