#include <cmath>
#include <algorithm>
#include "../Complex/utils.h"
#include "../Complex/ComplexNum.h"
#include "../Complex/ComplexFunction.h"
#include "Poly.h"

void appPoly() {
}

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

	Sentence &add(Sentence &result, const Word &me) {
		for (auto &word:result) {
			if (word.power == me.power && word.root == me.root) {
				word.coef += me.coef;
				return result;
			}
		}
		result.push_back(me);
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
			result.push_back(me[index]);
		}
		return result;
	}

	Sentence &expand(Sentence &result, const Word &me) {
		for (unsigned int i = 0; i <= me.power; i++) {
			auto choice = chooseI(i, me.power);
			double coef = me.coef * choice * std::pow(me.root, me.power - i);
			if (coef == 0)continue;
			add(result, Word{.coef=coef, .root = 0, .power=i});
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
			add(mem, word);
		}
		sort(result, mem);
		return result;
	}

	Sentence &plus(Sentence &result, const Sentence &lhs, const Sentence &rhs) {
		expand(result, lhs);
		expand(result, rhs);
		return result;
	}


}
