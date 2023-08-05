#include <iostream>
#include <vector>
#include <stack>
using namespace std;


// 1. 2-SAT 그래프 만들기
// 두 회의가 겹치지 않는지를 반환
inline bool DisJoint(const pair<int, int>& a, const pair<int, int>& b) {
	return b.second <= a.first || a.second <= b.first;
}

// 회의 정보가 필요
// A 팀의 회의 정보는 meeting[2*A], meeting[2*A+1]
vector<vector<int>> adj;
void Make2SetGraph(vector<pair<int,int> >& meeting)
{
	int vars = meeting.size();

	// 회의 X를 진행하는 상태 X의 인접 정점은 adj[2*X], 하지않는 상태 !X의 인접 정점은 adj[2*X+1]
	adj = vector<vector<int> >(2 * vars);

	for (int i = 0; i < vars; i+=2) {
		int j = i + 1;
		// 팀의 회의 두 개중 하나는 무조건 해야한다.
		// !i => j , !j => i
		adj[2 * i + 1].push_back(2 * j);
		adj[2 * j + 1].push_back(2 * i);
	}

	// 겹치는 회의가 있으면 둘 중 하나는 무조건 못 한다.
	// X, Y가 겹친다면 X => !Y, Y => !X
	for (int i = 0; i < vars; i++)
		for (int j = 0; j < i; j++)
			if (!DisJoint(meeting[i], meeting[j])) {
				adj[2 * i].push_back(2 * j + 1);
				adj[2 * j].push_back(2 * i + 1);
			}
}

// 2. 강결합 컴포넌트(SCC)로 묶는다
// 그래프상 갈 수 있는 정점 중 발견 순서가 가장 빠른 정점을 반환
stack<int> st, scc_st;
vector<int> discover, scc_id;
int discovered_order, scc_counter;
int DfsForScc(int here)
{
	int ret = discover[here] = discovered_order++;
	st.push(here);
	// 인접 정점들 검사
	// 발견 안됐으면 dfs하고 그 결과와 내 ret을 비교
	// 발견 됐다면 scc로 이미 묶였는지 보고 안 묶였다면 그 정점의 discover랑 ret를 비교
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		if (discover[there] == -1)
			ret = min(ret, DfsForScc(there));
		else if (scc_id[there] == -1)
			ret = min(ret, discover[there]);
	}

	if (ret == discover[here]) {
		while (1) {
			int there = st.top(); st.pop();
			scc_st.push(there);
			scc_id[there] = scc_counter;
			if (there == here) break;
		}
		scc_counter++;
	}

	return ret;
}

// 정점들을 SCC로 묶고 그 결과를 반환
// 스택에 위상정렬 결과를 담음
void GroupToScc()
{
	int vars = adj.size();
	st = scc_st = stack<int>();
	discover = scc_id = vector<int>(vars, -1);
	discovered_order = scc_counter = 0;

	for (int i = 0; i < vars; i++) {
		if (discover[i] == -1)
			DfsForScc(i);
	}
}

//3. 같은 SCC에 속한 (X, !X)쌍이 있는지 살펴본다.
// 해가 있는지를 반환
bool IsValid(int meeting_size)
{
	// i번 회의는 인덱스 [2*i]가 상태 i, [2*i+1]이 상태 !i
	for (int i = 0; i < meeting_size; i++) {
		if (scc_id[2 * i] == scc_id[2 * i + 1])
			return false;
	}
	return true;
}

// 4. scc_id의 내림차순은 곧 위상 정렬 결과이므로 scc_id가 높은 scc부터 값을 정한다. 
// 5. 한 팀이 두 회의 다 할 수 있는 경우 하나의 회의만 고른다.
vector<bool> SetValue(int meeting_size)
{
	vector<bool> vertex_set(2*meeting_size, false);
	// 스택에 DFS로 탐색한 scc의 정점들을 한번에 저장하여 마지막 원소부터 꺼내면 같은 효과이다.
	while (!scc_st.empty()) {
		int here = scc_st.top(); scc_st.pop();
		if (vertex_set[here]) continue;

		// !here을 set한다.
		if (here % 2 == 0)
			vertex_set[here + 1] = true;
		else
			vertex_set[here - 1] = true;
	}

	vector<bool> proceed(meeting_size, false);
	for (int i = 0; i < meeting_size; i++)
		proceed[i] = vertex_set[2 * i];

	return proceed;
}

void Solve(vector<pair<int, int> >& meeting)
{
	int n = meeting.size()/2;
	// 1. 2-SAT 그래프 만들기
	Make2SetGraph(meeting);
	// 2. 강결합 컴포넌트(SCC)로 묶는다
	GroupToScc();
	// 3. 같은 SCC에 속한 (X, !X)쌍이 있는지 살펴본다.
	if (!IsValid(meeting.size())) {
		cout << "IMPOSSIBLE\n";
		return;
	}
	else
		cout << "POSSIBLE\n";

	// 4. scc_id의 내림차순은 곧 위상 정렬 결과이므로 scc_id가 높은 scc부터 값을 정한다. 
	// => 스택에 DFS로 탐색한 scc의 정점들을 한번에 저장하여 마지막 원소부터 꺼내면 같은 효과이다.
	// 5. 한 팀이 두 회의 다 할 수 있는 경우 하나의 회의만 고른다.
	vector<bool> proceed = SetValue(meeting.size());
	// 6. 고른 회의들을 팀 순서대로 출력한다.
	for (int i = 0; i < n; i++) {
		int choice;
		if (proceed[2 * i]) choice = 2 * i;
		else choice = 2 * i + 1;

		cout << meeting[choice].first << ' ' << meeting[choice].second << '\n';
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		int meeting_size = 2 * n;
		vector<pair<int, int> > meeting(meeting_size);
		for (int i = 0; i < n; i++) {
			cin >> meeting[2*i].first >> meeting[2 * i].second;
			cin >> meeting[2 * i +1].first >> meeting[2 * i +1].second;
		}

		Solve(meeting);
	}
	return 0;
}