#ifndef POLY_H
#define POLY_H

#include "../Complex/utils.h"
#include <vector>

void appPoly();

namespace poly {
	// use "" or " " to remove/add space in poly printing
#define SPC ""

	/** each Word is coef*(Z+root)^power */
	struct Word {
		static const Word ZERO, ONE;
		double coef = 0.0;
		double root = 0.0; // TODO: use Complex
		unsigned int power = 0; // TODO: support negative powers

		[[nodiscard]] bool isConstant() const { return power == 0; }

		[[nodiscard]] bool isZero() const { return coef == 0; }

		[[nodiscard]] bool isFirst() const { return coef != 0 && power == 1; }
	};

	/** a sentence is a sum of some words */
	typedef std::vector<Word> Sentence;

	std::ostream &operator<<(std::ostream &stream, const Word &me);

	std::ostream &operator<<(std::ostream &stream, const Sentence &me);


	/// add a word to sentence without duplicate
	Sentence &add(Sentence &result, const Word &me);

	/// sort words by power
	Sentence &sort(Sentence &result, const Sentence &me);

	/// expands a word by pascal series in sentence
	Sentence &expand(Sentence &result, const Word &me);

	/// expands words of sentences in sentence
	Sentence &expand(Sentence &result, const Sentence &me);

	/** join redundant words (which only differs in coef) */
	Sentence &compact(Sentence &result, const Sentence &me);

	/** adds two sentences and insert into result (do not clear previous words) */
	Sentence &plus(Sentence &result, const Sentence &lhs, const Sentence &rhs);

	/** subtracts two sentences */
	Sentence minus(const Sentence &lhs, const Sentence &rhs);

	/** change root to new point */
	Sentence around(const Sentence &me, double around); // TODO: use Complex

	/** multiplies two sentences */
	Sentence mul(const Sentence &lhs, const Sentence &rhs);

	/** creates its taylor/laurent series */
	Sentence div(const Sentence &lhs, const Sentence &rhs, double around, int count);
}

#endif
