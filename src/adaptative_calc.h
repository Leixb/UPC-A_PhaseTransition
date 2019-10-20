#ifndef __ADAPTATIVE_CALC_H__
#define  __ADAPTATIVE_CALC_H__

#include <vector>
#include <list>

std::list<std::pair<double, double>> adaptative_calc(const int &n, const int &rep, const double &dy,
		double (*func)(const int &n, const double &p, const int &rep));

#endif
