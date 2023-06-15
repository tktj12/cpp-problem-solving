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
		for (int i = 0; i < N; i++)
			cin >> cost[i];

		double min = 100000., dL = (double)L;
		for (int i = 0; i < N - L + 1; i++)
		{
			int sum = 0;
			for (int j = 0; j < L; j++)
				sum += cost[i + j];
			
			double tp = (double)sum / dL;
			if (tp < min)
				min = tp;
			for (int j = 1; j < N - i - L + 1; j++)
			{
				sum += cost[i + L + j - 1];
				tp = (double)sum / (dL + (double)j);
				if (tp < min)
					min = tp;
			}
		}

		cout << min << '\n';
	}
}