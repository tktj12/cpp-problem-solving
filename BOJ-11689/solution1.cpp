#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
	long long n, ans =1;
	cin >> n;
	if (n == 1) {cout << 1; return 0;}

	long long sqrtn = sqrt(n);
	for (long long i = 2; i <= sqrtn; i++) {
		int k = 0;
		while (n % i == 0) k++, n /= i;
		if (k > 0)
			ans *= pow(i, k) - pow(i, k - 1);
	}
	if (n > 1) ans *= n - 1;

	cout << ans;

	return 0;
}