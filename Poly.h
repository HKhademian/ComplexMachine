#ifndef POLY_H
#define POLY_H

void appPoly();

namespace poly {
	struct Word {
		static const Word ZERO, ONE;
		double coef = 1.0;
		double power = 1.0;
		double root = 0.0; /* TODO: use Complex */
	};



}

#endif
