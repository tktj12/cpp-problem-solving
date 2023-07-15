#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<double> solve(vector<double>);
vector<double> differentiate(vector<double>&);
double f(vector<double>&, double);
double findRoot(double, double, vector<double>&);

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout.precision(10);

	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		vector<double> coefficient(n+1);
		for (int i = 0; i <= n; ++i)
			cin >> coefficient[i];

		vector<double> answer = solve(coefficient);
		for (int i = 0; i < answer.size(); ++i)
			cout << answer[i] << ' ';
		cout << '\n';
	}
	return 0;
}

// 다항식의 계수가 coef일 때 해를 반환
vector<double> solve(vector<double> coef)
{
	int degree = coef.size()-1;
	vector<double> ret;
	if (degree == 2) {
		double _2a = 2*coef[0];
		double b = coef[1];
		double bb = b * b;
		double _4ac = 4* coef[0] *coef[2];

		if (bb < _4ac) return {};
		else if (bb == _4ac) {
			ret.push_back(-b / _2a);
		}
		else {
			ret.push_back((-b - sqrt(bb - _4ac)) / _2a);
			ret.push_back((-b + sqrt(bb - _4ac)) / _2a);
		}
		return ret;
	}

	vector<double> extreme_values = solve(differentiate(coef));
	sort(extreme_values.begin(), extreme_values.end());
	int next_is_positive;
	// 차수가 홀수고, 최고차항의 계수가 양수 or 차수가 짝수도 최고차항의 계수가 음수일 때
	if (degree % 2 == 1 && coef[0] > 0 || degree % 2 ==0&& coef[0] < 0) 
		next_is_positive = true;
	else // 차수가 홀수고, 최고차항의 계수가 음수 or 차수가 짝수도 최고차항의 계수가 양수일 때
		next_is_positive = false;

	double x = extreme_values.back();
	for (; x < 10000.; x += 10.)
		if (coef[0] > 0 && f(coef, x) > 0) break;
		else if (coef[0] < 0 && f(coef, x) < 0)break;
	if (x >= 10000.) exit(-1);
	if (x > extreme_values.back()) extreme_values.push_back(x);
	
	double left = extreme_values[0] - 10.;
	for (; left > -10000.; left -= 10.) {
		if (next_is_positive && f(coef, left) < 0) break;
		else if (!next_is_positive && f(coef, left) > 0)break;
	}
	if (left <= -10000.) exit(-1);

	for (int i = 0; i < extreme_values.size(); ++i) {
		double& ev = extreme_values[i];
		if (next_is_positive && f(coef,ev) > 0) {
			ret.push_back(findRoot(left, ev, coef));
			left = ev;
			next_is_positive = false;
		}
		else if (!next_is_positive && f(coef, ev) < 0) {
			ret.push_back(findRoot(ev, left, coef));
			left = ev;
			next_is_positive = true;
		}
		else {
			if (f(coef, ev) == 0.) ret.push_back(ev);
			if (i + 1 < extreme_values.size()) {
				left = extreme_values[i + 1];
				++i;
			}
		}
	}
	return ret;
}

// 계수가 coef인 다항식을 미분하여 각 항의 계수를 반환
vector<double> differentiate(vector<double>& coef)
{
	int degree = coef.size() - 1;
	vector<double> ret(degree);

	for (int i = 0; i < degree; ++i) {
		ret[i] = coef[i] * (degree - i);
	}
	return ret;
}

// 계수가 coef인 다항식에 x를 대입해서 그 결과를 반환
double f(vector<double>& coef, double x)
{
	int degree = coef.size() - 1;
	double ret = 0;
	for (int i = 0; i < degree; ++i)
		ret += coef[i] * pow(x, degree - i);
	return ret + coef.back();
}

// 계수가 coef인 다항식이 구간 (lo, hi] 사이에 f(x) = 0이 있다고 가정하고 해당하는 x의 근사치를 반환
double findRoot(double lo, double hi, vector<double>& coef)
{
	// 불변식 : f(lo) < 0
	for (int i = 0; i < 100; ++i) {
		double mid = (lo + hi) / 2.;
		if (f(coef, mid) < 0)
			lo = mid;
		else hi = mid;
	}
	double mid = (lo + hi) / 2.;
	if (fabs(int(mid) - mid) < 1e-8) return int(mid);
	else return mid;
}