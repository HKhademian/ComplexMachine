#include <cmath>
#include <algorithm>
#include <iostream>
#include "Poly.h"

namespace poly {

	std::ostream &operator<<(std::ostream &stream, const Sentence &me) {
		if (me.size() == 1) return stream << me[0];
		stream << "(" SPC;
		bool first = true;
		for (auto &word:me) {
			if (!first) stream << "+" SPC;
			first = false;
			stream << word << SPC;
		}
		stream << ")";
		return stream;
	}

	Sentence operator+(const Sentence &lhs, const Sentence &rhs) {
		Sentence result;
		return plus(result, lhs, rhs);
	}

	Sentence operator+(const Sentence &lhs, const Word &rhs) {
		Sentence result;
		plus(result, lhs);
		return plus(result, rhs);
	}

	Sentence operator+(const Word &rhs, const Sentence &lhs) {
		return lhs + rhs;
	}

	Sentence &operator+=(Sentence &lhs, const Word &rhs) {
		return plus(lhs, rhs);
	}

	Sentence operator*(const Sentence &lhs, const double &rhs) {
		Sentence result;
		for (const auto &word:lhs) {
			plus(result, word * rhs);
		}
		return result;
	}

	Sentence &operator*=(Sentence &lhs, const double &rhs) {
		for (auto &word:lhs) {
			word *= rhs;
		}
		return lhs;
	}

	Sentence operator*(const Sentence &lhs, const Sentence &rhs) {
		Sentence result;
		return mul(result, lhs, rhs);
	}

	Sentence &plus(Sentence &result, const Word &me) {
		for (auto &word:result) {
			if (word.power == me.power && word.root == me.root) {
				word.coef += me.coef;
				return result;
			}
		}
		// find zero to  replace
		for (auto &word:result) {
			if (word.isZero()) {
				word.coef = me.coef;
				word.root = me.root;
				word.power = me.power;
				return result;
			}
		}
		// add new word
		result.push_back(me);
		return result;
	}

	Sentence &plus(Sentence &result, const Sentence &me) {
		for (auto &word:me) {
			plus(result, word);
		}
		return result;
	}

	Sentence &sort(Sentence &result, const Sentence &me) {
		result.clear();
		std::vector<int> indexes;
		indexes.reserve(me.size());
		for (int i = 0; i < me.size(); i++) indexes.push_back(i);
		std::sort(indexes.begin(), indexes.end(), [me](int l, int r) {
			return me[l].power < me[r].power || ((me[l].power == me[r].power) && me[l].root < me[r].root);
		});
		for (auto index:indexes) {
			auto &word = me[index];
			if (word.isZero()) continue;
			result.push_back(word);
		}
		return result;
	}

	Sentence &expand(Sentence &result, const Sentence &me) {
		for (const auto &word:me) {
			expand(result, word);
		}
		return result;
	}

	Sentence &compact(Sentence &result, const Sentence &me) {
		Sentence mem;
		for (const auto &word:me) {
			plus(mem, word);
		}
		sort(result, mem);
		return result;
	}

	Sentence &plus(Sentence &result, const Sentence &lhs, const Sentence &rhs) {
		expand(result, lhs);
		expand(result, rhs);
		return result;
	}

	Sentence &mul(Sentence &result, const Sentence &lhs, const Sentence &rhs) {
		for (const auto &lword: lhs) {
			for (const auto &rword: rhs) {
				auto res = lword * rword;
				plus(result, res);
			}
		}
		return result;
	}
}
