#include "../Complex/utils.h"
#include "Polynomial.h"

namespace poly {
	Sentence &generateExp(Sentence &result, const Word &variable, int count) {
		for (int i = 0; i < count; i++) {
			const auto coef = 1.0 / (factorial(i) * variable.coef);
			const auto power = -i * variable.power;
			const auto word = Word{
				.coef = coef,
				.root = variable.root,
				.power = power,
			};
			result += word;
		}
		return result;
	}

	Sentence &generateCos(Sentence &result, const Word &variable, int count) {
		for (int i = 0; i < count; i++) {
			const auto coef = (i % 2 ? -1.0 : 1.0) / (factorial(2 * i) * variable.coef);
			const auto power = -(2 * i) * variable.power;
			const auto word = Word{
				.coef = coef,
				.root = variable.root,
				.power = power,
			};
			result += word;
		}
		return result;
	}

	Sentence &generateSin(Sentence &result, const Word &variable, int count) {
		for (int i = 0; i < count; i++) {
			const auto coef = (i % 2 ? -1.0 : 1.0) / (factorial(2 * i + 1) * variable.coef);
			const auto power = -(2 * i + 1) * variable.power;
			const auto word = Word{
				.coef = coef,
				.root = variable.root,
				.power = power,
			};
			result += word;
		}
		return result;
	}

	double generateLaurent(Sentence &result, const Sentence &lhs, const Sentence &rhs, const double &root, const unsigned int count) {
		double res;
		*((long long *) ((void *) (&res))) = 0; // error value is 64bit 0

		if (lhs.words().empty() || rhs.words().empty())return res; // div by/on 0
		/*
		 * T=Z+root so Z=T-root
		 * we first change domain to T and expand words
		 * then calculates laurent around zero of T
		 * then backs to Z domain
		 */
		Sentence lT, rT;

		for (auto word:lhs.words()) { // move RHS to t domain
			word.root -= root;
			expand(lT, word);
		}
		for (auto word:rhs.words()) { // move RHS to t domain
			word.root -= root;
			expand(rT, word);
		}

		// here lT and rT are around their zero
		for (int i = 0; i < count; i++) {
			Word part{
				.coef = lT.words()[0].coef / rT.words()[0].coef,
				.root = 0,
				.power = lT.words()[0].power - rT.words()[0].power,
			};

			if (part.power == -1) {
				res = part.coef; //found, so coef is residue
			}

			Sentence extra = rT * Sentence(part);
			lT -= extra;

			part.root -= root; // T domain to Z
			result += part;
		}

		return res;
	}
}