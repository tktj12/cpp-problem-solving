#include <iostream>
#include <vector>
#include <cmath>
#include <map>
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
		return fmod(atan2(x, y) + 2. * PI, 2. * PI);
	}
	// this�� rhs�� �翵�� ����
	Vec project(const Vec rhs) const {
		Vec unit = rhs.normalize();
		return unit * unit.dot(*this);
	}
};

// x = n �Ǵ� y = n�� ������ �� a, b�� �մ� ������ �����ϴ���
// �����Ѵٸ� �� ��ǥ�� res�� ��ȯ
// mode�� 'x'�� x = n�� ����, 'y'�� y = n�� ����
bool GetIntersection(Vec a, Vec b, double n, char mode, double& res)
{
	if (mode == 'y') {
		if ((a.y > n) != (b.y > n)) {
			res = a.x + (b.x - a.x) * (a.y - n) / (a.y - b.y);
			return true;
		}
	}
	if (mode == 'x') {
		if ((a.x > n) != (b.x > n)) {
			res = a.y + (b.y - a.y) * (a.x - n) / (a.x - b.x);
			return true;
		}
	}

	return false;
}

vector<Vec> Reconstruct(int start, double n, char mode, vector<Vec>& p)
{
	vector<Vec> choices;
	bool inside = true; // ���� �������� ���� �ȿ� �ִ���
	for (int loop = 0; loop < p.size(); loop++) {
		int i = (start + loop) % p.size();
		int j = (start + loop+1) % p.size();
		
		if (inside) choices.push_back(p[i]);

		double at;
		if (GetIntersection(p[i], p[j], n, mode, at) == false) continue;
		inside = !inside;
		
		Vec intersection(0, 0);
		if (mode == 'x') intersection.x = n, intersection.y = at;
		else if (mode == 'y') intersection.y = n, intersection.x = at;

		choices.push_back(intersection);
	}
	return choices;
}

double GetArea(vector<Vec>& p)
{
	double sum = 0;
	for (int i = 0; i < p.size(); ++i) {
		int j = (i + 1) % p.size();
		sum += p[i].cross(p[j]);
	}
	return fabs(sum)/2.;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout.precision(15);

	int tc;
	cin >> tc;
	while (tc--) {
		Vec lb(0, 0), rt(0, 0); // left bottom, right top
		int vertex_size;
		cin >> lb.x >> lb.y >> rt.x >> rt.y >> vertex_size;
		vector<Vec> island;
		island = vector<Vec>(vertex_size, Vec(0, 0));
		for (int i = 0; i < vertex_size; ++i)
			cin >> island[i].x >> island[i].y;

		bool no_area = true;
		for (int i = 0; i < island.size(); ++i)
			if (island[i].y > lb.y) {
				island = Reconstruct(i, lb.y, 'y', island);
				no_area = false;
				break;
			}
		if (no_area) { cout << "0\n"; continue; }

		no_area = true;
		for (int i = 0; i < island.size(); ++i)
			if (island[i].x < rt.x) {
				island = Reconstruct(i, rt.x, 'x', island);
				no_area = false;
				break;
			}
		if (no_area) { cout << "0\n"; continue; }

		no_area = true;
		for (int i = 0; i < island.size(); ++i)
			if (island[i].y < rt.y) {
				island = Reconstruct(i, rt.y, 'y', island);
				no_area = false;
				break;
			}
		if (no_area) { cout << "0\n"; continue; }

		no_area = true;
		for (int i = 0; i < island.size(); ++i)
			if (island[i].x > lb.x) {
				island = Reconstruct(i, lb.x, 'x', island);
				no_area = false;
				break;
			}
		if (no_area) { cout << "0\n"; continue; }


		cout << GetArea(island) << '\n';
	}
	return 0;
}