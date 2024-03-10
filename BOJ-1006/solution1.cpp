#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n_room,soldier;
int enemy[10000][2], cache[10001][2][2];
const int SINGLE = 0, HORIZON=1, INF=987654321;

// 이전의 선택이 prev_choice이고 현재 살펴볼 위치가 원타곤의 section번 구역의 side(안 또는 바깥)위치이다.
// 현재 위치부터 요원을 최소로 배치하는 경우를 구한다.
int DP(int section,bool side,int prev_choice) {
	if (section >= n_room) return 0;

	int& ret = cache[section][side][prev_choice];
	if (ret != -1) return ret;
	ret = 0;

	int r = soldier - enemy[section][side];
	if (side == 0) {
		switch (prev_choice) {
		case HORIZON:
			ret = DP(section + 1,0,SINGLE); 
			if (r >= enemy[section + 1][0])
				ret = min(ret,DP(section + 1,1,SINGLE)); // HORIZON
			break;
		case SINGLE:
			ret = DP(section,1,SINGLE); 
			if (r >= enemy[section + 1][0])
				ret = min(ret,DP(section,1,HORIZON));
			if (r >= enemy[section][1])
				ret = min(ret,DP(section + 1,0,SINGLE)); // VERTICAL
			break;
		default:
			return -1;
		}
	}
	else {
		switch (prev_choice) {
		case HORIZON:
			ret = DP(section + 1,1,SINGLE);
			if(r >= enemy[section+1][1])
				ret = min(ret,DP(section + 2,0,SINGLE)); // HORIZON
			break;
		case SINGLE:
			ret = DP(section + 1,0,SINGLE);
			if (r >= enemy[section + 1][1])
				ret = min(ret,DP(section + 1,0,HORIZON));
			break;
		default:
			return -1;
		}
	}

	return ++ret;
}

int main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		memset(cache,-1,sizeof(cache));
		cin >> n_room >> soldier;
		for(int side=0;side<2;side++)
			for (int i = 0; i < n_room; i++)
				cin >> enemy[i][side];

		int ans = DP(0,0,SINGLE);
		if (n_room > 2) {
			int back = n_room - 1;
			if (enemy[back][0] + enemy[0][0] <= soldier) {
				int tp = enemy[back][0];
				enemy[back][0] = INF;
				memset(cache,-1,sizeof(cache));
				ans = min(ans,DP(0,1,SINGLE));
				swap(tp,enemy[back][0]);
			}
			if (enemy[back][1] + enemy[0][1] <= soldier) {
				int tp = enemy[back][1];
				enemy[back][1] = INF;
				memset(cache,-1,sizeof(cache));
				ans = min(ans,DP(0,0,HORIZON));
				swap(tp,enemy[back][1]);
			}
			if (enemy[back][0] + enemy[0][0] <= soldier &&
				enemy[back][1] + enemy[0][1] <= soldier) {
				n_room--;
				memset(cache,-1,sizeof(cache));
				ans = min(ans,DP(1,0,SINGLE) + 2);
			}
		}

		cout << ans << '\n';
	}
	return 0;
}