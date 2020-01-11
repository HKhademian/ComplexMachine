//#include <algorithm>
#include <iostream>
#include "../Complex/utils.h"
#include "Polynomial.h"
#include "Sentence.h"

namespace poly {
	Sentence::Sentence(const Word &word) {
		push_back(word);
	}

	const std::vector<Word> &Sentence::words() const {
		return self;
	}

	std::ostream &operator<<(std::ostream &stream, const Sentence &rhs) {
		if (rhs.size() == 1) return stream << rhs[0];
		stream << "(" SPC;
		bool first = true;
		for (auto &word:rhs) {
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

	Sentence &operator+=(Sentence &lhs, const Sentence &rhs) {
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

	Sentence operator/(const Sentence &lhs, const Sentence &rhs) {
		Sentence quotient, remainder;
		div(quotient, remainder, lhs, rhs);
		return quotient;
	}

	Sentence operator%(const Sentence &lhs, const Sentence &rhs) {
		Sentence quotient, remainder;
		div(quotient, remainder, lhs, rhs);
		return remainder;
	}

	Sentence &plus(Sentence &result, const Word &rhs) {
		for (int i = 0; i < result.size(); i++) {
			auto &word = result[i];
			if (word.power == rhs.power && word.root == rhs.root) {
				word.coef += rhs.coef;
				if (word.isZero() && result.size() > 1) { // remove if it is zero and its not empty
					result.erase(result.begin() + i);
				}
				return result;
			}
		}

		//remove zeros
		for (int i = 0; i < result.size(); i++) {
			auto &word = result[i];
			if (word.isZero()) {
				result.erase(result.begin() + i--);
			}
		}

		//search for first greater power and add before it
		for (int i = 0; i < result.size(); i++) {
			auto &word = result[i];
			if (rhs.power < word.power || (rhs.power == word.power && rhs.root < word.root)) {
				result.insert(result.begin() + i, rhs);
				return result;
			}
		}

		// add as last word
		result.push_back(rhs);
		return result;
	}

	Sentence &plus(Sentence &result, const Sentence &rhs) {
		for (auto &word:rhs) {
			plus(result, word);
		}
		return result;
	}

	/*Sentence &sort(Sentence &result, const Sentence &rhs) {
		result.clear();
		std::vector<int> indexes;
		indexes.reserve(rhs.size());
		for (int i = 0; i < rhs.size(); i++) indexes.push_back(i);
		std::sort(indexes.begin(), indexes.end(), [rhs](int l, int r) {
			return rhs[l].power < rhs[r].power || ((rhs[l].power == rhs[r].power) && rhs[l].root < rhs[r].root);
		});
		for (auto index:indexes) {
			auto &word = rhs[index];
			if (word.isZero()) continue;
			result.push_back(word);
		}
		return result;
	}*/

	Sentence &expand(Sentence &result, const Sentence &rhs) {
		for (const auto &word:rhs) {
			expand(result, word);
		}
		return result;
	}

	Sentence &compact(Sentence &result, const Sentence &rhs) {
		for (const auto &word:rhs) {
			plus(result, word);
		}
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

	Sentence &div(Sentence &quotient, Sentence &remainder, const Sentence &lhs, const Sentence &rhs) {
		// TODO: implement
		return quotient;
	}

}
