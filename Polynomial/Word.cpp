#include <cmath>
#include <iostream>
#include "../Complex/utils.h"
#include "Polynomial.h"

namespace poly {
	const Word Word::ZERO = Word{.coef=0.0, .root=0.0, .power=0};
	const Word Word::ONE = Word{.coef=1.0, .root=0.0, .power=0};
	const Word Word::Z = Word{.coef=1.0, .root=0.0, .power=1};
	const Word Word::Z2 = Word{.coef=1.0, .root=0.0, .power=2};

	std::ostream &operator<<(std::ostream &stream, const Word &me) {
		const auto coef = ROUND(me.coef);
		const auto root = ROUND(me.root);
		const auto power = me.power;
		if (coef == 0) { return stream << 0; }
		if (coef != 1 || power == 0) {
			if (coef > 0) stream << coef;
			else stream << "(" << coef << ")";
		}
		if (power != 0) {
			if (coef != 1) { stream << "*"; }
			if (root != 0) {
				stream << "(Z";
				if (root > 0) stream << "+" << root;
				else stream << root;
				stream << ")";
			} else {
				stream << "Z";
			}
			if (power > 1) {
				stream << "^" << power;
			} else if (power < 1) {
				stream << "^(" << power << ")";
			}
		}
		return stream;
	}

	Word operator*(const Word &lhs, const double &rhs) {
		return Word{.coef = lhs.coef * rhs, .root = lhs.root, .power = lhs.power};
	}

	Word operator*(const double &lhs, const Word &rhs) {
		return rhs * lhs;
	}

	Word &operator*=(Word &lhs, const double &rhs) {
		lhs.coef *= rhs;
		return lhs;
	}

	Sentence operator*(const Word &lhs, const Word &rhs) {
		Sentence result;
		return mul(result, lhs, rhs);
	}

	Word operator/(const Word &lhs, const double &rhs) {
		if (rhs == 0) return lhs;//ERR
		return Word{.coef = lhs.coef / rhs, .root = lhs.coef, .power = lhs.power};
	}

	Word &operator/=(Word &lhs, const double &rhs) {
		if (rhs == 0) return lhs;//ERR
		lhs.coef /= rhs;
		return lhs;
	}

	Sentence operator/(const Word &lhs, const Word &rhs) {
		Sentence quotient, remainder;
		div(quotient, remainder, lhs, rhs);
		return quotient;
	}

	Sentence operator%(const Word &lhs, const Word &rhs) {
		Sentence quotient, remainder;
		div(quotient, remainder, lhs, rhs);
		return remainder;
	}

	Sentence operator+(const Word &lhs, const Word &rhs) {
		Sentence result;
		return plus(result, lhs, rhs);
	}

	Sentence operator-(const Word &lhs, const Word &rhs) {
		Sentence result;
		return plus(result, lhs, rhs * (-1));
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

	Sentence &div(Sentence &quotient, Sentence &remainder, const Word &lhs, const Word &rhs) {
		if (rhs.isZero()) return quotient; // ERR
		if (lhs.isZero()) return quotient; // Nothing happened as function definition
		if (lhs.root == rhs.root) {
			return plus(quotient, Word{
				.coef = lhs.coef / rhs.coef,
				.root = lhs.root,
				.power = lhs.power - rhs.power,
			});
		}
		// expands two and divide two resulting sentences
		Sentence ls, rs;
		expand(ls, lhs);
		expand(rs, rhs);
		return div(quotient, remainder, ls, rs);
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