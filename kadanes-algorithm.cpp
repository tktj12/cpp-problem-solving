int N; cin >> N;
int ans = -987654321;
int p_sum = 0, min_sum = 0;
for (int i = 0; i < N; i++) {
	int x; cin >> x;
	p_sum += x;
	ans = max(ans, p_sum - min_sum);
	min_sum = min(min_sum, p_sum);
}
cout << ans << '\n';