#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

struct pos {
	double x;
	double y;

	bool operator==(const pos& operand) {
		if (x == operand.x && y == operand.y)
			return true;
		return false;
	}
};

bool compare(const pos& a, const pos& b) {
	if (a.y == b.y) return a.x > b.x;
	return a.y > b.y;
}

struct SLL {
	pos p;
	SLL* next = nullptr;
};

void insert(SLL*& head, pos p)
{
	SLL* cur = head;
	if (cur == nullptr) {
		head = new SLL;
		head->p = p;
		return;
	}

	while (cur->next != nullptr) cur = cur->next;
	cur->next = new SLL;
	cur->next->p = p;
}

SLL* insert2(SLL* cur, pos p) {
	cur->next = new SLL;
	cur->next->p = p;
	return cur->next;
}

void destroy(SLL* cur, int size, int now)
{
	if (now == size) return;
	destroy(cur->next, size, now+1);
	delete cur;
}
void BuildShape(SLL*&, vector<pos>&);
void AddPos(SLL* a, SLL* b, vector<pos>& coords);
double CalcHeight(SLL* shape);

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout.precision(15);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, m;
		cin >> n >> m;
		vector<pos> A(n), B(m);
		for (int i = 0; i < n; i++) cin >> A[i].x >> A[i].y;
		for (int i = 0; i < m; i++) cin >> B[i].x >> B[i].y;

		SLL* head_A, * head_B, * head_C;
		head_A = head_B = head_C = nullptr;
		BuildShape(head_A, A);
		BuildShape(head_B, B);

		vector<pos> C;
		AddPos(head_A, head_B, C);
		AddPos(head_B, head_A, C);

		BuildShape(head_C, C);
		cout << CalcHeight(head_C) << '\n';

		destroy(head_A, A.size(), 0);
		destroy(head_B, B.size(), 0);
		destroy(head_C, C.size(), 0);
	}

	return 0;
}

double distance(pos a, pos b){
	return pow(a.x - b.x, 2) + pow(a.y - b.y, 2); // sqrt 없이
}

double const pi = acos(0) * 2.;
double angle(pos a, pos b) {
	double ret = atan2(b.y - a.y, b.x - a.x) * 180 / pi;
	if (ret < 0)
		ret = 360. + ret;
	return ret;
}

// 반시계 방향으로 돌면 a가 b보다 s에게 더 가까운 각도인가
bool IsClockwiseCloser(double s, double a, double b)
{
	if (s >= 180) {
		if (a > s) return false;
		else return a > b;
	}

	if (a > 180) a -= 360;
	if (b > 180) b -= 360;
	return a > b;
}

// 한 좌표는 시계방향의 다음 좌표를 가리키고 있음
void BuildShape(SLL*& head, vector<pos>& coords)
{
	if (coords.size() == 0) return;

	// 제일 위에 있는 좌표를 0번으로 (두 개면 오른쪽 좌표)
	sort(coords.begin(), coords.end(), compare);
	//shape.erase(unique(shape.begin(),shape.end() ), shape.end() );
	insert(head, coords[0]);
	vector<int> not_chosen(coords.size());
	for (int i = 0; i < not_chosen.size(); ++i)
		not_chosen[i] = i;
	not_chosen.erase(not_chosen.begin());
		
	double pre_angle = 360.;
	SLL* cur = head;
	while(not_chosen.empty() == false) {
		int choice = 0;
		double max_angle = angle(cur->p, coords[not_chosen[0] ]);
		for (int i = 1; i < not_chosen.size(); ++i) {
			double ang = angle(cur->p, coords[not_chosen[i] ]);
			if (IsClockwiseCloser(pre_angle, ang, max_angle)) {
				max_angle = ang;
				choice = i;
			}
		}
		cur = insert2(cur, coords[not_chosen[choice] ]);
		not_chosen.erase(not_chosen.begin() + choice);
		pre_angle = max_angle;
	}

	cur->next = head;
}

double CalcPoint(vector<double>& a, vector<double>& b)
{
	return (b[1] - a[1]) / (a[0] - b[0]);
}

vector<double> straight(pos a, pos b)
{
	vector<double> ret(2);
	ret[0] = (a.y - b.y) / (a.x - b.x);
	ret[1] = (a.x * b.y - b.x * a.y) / (a.x - b.x);
	return ret;
}

// 각도 a를 12시라고 했을 때 각도 b가 6시~12시 사이인지
bool GoingInside(double a, double b)
{
	if (a > 180 && b < a - 180) b += 360;
	return (a < b && b < a + 180);
}

// 도형 a가 도형 b와 겹치는 공간의 도형 a의 좌표들을 coords에 저장
void AddPos(SLL* a, SLL* b, vector<pos>& coords)
{
	SLL* start_a = a, *cur_a = a;
	int lap = 0;
	bool inside = false;
	while (1) {
		SLL* start_b = b, * cur_b = b;
		vector<double> straight_a = straight(cur_a->p, cur_a->next->p);
		while (1) {
			vector<double> straight_b = straight(cur_b->p, cur_b->next->p);
			double x = CalcPoint(straight_a, straight_b);
			if (cur_a->p.x < x && x < cur_a->next->p.x ||
				cur_a->next->p.x < x && x < cur_a->p.x)
			{
				if (cur_b->p.x < x && x < cur_b->next->p.x ||
					cur_b->next->p.x < x && x < cur_b->p.x)
				{

					if (inside) inside = false;
					else {
						double angle_a = angle(cur_a->p, cur_a->next->p);
						double angle_b = angle(cur_b->p, cur_b->next->p);

						if (GoingInside(angle_a, angle_b)) {
							inside = true;
							// 접점의 좌표 구해서 coords에 삽입
							pos point;
							point.x = x;
							point.y = straight_a[0] * x + straight_a[1];
							coords.push_back(point);
						}
					}
					break;
				}
			}

			cur_b = cur_b->next;
			if (cur_b == start_b) break;
		}

		if (inside)
			coords.push_back(cur_a->next->p);
		cur_a = cur_a->next;
		if (cur_a == start_a) lap++;
		if (lap>0 && !inside) break;
	}
}

double CalcHeight(SLL* shape)
{
	if (shape == nullptr) return 0.;

	pos top = shape->p;
	SLL* cur = shape->next;
	double best = 0.;
	while (1) {
		if (cur->next->p.x < top.x && top.x < cur->p.x) {
			pos a = cur->p, b = cur->next->p;
			best = top.y - a.y + (a.y - b.y) * (top.x - a.x) / (b.x - a.x);
		}
		cur = cur->next;
		if (cur == shape) break;
	}

	while (1) {
		if (cur->next->p.y < cur->p.y) {
			cur = cur->next;
		}
		else if (cur->next->p.y == cur->p.y) {
			if (top.x < cur->p.x) 
				cur = cur->next;
			break;
		}
		else break;
		cur = cur->next;
	}

	pos bottom = cur->p;
	SLL* start = cur;
	while (1) {
		if (cur->p.x < bottom.x && bottom.x < cur->next->p.x) {
			pos a = cur->p, b = cur->next->p;
			double cand = a.y-bottom.y + (b.y - a.y) * (bottom.x - a.x) / (b.x - a.x);
			if (cand > best) best = cand;
			break;
		}
		cur = cur->next;
		if (cur == start)break;
	}
	return best;
}