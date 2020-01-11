#include <cmath>
#include <cstring>
#include "utils.h"
#include "ComplexNum.h"
#include "ComplexFunction.h"

namespace Complex {
	struct ComplexFunction {
		char name[10];
		ComplexFun1 func;
	} static const functions[] = {
			{"neg",   &(Complex::neg)},
			{"conj",  &(Complex::conj)},
			{"deg",   &(Complex::deg)},
			{"rad",   &(Complex::rad)},
			{"princ", &(Complex::princ)},

			{"abs",   &(Complex::lenComplex)},
			{"len",   &(Complex::lenComplex)},
			{"len2",  &(Complex::len2Complex)},
			{"arg",   &(Complex::argComplex)},
			{"re",    &(Complex::reComplex)},
			{"im",    &(Complex::imComplex)},

			{"cart",  &(Complex::cart)},
			{"euler", &(Complex::euler)},
			{"floor", &(Complex::floor)},
			{"round", &(Complex::round)},

			{"sqrt",  &(Complex::sqrt)},
			{"exp",   &(Complex::exp)},
			{"ln",    &(Complex::ln)},

			{"cos",   &(Complex::cos)},
			{"cosh",  &(Complex::cosh)},
			{"acos",  &(Complex::acos)},
			{"acosh", &(Complex::acosh)},
			{"sin",   &(Complex::sin)},
			{"sinh",  &(Complex::sinh)},
			{"asin",  &(Complex::asin)},
			{"asinh", &(Complex::asinh)},
			{"tan",   &(Complex::tan)},
			{"tanh",  &(Complex::tanh)},
			{"atan",  &(Complex::atan)},
			{"atanh", &(Complex::atanh)},
	};

	ComplexNum deg(const ComplexNum &z) {
		if (!z.isReal()) {
			throw std::invalid_argument("deg receive REAL values;");
		}
		double angle = z.getReal();
		angle /= 2.0 * M_PI / 360.0;
		return cart(angle, 0);
	}

	ComplexNum rad(const ComplexNum &z) {
		if (!z.isReal()) {
			throw std::invalid_argument("rad receive REAL values;");
		}
		double angle = z.getReal();
		angle *= 2.0 * M_PI / 360.0;
		return cart(angle, 0);
	}

	ComplexNum princ(const ComplexNum &z) {
		if (z.isCartesian()) {
			return z;
		} else {
			return euler(z.getRadius(), principle(z.getRadius()));
		}
	}


	ComplexNum pow2(const ComplexNum &z) {
		return z * z;
	}

	ComplexNum cart(const ComplexNum &z) {
		return z.isCartesian() ? z : z.toCartesian();
	}

	ComplexNum euler(const ComplexNum &z) {
		return z.isEuler() ? z : z.toEuler();
	}

	ComplexNum floor(const ComplexNum &z) {
		return cart(
				std::floor(z.getReal()),
				std::floor(z.getImag())
		);
	}

	ComplexNum round(const ComplexNum &z) {
		if (z.isCartesian()) {
			const auto re = ROUND(z.getReal());
			const auto im = ROUND(z.getImag());
			return cart(
					re,
					im
			);
		} else {
			const auto ra = ROUND(z.getRadius());
			const auto an = ROUND(z.getAngle());
			return euler(
					ra,
					an
			);
		}
	}

	ComplexNum sqrt(const ComplexNum &z) {
		//const auto radi = z.getRadius();
		//const auto angl = z.getAngle();
		//return euler(
		//		std::sqrt(radi),
		//		angl / 2
		//);
		return pow(z, 0.5);
	}

	ComplexNum exp(const ComplexNum &z) {
		const auto expx = std::exp(z.getReal());
		const auto im = z.getImag();
		return cart(
				expx * std::cos(im),
				expx * std::sin(im)
		);
	}

	ComplexNum ln(const ComplexNum &z) {
		return cart(
				std::log(z.getRadius()),
				z.getAngle()
		);
	}

	ComplexNum root(const ComplexNum &z, double c) {
		/// TODO: write complete one
		return pow(z, 1 / c);
	}

	ComplexNum pow(const ComplexNum &z, double c) {
		/// TODO: write complete one
		if (c == 2) {
			return z * z;
		}
		return euler(
				std::pow(z.getRadius(), c),
				z.getAngle() * c
		);
	}

	ComplexNum pow(const ComplexNum &z, const ComplexNum &w) {
		if (w.isReal()) {
			return pow(z, re(w));
		}
		return exp(w * ln(z));
	}


	ComplexNum cos(const ComplexNum &z) {
		const auto re = z.getReal();
		const auto im = z.getImag();
		return cart(
				std::cos(re) * std::cosh(im),
				std::sin(-re) * std::sinh(im)
		);
	}

	ComplexNum sin(const ComplexNum &z) {
		const auto re = z.getReal();
		const auto im = z.getImag();
		return cart(
				std::sin(re) * std::cosh(im),
				std::cos(re) * std::sinh(im)
		);
	}

	ComplexNum tan(const ComplexNum &z) {
		return sin(z) / cos(z);
	}

	ComplexNum acos(const ComplexNum &z) {
		return (CI * -1) * ln(z + CIe * sqrt(C1 - pow2(z)));
	}

	ComplexNum asin(const ComplexNum &z) {
		const auto i = z.isEuler() ? CIe : CI;
		return (CI * -1) * ln(z * i + sqrt(C1 - pow2(z)));
	}

	ComplexNum atan(const ComplexNum &z) {
		return CI * ln((CI + z) / (CI - z)) / 2;
	}

	ComplexNum cosh(const ComplexNum &z) {
		const auto re = z.getReal();
		const auto im = z.getImag();
		return cart(
				std::cosh(re) * std::cos(im),
				std::sinh(re) * std::sin(im)
		);
	}

	ComplexNum sinh(const ComplexNum &z) {
		const auto re = z.getReal();
		const auto im = z.getImag();
		return cart(
				std::sinh(re) * std::cos(im),
				std::cosh(re) * std::sin(im)
		);
	}

	ComplexNum tanh(const ComplexNum &z) {
		return sinh(z) / cosh(z);
	}

	ComplexNum acosh(const ComplexNum &z) {
		return ln(z + sqrt(pow2(z) - C1));
	}

	ComplexNum asinh(const ComplexNum &z) {
		return ln(z + sqrt(pow2(z) + C1));
	}

	ComplexNum atanh(const ComplexNum &z) {
		return ln(z + sqrt(pow2(z) + C1)) / 2;
	}

	ComplexFun1 selectFunc1(const char *eql, int start, int end) {
		// const static int functionsCount = 15;

		const auto len = trim(eql, start, end);
		if (len > 0) {
			for (const auto &compfun : functions) {
				const auto funName = compfun.name;
				const auto funLen = strlen(funName);
				if (len == funLen && strncasecmp(eql + start, funName, len) == 0) {
					return compfun.func;
				}
			}
		}

		return nullptr;
	}
}