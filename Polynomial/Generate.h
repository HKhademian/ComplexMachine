#ifndef POLYNOMIAL_GENERATE_H
#define POLYNOMIAL_GENERATE_H

namespace poly {
	struct Word;
	struct Sentence;

	Sentence &generateExp(Sentence &result, const Word &variable, int count);

	Sentence &generateCos(Sentence &result, const Word &variable, int count);

	Sentence &generateSin(Sentence &result, const Word &variable, int count);

	/** creates its taylor/laurent series (count words) around this new root
	 * lhs is numerator and rhs is denominator of a fraction
	 * it returns possible residue value,
	 * if it can't find it in maxCount generated words of series or any other errors, it return 64bit 0 instead.
	 */
	double generateLaurent(Sentence &result, const Sentence &lhs, const Sentence &rhs, const double &root, unsigned int count);
}

#endif
