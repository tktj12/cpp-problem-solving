#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N,W;
pair<int,int> incident[1002];
int cache[1002][2][1002];

int CalcDist(pair<int,int> a, pair<int,int> b)
{
	a.first -= b.first;
	a.second -= b.second;
	return max(a.first,-a.first) + max(a.second,-a.second);
}

int DP(int incident_num,int pick,int other_pos)
{
	if (incident_num >= W - 1) return 0;
	int& ret = cache[incident_num][pick][other_pos];
	if (ret != -1) return ret;

	int next = incident_num + 1;
	int a,b;
	if (pick == 0) {
		a = CalcDist(incident[incident_num],incident[next]) + DP(next,0,other_pos);
		b = CalcDist(incident[other_pos],incident[next]) + DP(next,1,incident_num);
	}
	else {
		a = CalcDist(incident[other_pos],incident[next]) + DP(next,0,incident_num);
		b = CalcDist(incident[incident_num],incident[next]) + DP(next,1,other_pos);
	}
	return ret = min(a,b);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	memset(cache,-1,sizeof(cache));

	cin >> N >> W;
	for (int i = 0; i < W; i++)
		cin >> incident[i].first >> incident[i].second;
	incident[1000] = { 1,1 };
	incident[1001] = { N,N };

	int a = CalcDist({ 1,1 },incident[0]) + DP(0,0,1001);
	int b = CalcDist({N,N}, incident[0]) + DP(0,0,1000);
	cout << min(a,b) << '\n';

	int pick,other_pos;
	if (a < b)	pick = 0,other_pos = 1001;
	else		pick = 1,other_pos = 1000;
	cout << pick + 1 << '\n';

	for (int i = 0; i < W-1; i++) {
		int next = i + 1;
		if (pick == 0) {
			a = CalcDist(incident[i],incident[next]) + DP(next,0,other_pos);
			b = CalcDist(incident[other_pos],incident[next]) + DP(next,1,i);
			if (b < a) {
				other_pos = i;
				pick = 1;
			}
		}
		else {
			a = CalcDist(incident[other_pos],incident[next]) + DP(next,0,i);
			b = CalcDist(incident[i],incident[next]) + DP(next,1,other_pos);
			if (a < b) {
				other_pos = i;
				pick = 0;
			}
		}

		cout << pick+1 << '\n';
	}
	
	return 0;
}