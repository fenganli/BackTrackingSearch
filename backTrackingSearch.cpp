#include "backTrackingSearch.h"
BackTrackingSearch::BackTrackingSearch()
{
	//empty constructor
}
//people really care about function, derivative function, and initial points
BackTrackingSearch::BackTrackingSearch(double (*_func)(vector<double> &), vector<double> (*_deriv)(vector<double> &), vector<double> (* _direc)(vector<double> &), vector<double>& _searchPoint)
{
		func = _func;
		deriv = _deriv;
		direc = _direc;
		searchPoint = _searchPoint;
		//set up some init parameters
		rate = 0.5;
		c = 1e-2;
		initAlpha = 1;
}

void BackTrackingSearch::setParameter(double _rate, double _c, double _initAlpha)
{
		rate = _rate;
		c = _c;
		initAlpha = _initAlpha;
}
	//search function returns a local minimizer
vector<double> BackTrackingSearch::search()
{
		int step = 0;
		alpha = initAlpha;
		while (true)
		{
			if (acceptAlpha())
			{
				vector<double> pk = direc(searchPoint);
				vector<double> derivative = deriv(searchPoint);
				double originValue = func(searchPoint);
				int size = pk.size();
				//update searchPoint
				for (int i = 0; i < size; i++)
					searchPoint[i] = searchPoint[i] + alpha * pk[i];
				//update alpha
				double updateValue = func(searchPoint);
				// if the updated value is too small
				if (updateValue + EPS > originValue)
					return searchPoint;
				cout << "step: " << step << ":" << " alpha:" << alpha << " point:" << searchPoint[0] << "  " << searchPoint[1] << endl;
				step++;
				alpha = initAlpha;
			}
			else
				alpha = alpha * rate; //shrink the alpha
		}
}

bool BackTrackingSearch::acceptAlpha()
{
		vector<double> trialPoint = searchPoint;
		vector<double> derivative = deriv(searchPoint);
		vector<double> direcVec = direc(searchPoint);
		int size = trialPoint.size();
		for (int i = 0; i < size; i++)
			trialPoint[i] = searchPoint[i] + direcVec[i] * alpha;
		double newValue = func(trialPoint);
		double originValue = func(searchPoint);
		for (int i = 0; i < size; i++)
			originValue += c * alpha * derivative[i] * direcVec[i];
		if (newValue < originValue)
			return true;
		else
			return false;
}

BackTrackingSearch::~BackTrackingSearch()
{
	//nothing to do here
}
