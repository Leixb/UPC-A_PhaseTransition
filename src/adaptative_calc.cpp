#include <list>
#include <vector>

#include "adaptative_calc.h"

using std::list;
using std::vector;
using std::pair;

#define DEPTH_LIMIT 7
#define PART_INI 10

template<typename T>
T abs(const T &a) {return (a<0)? -a : a;}

void calculate(list<pair<double, double>> &l, vector<list<pair<double,double> >::iterator> &v,
		const int &n, const double &dy, const int&rep,
		double (*func)(const int &n, const double &p, const int &rep),
		const int &depth=0) {
	if (depth > DEPTH_LIMIT) return; // si ens passem del limit de profunditat, acaba

	// Vector d'iteradors a nodes per calcular
	vector <list<pair<double, double> >::iterator> next_it;

	for (const auto it : v) {
		auto prev = it;
		advance(prev, -1);

		if (it->second < -0.5) // Nomes calculem els que no han estat calculats previament (majors iguals a 0
			it->second = func(n, it->first, rep);

		if (depth == DEPTH_LIMIT) continue; // No afegim mes si ja estem al limit

		// Si la diferencia entre consecutius es major a dy, afegim punt mig a calcular.
		if (abs(it->second - prev->second) > dy) {
			next_it.push_back(l.emplace(it, (it->first + prev->first)/2, -1));
			next_it.push_back(it);
		}
	}

	// Si la llista a calcular no esta buida, crida seguent nivell
	if (next_it.size() > 0)
		calculate(l, next_it, n, dy, rep, func, depth+1);
}

// Evalua funcio dividint recursivament fins que la diferencia entre punts consecutius
// sigui sempre menor a dy. (o s arribi al limit de recursivitat DEPTH_LIMIT)
list<pair<double, double>> adaptative_calc(const int &n, const int &rep, const double &dy,
		double (*func)(const int &n, const double &p, const int &rep)) {

	list<pair<double, double> > l;
	l.emplace_back(0, func(n, 0, rep));

	vector<list<pair<double, double> >::iterator> v(PART_INI);

	// Divideix el rang d entrada en PART_INI particions
	for (std::size_t i = 1; i <= PART_INI; ++i)
		v[i-1] = l.emplace(l.end(), double(i)/double(PART_INI), -1);


	// Iniciem crida recursiva
	calculate(l, v, n, dy, rep, func);

	return l;
}
