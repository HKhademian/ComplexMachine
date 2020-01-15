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
		//if (rhs.size() == 1) return stream << rhs[0];
		if (rhs.size() != 1)stream << "(";
		bool first = true;
		for (auto &word:rhs) {
			if (!first) {
				stream << SPC;
			}
			if (word.isNeg()) {
				stream << "-";
			} else if (!first) {
				stream << "+";
			}
			if (!first && !word.isConstant()) {
				stream << SPC;
			}
			first = false;
			print(stream, word, false);
		}
		if (rhs.size() != 1)stream << ")";
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

	Sentence operator-(const Sentence &lhs, const Sentence &rhs) {
		Sentence result;
		return minus(result, lhs, rhs);
	}

	Sentence operator-(const Sentence &lhs, const Word &rhs) {
		Sentence result;
		plus(result, lhs);
		return minus(result, rhs);
	}

	Sentence &operator-=(Sentence &lhs, const Word &rhs) {
		return minus(lhs, rhs);
	}

	Sentence &operator-=(Sentence &lhs, const Sentence &rhs) {
		return minus(lhs, rhs);
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

	Sentence operator*(const Sentence &lhs, const Word &rhs) {
		Sentence result;
		return mul(result, lhs, Sentence(rhs));
	}

	Sentence operator*(const Word &lhs, const Sentence &rhs) {
		return rhs * lhs;
	}

	Sentence &operator*=(Sentence &lhs, const Word &rhs) {
		Sentence result;
		mul(result, lhs, Sentence(rhs));
		lhs.clear();
		lhs += result;
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

	Sentence &plus(Sentence &result, const Sentence &lhs, const Sentence &rhs) {
		expand(result, lhs);
		expand(result, rhs);
		return result;
	}

	Sentence &minus(Sentence &result, const Word &rhs) {
		return plus(result, rhs * (-1));
	}

	Sentence &minus(Sentence &result, const Sentence &rhs) {
		return plus(result, rhs * (-1));
	}

	Sentence &minus(Sentence &result, const Sentence &lhs, const Sentence &rhs) {
		return plus(result, lhs, rhs * (-1));
	}

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
		// quotient.clear();
		// remainder.clear();
		if (lhs.empty() || rhs.empty()) return quotient; // div by/on 0

		Sentence l, r;
		expand(l, lhs);
		expand(r, rhs);

		while (!l.empty()) {
			const auto &lw = l.back(), rw = r.back();

			if (rw.power > lw.power) { // cannot divide
				remainder += l;
				l.clear();
				continue;
			}

			const Word part{
				.coef = lw.coef / rw.coef,
				.root = 0,
				.power = lw.power - rw.power,
			};
			quotient += part;

			const Sentence extra = r * Sentence(part);
			l -= extra;
		}

		return quotient;
	}


	Sentence &laurent(Sentence &result, const Sentence &lhs, const Sentence &rhs, const double &root, const unsigned int count) {
		// result.clear();
		if (lhs.empty() || rhs.empty())return result; // div by/on 0
		/*
		 * T=Z+root so Z=T-root
		 * we first change domain to T and expand words
		 * then calculates laurent around zero of T
		 * then backs to Z domain
		 */
		Sentence lT, rT;

		//std::cout << "LHS:" << std::endl << lhs << std::endl << expand(lT, lhs) << std::endl;
		//lT.clear();
		for (auto word:lhs) { // move RHS to t domain
			word.root -= root;
			expand(lT, word);
		}
		//std::cout << lT << std::endl;
		//Sentence lZ;
		//for (auto word:lT) { // move back LHS to Z domain
		//	word.root += root;
		//	plus(lZ, word);
		//}
		//std::cout << lZ << std::endl;

		//std::cout << "RHS:" << std::endl << rhs << std::endl << expand(rT, rhs) << std::endl;
		//rT.clear();
		for (auto word:rhs) { // move RHS to t domain
			word.root -= root;
			expand(rT, word);
		}
		//std::cout << rT << std::endl;
		//Sentence rZ;
		//for (auto word:rT) { // move back RHS to Z domain
		//	word.root += root;
		//	plus(rZ, word);
		//}
		//std::cout << rZ << std::endl;

		// here lT and rT are around their zero
		for (int i = 0; i < count; i++) {
			Word part{
				.coef = lT[0].coef / rT[0].coef,
				.root = 0,
				.power = lT[0].power - rT[0].power,
			};

			Sentence extra = rT * Sentence(part);
			lT -= extra;

			part.root -= root; // T domain to Z
			result += part;
		}
		return result;
	}

}
