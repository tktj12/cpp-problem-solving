#include <iostream>

using namespace std;

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << fixed;
	cout.precision(8);

	int cost[1001];
	int T;
	cin >> T;
	for (int test_case = 0; test_case < T; test_case++)
	{
		int N, L;
		cin >> N >> L;
		for (int i = 1; i <= N; i++)
			cin >> cost[i];

		double min = 100000.;
		for (int i = 1; i <= N - L + 1; i++)
		{
			int sum = 0, j;
			for (j = i; j < i + L; j++)
				sum += cost[j];
			
			double tp = (double)sum / (double)L;
			if (tp < min) min = tp;
			for (j = i+L; j <= N; j++)
			{
				sum += cost[j];
				tp = (double)sum / (double)(j-i+1);
				if (tp < min) min = tp;
			}
		}

		cout << min << '\n';
	}
}