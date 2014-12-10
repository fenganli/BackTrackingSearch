#ifndef BACK_TRACKING_SEARCH_H
#define BACK_TRACKING_SEARCH_H
#define EPS 1e-9
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
class BackTrackingSearch
{
	//shrink rate
	double rate;
	//initial search point
	vector<double> searchPoint;
	//c value
	double c;
	//alpha value
	//initial alpha
	double initAlpha;
	double alpha;

	//function pointer to origin function
	double (*func)(vector<double> &);
	//derivative of origin function
	vector<double> (*deriv)(vector<double> &);
	//search direction function
	vector<double> (*direc)(vector<double> &);
	public:
	BackTrackingSearch();
	//constructor
	BackTrackingSearch(double (*_func)(vector<double> &), vector<double> (*_deriv)(vector<double> &), vector<double> (* _direc)(vector<double> &), vector<double>& _searchPoint);	

	void setParameter(double _rate, double _c, double _initAlpha);
	//search method
	vector<double> search();

	//accept the step length
	bool acceptAlpha();

	//destructor
	~BackTrackingSearch();
};
#endif
