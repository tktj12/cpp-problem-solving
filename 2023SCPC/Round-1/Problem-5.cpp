#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
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

double GetLineIntersect(Vec a, Vec b, Vec c, Vec d)
{
	double det = (b - a).cross(d - c);
	// 이 문제의 조건에 의해 평행하는 경우가 없음
	//if (det == 0) return false;

	return (c - a).cross(d - c) / det;
}

void GetConvexHull(vector<pair<Vec, Vec> >& straights, map<double, int >& hull)
{
	int n = straights.size();

	hull[0.] = 0;
	for (int i = 1; i < n; i++) {
		// 교점 구하기
		double inter = GetLineIntersect(straights[i].first, straights[i].second,
			straights[i - 1].first, straights[i - 1].second);

		// 필요 없는 교점 삭제
		while (inter <= (--hull.end())->first) {
			hull.erase(--hull.end());
			int j = (--hull.end())->second;
			inter = GetLineIntersect(straights[i].first, straights[i].second, straights[j].first, straights[j].second);
		}

		// 교점 추가
		hull[inter] = i;
	}
}

int N, M;
long long transition[100010], power[100010], sleep[100010];
inline long long f(int a, long long t) {
	return t * power[a] + transition[a];
}
int main(int argc, char** argv)
{
	cin.tie(nullptr), cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int T, test_case;
	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		memset(transition, 0, sizeof(transition));
		memset(power, 0, sizeof(power));
		memset(sleep, 0, sizeof(sleep));

		cin >> N;
		// 구간 입력
		// 작업 구간, 수면 구간
		long long r, d;
		cin >> r >> d;
		long long work = d - r;

		int _N = N - 1;
		for (int i = 0; i < _N; i++) {
			long long r_now, d_now;
			cin >> r_now >> d_now;
			work += d_now - r_now;
			sleep[i] = r_now - d;
			r = r_now;
			d = d_now;
		}

		cin >> M;
		for (int i = 0; i < M; i++) cin >> power[i];
		for (int i = 0; i < M; i++) cin >> transition[i];

		vector<pair<Vec, Vec> > vectors;
		vectors.reserve(M);
		for (int i = 0; i < M; i++)
			vectors.push_back({ Vec(0,transition[i]), Vec(1,power[i] + transition[i]) });

		map<double, int > hull;
		GetConvexHull(vectors, hull);

		long long ans = work * power[0];
		for (int i = 0; i < _N; i++) {
			auto it = hull.upper_bound(double(sleep[i]));
			--it;
			ans += f(it->second, sleep[i]);
		}

		cout << "Case #" << test_case + 1 << '\n';
		cout << ans << '\n';
	}

	return 0;
}