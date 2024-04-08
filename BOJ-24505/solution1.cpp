#include <iostream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

const int MOD = 1'000'000'007;

// tree[x][y] : 길이가 x+1이고 마지막 원소가 y인 증가 수열의 개수
int tree[11][100002], N;

int Sum(int x,int y) {
	int ret = 0;
	while (y > 0) {
		ret = (ret + tree[x][y]) % MOD;
		y &= (y - 1);
	}
	return ret;
}

void Add(int x,int y,int val) {
	while (y <= N) {
		tree[x][y] = (tree[x][y] + val) % MOD;;
		y += (y & -y);
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int y; cin >> y;
		Add(0,y,1);
		for (int k = 1; k < 11; k++) {
			Add(k,y,Sum(k - 1,y-1));
		}
	}

	cout << Sum(10,N);
	
	return 0;
}