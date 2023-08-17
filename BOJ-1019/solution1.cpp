#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int main()
{
	string num;
	cin >> num;
	int n=0, e=1;
	for (int i = num.size()-1; i >= 0; i--) {
		num[i] -= '0';
		n += num[i]*e;
		e *= 10;
	}

	vector<long long> ans(10);

	// 일의 자리부터 각 숫자가 각 자리에서 몇 개나 나올 수 있는지 계산한다.
	// ex) num = 20일 때 1은 일의 자리에서 두 번 나타난다.
	e = 1; // 현재 계산할 자릿수
	for (int i = num.size()-1; i >= 0; i--) {
		int now = num[i];
		int back = n % e;

		// 뒤에 있는 수 + 1 만큼 숫자 now가 나왔음. 
		// ex) 87에서 now가 십의 자리 8일 때 now는 80~87까지 8번 나왔음
		ans[now--] += back + 1;	 

		// 근데 now가 0이었다면 e가 한 번 더해지기 때문에 e를 미리 빼줘야함
		if (now == -1) ans[0] -= e;	

		// e의 자릿수들은 e만큼 나왔음.
		// ex) 89까지 십의자리 7~1은 10개씩 나왔음
		while (now > 0) ans[now--] += e;

		// e자리의 수들은 e가 커짐에 따라 num/(10*e) 만큼 더 나옴
		// ex) num = 300일 때 0부터 300까지 십의 자리의 수는 3*10 번 나옴
		// 십의 자릿수 1의 경우 : 10~19, 110~119, 210~219
		// 단, 이 계산은 정확히는 300까지가 아니라 309까지 0의 개수를 계산하는데 이 예외를 위에서 처리하였음
		int tp = n / e / 10;
		for (int digit = 0; digit < 10; digit++)
			ans[digit] += tp * e;
		e *= 10;
	}

	for (int i : ans)
		cout << i << ' ';

	return 0;
}