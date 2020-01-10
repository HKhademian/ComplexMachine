#ifndef COMPLEX_FUNCTION_H
#define COMPLEX_FUNCTION_H

#include "ComplexNum.h"

namespace Complex {
	typedef ComplexNum (*ComplexFun1)(const ComplexNum &);

	ComplexNum cart(const ComplexNum &z);

	ComplexNum euler(const ComplexNum &z);

	ComplexNum floor(const ComplexNum &z);

	ComplexNum round(const ComplexNum &z);

	ComplexNum pow2(const ComplexNum &z);

	ComplexNum sqrt(const ComplexNum &z);

	ComplexNum exp(const ComplexNum &z);

	ComplexNum ln(const ComplexNum &z);


	ComplexNum root(const ComplexNum &z, double c);

	ComplexNum pow(const ComplexNum &z, double c);

	ComplexNum pow(const ComplexNum &z, const ComplexNum &w);


	ComplexNum cos(const ComplexNum &z);

	ComplexNum sin(const ComplexNum &z);

	ComplexNum tan(const ComplexNum &z);

	ComplexNum acos(const ComplexNum &z);

	ComplexNum asin(const ComplexNum &z);

	ComplexNum atan(const ComplexNum &z);

	ComplexNum cosh(const ComplexNum &z);

	ComplexNum sinh(const ComplexNum &z);

	ComplexNum tanh(const ComplexNum &z);

	ComplexNum acosh(const ComplexNum &z);

	ComplexNum asinh(const ComplexNum &z);

	ComplexNum atanh(const ComplexNum &z);


	ComplexNum deg(const ComplexNum &z);

	ComplexNum rad(const ComplexNum &z);

	ComplexNum princ(const ComplexNum &z);


	ComplexFun1 selectFunc1(const char *eql, int start, int end);

}
#endif
