#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int height[100000];
// mid�� �����ϴ� ���簢��, [lo,mid-1]���� ���� ū ���簢��, [mid+1,hi]���� ���� ū ���簢��
// �� ���� ū ���� ��ȯ
int Divide(int lo, int hi)
{
	if (lo > hi) return 0;
	if (lo == hi) return height[lo];

	int mid = (lo + hi) / 2;
	int ret = 0, h = height[mid], w = 1;

	int left = mid - 1, right = mid + 1;
	while (lo <= left || right <= hi) {
		while (left >= lo && height[left] >= h)
			left--, w++;
		while (right <= hi && height[right] >= h)
			right++, w++;

		ret = max(ret, w * h);
		
		if (lo <= left && right <= hi)
			h = max(height[left], height[right]);
		else if (lo <= left)
			h = height[left];
		else
			h = height[right];
	}

	return max(ret, max(Divide(lo, mid - 1), Divide(mid + 1, hi)) );
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> height[i];

	cout << Divide(0, n - 1);
	
	return 0;
}