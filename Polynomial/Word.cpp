#include <cmath>
#include <algorithm>
#include <iostream>
#include "Poly.h"

namespace poly {
	const Word Word::ZERO = Word{.coef=0.0, .root=0.0, .power=0};
	const Word Word::ONE = Word{.coef=1.0, .root=0.0, .power=0};

	std::ostream &operator<<(std::ostream &stream, const Word &me) {
		if (me.coef == 0) { return stream << 0; }
		if (me.coef != 1 || me.power <= 0) { stream << me.coef; }
		if (me.power > 0) {
			if (me.coef != 1) { stream << "*"; }
			if (me.root != 0) {
				stream << "(Z+" << me.root << ")";
			} else {
				stream << "Z";
			}
			if (me.power > 1) {
				stream << "^" << me.power;
			}
		}
		return stream;
	}

	Word operator*(const Word &lhs, const double &rhs) {
		return Word{.coef = lhs.coef * rhs, .root = lhs.coef, .power = lhs.power};
	}

	Word &operator*=(Word &lhs, const double &rhs) {
		lhs.coef *= rhs;
		return lhs;
	}

	Sentence operator*(const Word &lhs, const Word &rhs) {
		Sentence result;
		return mul(result, lhs, rhs);
	}

	Sentence operator+(const Word &lhs, const Word &rhs) {
		Sentence result;
		return plus(result, lhs, rhs);
	}

	Sentence &plus(Sentence &result, const Word &lhs, const Word &rhs) {
		plus(result, lhs);
		plus(result, rhs);
		return result;
	}

	Sentence &mul(Sentence &result, const Word &lhs, const Word &rhs) {
		if (lhs.isZero() || rhs.isZero()) { return plus(result, Word::ZERO); }
		if (lhs.root == rhs.root) {
			return plus(result, Word{
				.coef = lhs.coef * rhs.coef,
				.root = lhs.root,
				.power = lhs.power + rhs.power,
			});
		}
		Sentence l, r;
		expand(l, lhs);
		expand(r, rhs);
		return mul(result, l, r);
	}


	Sentence &expand(Sentence &result, const Word &me) {
		for (unsigned int i = 0; i <= me.power; i++) {
			auto choice = chooseI(i, me.power);
			double coef = me.coef * choice * std::pow(me.root, me.power - i);
			if (coef == 0)continue;
			plus(result, Word{.coef=coef, .root = 0, .power=i});
		}
		return result;
	}

}