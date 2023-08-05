#include <iostream>
#include <vector>
#include <stack>
using namespace std;


// 1. 2-SAT �׷��� �����
// �� ȸ�ǰ� ��ġ�� �ʴ����� ��ȯ
inline bool DisJoint(const pair<int, int>& a, const pair<int, int>& b) {
	return b.second <= a.first || a.second <= b.first;
}

// ȸ�� ������ �ʿ�
// A ���� ȸ�� ������ meeting[2*A], meeting[2*A+1]
vector<vector<int>> adj;
void Make2SetGraph(vector<pair<int,int> >& meeting)
{
	int vars = meeting.size();

	// ȸ�� X�� �����ϴ� ���� X�� ���� ������ adj[2*X], �����ʴ� ���� !X�� ���� ������ adj[2*X+1]
	adj = vector<vector<int> >(2 * vars);

	for (int i = 0; i < vars; i+=2) {
		int j = i + 1;
		// ���� ȸ�� �� ���� �ϳ��� ������ �ؾ��Ѵ�.
		// !i => j , !j => i
		adj[2 * i + 1].push_back(2 * j);
		adj[2 * j + 1].push_back(2 * i);
	}

	// ��ġ�� ȸ�ǰ� ������ �� �� �ϳ��� ������ �� �Ѵ�.
	// X, Y�� ��ģ�ٸ� X => !Y, Y => !X
	for (int i = 0; i < vars; i++)
		for (int j = 0; j < i; j++)
			if (!DisJoint(meeting[i], meeting[j])) {
				adj[2 * i].push_back(2 * j + 1);
				adj[2 * j].push_back(2 * i + 1);
			}
}

// 2. ������ ������Ʈ(SCC)�� ���´�
// �׷����� �� �� �ִ� ���� �� �߰� ������ ���� ���� ������ ��ȯ
stack<int> st, scc_st;
vector<int> discover, scc_id;
int discovered_order, scc_counter;
int DfsForScc(int here)
{
	int ret = discover[here] = discovered_order++;
	st.push(here);
	// ���� ������ �˻�
	// �߰� �ȵ����� dfs�ϰ� �� ����� �� ret�� ��
	// �߰� �ƴٸ� scc�� �̹� �������� ���� �� �����ٸ� �� ������ discover�� ret�� ��
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

// �������� SCC�� ���� �� ����� ��ȯ
// ���ÿ� �������� ����� ����
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

//3. ���� SCC�� ���� (X, !X)���� �ִ��� ���캻��.
// �ذ� �ִ����� ��ȯ
bool IsValid(int meeting_size)
{
	// i�� ȸ�Ǵ� �ε��� [2*i]�� ���� i, [2*i+1]�� ���� !i
	for (int i = 0; i < meeting_size; i++) {
		if (scc_id[2 * i] == scc_id[2 * i + 1])
			return false;
	}
	return true;
}

// 4. scc_id�� ���������� �� ���� ���� ����̹Ƿ� scc_id�� ���� scc���� ���� ���Ѵ�. 
// 5. �� ���� �� ȸ�� �� �� �� �ִ� ��� �ϳ��� ȸ�Ǹ� ����.
vector<bool> SetValue(int meeting_size)
{
	vector<bool> vertex_set(2*meeting_size, false);
	// ���ÿ� DFS�� Ž���� scc�� �������� �ѹ��� �����Ͽ� ������ ���Һ��� ������ ���� ȿ���̴�.
	while (!scc_st.empty()) {
		int here = scc_st.top(); scc_st.pop();
		if (vertex_set[here]) continue;

		// !here�� set�Ѵ�.
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
	// 1. 2-SAT �׷��� �����
	Make2SetGraph(meeting);
	// 2. ������ ������Ʈ(SCC)�� ���´�
	GroupToScc();
	// 3. ���� SCC�� ���� (X, !X)���� �ִ��� ���캻��.
	if (!IsValid(meeting.size())) {
		cout << "IMPOSSIBLE\n";
		return;
	}
	else
		cout << "POSSIBLE\n";

	// 4. scc_id�� ���������� �� ���� ���� ����̹Ƿ� scc_id�� ���� scc���� ���� ���Ѵ�. 
	// => ���ÿ� DFS�� Ž���� scc�� �������� �ѹ��� �����Ͽ� ������ ���Һ��� ������ ���� ȿ���̴�.
	// 5. �� ���� �� ȸ�� �� �� �� �ִ� ��� �ϳ��� ȸ�Ǹ� ����.
	vector<bool> proceed = SetValue(meeting.size());
	// 6. �� ȸ�ǵ��� �� ������� ����Ѵ�.
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