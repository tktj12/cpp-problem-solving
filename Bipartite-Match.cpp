// 구종만, 『프로그래밍 대회에서 배우는 알고리즘 문제해결 전략』 (서울:인사이트, 2012), 1019
// 이분 매칭

#include <vector>
using namespace std;

const int MAX_N = 100;
// A와 B의 정점의 개수
int n,m;
bool adj[MAX_N][MAX_N];
// 각 정점에 매칭된 상대 정점의 번호를 저장한다.
vector<int> aMatch,bMatch;
// dfs()의 방문 여부
vector<bool> visited;
// A의 정점인 a에서 B의 매칭되지 않은 정점으로 가는 경로를 찾는다.
bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for(int b = 0;b<m;++b) 
		if(adj[a][b])
			// b가 이미 매칭되어있다면 bMatch[b]에서부터 시작해 증가 경로를 찾는다.
			if (bMatch[b] == -1 || dfs(bMatch[b])) {
				// 증가 경로 발견! a와 b를 매치시킨다.
				aMatch[a] = b;
				bMatch[b] = a;
				return true;
			}
	return false;
}

// aMatch, bMatch 배열을 계산하고 최대 매칭의 크기를 반환한다.
int BipartiteMatch() {
	// 처음에는 어떤 정점도 연결되어 있지 않다.
	aMatch = vector<int>(n,-1);
	bMatch = vector<int>(m,-1);
	int size = 0;
	for (int start = 0; start < n; ++start) {
		visited = vector<bool>(n,false);
		//dfs를 이용해 start에서 시작하는 증가 경로를 찾는다.
		if (dfs(start))
			++size;
	}
	return size;
}