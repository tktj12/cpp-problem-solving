#include <iostream>
#include <vector>
#include <map>
using namespace std;

int arr[40];
int N, S, mid;
map<int,int> intmap;
long long ans;

void PickInLeftHalf(int idx, int sum, bool picked)
{
	if (idx == mid) {
		if (picked) intmap[sum]++;
		return;
	}

	PickInLeftHalf(idx + 1, sum + arr[idx], true);
	PickInLeftHalf(idx + 1, sum, picked);
}

void PickInRightHalf(int idx, int sum, bool picked)
{
	if (idx == N) {
		if (!picked) return;

		if (sum == S) ans++;
		ans += intmap[S - sum];
		return;
	}

	PickInRightHalf(idx + 1, sum + arr[idx], true);
	PickInRightHalf(idx + 1, sum, picked);
}

int main()
{
	cin >> N >> S;
	for (int i = 0; i < N; i++) cin >> arr[i];
	mid = N / 2;
	PickInLeftHalf(0, 0, false);
	PickInRightHalf(mid, 0,false);
	ans += intmap[S];

	cout << ans;
	
	return 0;
}