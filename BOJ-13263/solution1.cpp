#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

class Vec {
public:
	long long x, y;

	explicit Vec(long long _x=0, long long _y=0) : x(_x), y(_y) {}

	Vec operator+(const Vec rhs) const {
		return Vec(x + rhs.x, y + rhs.y);
	}
	Vec operator-(const Vec rhs) const {
		return Vec(x - rhs.x, y - rhs.y);
	}
	Vec operator*(long long scalar) const {
		return Vec(scalar * x, scalar * y);
	}
	// 외적, 스칼라만 반환
	// 반환값이 양수라면 rhs가 반시계 방향 180도 안에 위치하고, 음수라면 rhs가 시계방향 180도 안에 위치
	long long cross(const Vec rhs) const {
		return x * rhs.y - rhs.x * y;
	}
};

typedef pair<Vec, Vec> Line;
long long GetLineIntersect(Line l1, Line l2)
{
	Vec a = l1.first, b = l1.second, c = l2.first, d = l2.second;
	long long det = (b - a).cross(d - c);
	// 이 문제의 조건에 의해 평행하는 경우가 없음
	//if (det == 0) return false;

	long long temp = (c - a).cross(d - c);
	long long ret = temp / det;
	if (temp % det) ret++; // 올림
	return ret;
}

void InsertNewLine(map<long long, Line>& chull, Line line)
{
	long long intersection;
	while (1) {
		Line back = chull.rbegin()->second;
		long long back_intersection = chull.rbegin()->first;
		intersection = GetLineIntersect(back, line);
		if (intersection <= back_intersection)
			chull.erase(--chull.end());
		else break;
	}

	chull[intersection] = line;
}

long long F(long long x, Line line)
{
	return (long long)((line.first + (line.second - line.first) * x).y);
}

Line GetMarkingLine(long long x, map<long long, Line>& chull)
{
	auto iter = --chull.upper_bound(x);
	chull.erase(chull.begin(), iter);
	return chull.begin()->second;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<long long> height(n), charge(n);
	for (int i = 0; i < n; i++) cin >> height[i];
	for (int i = 0; i < n; i++) cin >> charge[i];
	if (n == 1) {
		cout << 0;
		return 0;
	}

	map<long long, Line> chull;
	chull[1] = { Vec(0,0), Vec(1,charge[0]) };
	long long cost=0;
	for (int i = 1; i < n; i++) {
		Line marking = GetMarkingLine(height[i], chull);
		cost = F(height[i], marking);
		InsertNewLine(chull, { Vec(0,cost), Vec(1, cost + charge[i]) });
	}
	cout << cost;
	
	return 0;
}