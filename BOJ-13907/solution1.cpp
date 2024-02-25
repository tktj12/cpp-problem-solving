#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

class Vec {
public:
	int x,y;

	explicit Vec(int _x = 0,int _y = 0) : x(_x),y(_y) {}

	Vec operator+(const Vec rhs) const {
		return Vec(x + rhs.x,y + rhs.y);
	}
	Vec operator-(const Vec rhs) const {
		return Vec(x - rhs.x,y - rhs.y);
	}
	Vec operator*(int scalar) const {
		return Vec(scalar * x,scalar * y);
	}
	// 외적, 스칼라만 반환
	// 반환값이 양수라면 rhs가 반시계 방향 180도 안에 위치하고, 음수라면 rhs가 시계방향 180도 안에 위치
	int cross(const Vec rhs) const {
		return x * rhs.y - rhs.x * y;
	}
};

typedef pair<Vec,Vec> Line;
int GetLineIntersect(Line l1,Line l2)
{
	Vec a = l1.first,b = l1.second,c = l2.first,d = l2.second;
	int det = (b - a).cross(d - c);
	// 이 문제의 조건에 의해 평행하는 경우가 없음
	// if (det == 0) return false;

	double temp = (double)(c - a).cross(d - c) / det;
	temp = a.x + (b - a).x*temp;
	int ret = temp;
	if (temp - ret != 0) return ret + 1;
	else return ret;
}

void InsertNewLine(map<int ,Line>& chull,Line line)
{
	int intersection;
	while (1) {
		Line back = chull.rbegin()->second;
		int back_intersection = chull.rbegin()->first;
		intersection = GetLineIntersect(back,line);
		if (intersection <= back_intersection)
			chull.erase(--chull.end());
		else break;
	}

	chull[intersection] = line;
}

const int INF = 987654321;
int city_num,road_num,raise_num,start,dest;
// lowest_cost[city] : city번 도시에서 지금까지 나온 최저 코스트의 도로 수 {도로 수, 최저 코스트}
pair<int,int> lowest_cost[1001];
vector<vector<pair<int,int>>> adj;

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	fill(lowest_cost,lowest_cost + 1001,make_pair(INF,INF));

	cin >> city_num >> road_num >> raise_num >> start >> dest;
	adj = vector<vector<pair<int,int>>>(city_num + 1);
	while (road_num--) {
		int u,v,c;
		cin >> u >> v >> c;
		adj[u].push_back({ v,c });
		adj[v].push_back({ u,c });
	}

	// {cost, road, city}
	priority_queue<pair<pair<int,int>,int>> pq;
	pq.push({ {0,0}, start });
	map<int,Line> chull;
	chull[-1] = { Vec(0,0),Vec(0,1) };
	while (!pq.empty()) {
		int here = pq.top().second;
		int cost = -pq.top().first.first;
		int road = -pq.top().first.second;
		pq.pop();

		if (lowest_cost[here].first <= road)
			continue;

		lowest_cost[here] = { road,cost };
		if (here == dest) {
			InsertNewLine(chull,{ Vec(0,cost),Vec(1,cost+road) });
			continue;
		}
		
		for (pair<int,int>& e : adj[here]) {
			int there = e.first;
			int there_cost = e.second;
			pq.push({ {-cost - there_cost, -road-1}, there });
		}
	}
	
	cout << chull[0].first.y << '\n';
	int total_inc = 0,idx = 0;
	while (raise_num--) {
		int n; cin >> n;
		total_inc += n;
		auto it = --(chull.upper_bound(total_inc));
		int cost = it->second.first.y;
		int road = it->second.second.y - cost;
		cout << cost + road * total_inc << '\n';
	}

	return 0;
}