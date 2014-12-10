#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include "backTrackingSearch.h"
using namespace std;
double rosen(vector<double> & point);
vector<double> rosenDeriv(vector<double> & point);
vector<double> rosenPk (vector<double> & point);
vector<double> rosenPk2 (vector<double> & point);
int main(int argc, char * argv[])
{
	vector<double> inputVec;
	inputVec.push_back(atof(argv[2]));
	inputVec.push_back(atof(argv[3]));
	BackTrackingSearch * searchLength;
	if (atof(argv[1]) == 1)
		searchLength = new BackTrackingSearch(rosen, rosenDeriv, rosenPk, inputVec);
	else if (atof(argv[1]) == 2)
		searchLength = new BackTrackingSearch(rosen, rosenDeriv, rosenPk2, inputVec);
	vector<double> minimizer = searchLength -> search();
	cout << minimizer[0] << "      " << minimizer[1] << endl;
	return 0;
}
double rosen(vector<double> & point)
{
	return 100 * pow(point[1] - point[0] * point[0], 2) + pow(1 - point[0], 2);
}
vector<double> rosenDeriv(vector<double> & point)
{
	vector<double> returnVec;
	returnVec.push_back(-400 * point[0] * point[1] + 400 * pow(point[0], 3) + 2 * point[0] -2);
	returnVec.push_back(200 * (point[1] - point[0] * point[0]));
	return returnVec;
}
vector<double> rosenPk(vector<double> & point)
{
	vector<double> vec = rosenDeriv(point);
	vec[0] = 0 - vec[0];
	vec[1] = 0 - vec[1];
	return vec;
}
vector<double> rosenPk2(vector<double> &point)
{
	double a11 = -400 * point[1] + 1200 * point[0] * point[0] + 2;
	double a12 = -400 * point[0];
	double a21 = -400 * point[0];
	double a22 = 200;
	vector<double> deriv = rosenDeriv(point);
	vector<double> returnVec;
	double first = -(deriv[0] * a22 + deriv[1] * (-a12)) / (a11 * a22 - a12 * a21);
	double second = -(deriv[0] * (-a21) + deriv[1] * a11) / (a11 * a22 - a12 * a21);
	returnVec.push_back(first);
	returnVec.push_back(second);
	return returnVec;
}
