#include <iostream>
#include <vector>
using namespace std;

vector<bool> visited;
vector<int> ascend_match, descend_match;
bool DFS(int ascend, vector<vector<int>>& as_to_des) {
	if (visited[ascend]) return false;
	visited[ascend] = true;

	for (int descend : as_to_des[ascend]) {
		if (descend_match[descend] == -1 || DFS(descend_match[descend], as_to_des) ) {
			ascend_match[ascend] = descend;
			descend_match[descend] = ascend;
			return true;
		}
	}
	return false;
}

int BipartiteMatch(int as, int des, vector<vector<int>>& as_to_des) {
	ascend_match = vector<int>(as, -1);
	descend_match = vector<int>(des, -1);

	int ret = 0;
	for (int i = 0; i < as;i++) {
		visited = vector<bool>(as, false);
		if (DFS(i, as_to_des))
			ret++;
	}
	return ret;
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
		vector<string> map(n);
		for (int i = 0; i < n; i++) cin >> map[i];

		vector<vector<int> > ascend_group(n, vector<int>(n, -1));
		vector<vector<int> > descend_group(n, vector<int>(n, -1));
		int as = 0, des = 0;
		for(int i=0;i<n;i++)
			for (int j = 0; j < n; j++) {
				if (map[i][j] == '*') continue;
				
				if (descend_group[i][j] == -1) {
					for (int k = 0; i + k < n && j + k < n; k++) {
						if (map[i + k][j + k] == '*') break;
						descend_group[i + k][j + k] = des;
					}
					des++;
				}

				if (ascend_group[i][j] == -1) {
					for (int k = 0; i + k < n && j - k >= 0; k++) {
						if (map[i + k][j - k] == '*') break;
						ascend_group[i + k][j - k] = as;
					}
					as++;
				}
			}

		// ascend에서 descend로 가는 간선에 대한 인접 리스트
		// 체스판 상의 (장애물이 아닌) 한 점은 무조건 하나의 ascend와 하나의 descend가 유일하게 만나는 점이라는 것을 이용해서 그래프를 생성
		vector<vector<int>> as_to_des(as);
		for(int i=0;i<n;i++)
			for (int j = 0; j < n; j++) {
				if (map[i][j] == '*') continue;

				int as_num = ascend_group[i][j];
				int des_num = descend_group[i][j];
				as_to_des[as_num].push_back(des_num);
			}

		cout << BipartiteMatch(as, des, as_to_des) << '\n';
	}
	return 0;
}