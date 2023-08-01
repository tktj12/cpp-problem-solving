#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class SquareMatrix {
public:
	vector<vector<double> > e;
	int size;
	
	SquareMatrix(int n) : size(n), e(n, vector<double>(n,0.)) {	}

	vector<double>& operator[](int n) {
		return e[n];
	}
};

int main()
{
	cout.precision(10);

	SquareMatrix mat(3);
	mat[1][2] = 1;

	

	return 0;
}