#ifndef POLYNOMIAL_GENERATE_H
#define POLYNOMIAL_GENERATE_H

namespace poly {
	struct Word;
	struct Sentence;

	Sentence &generateExp(Sentence &result, const Word &variable, int count);

	Sentence &generateCos(Sentence &result, const Word &variable, int count);

	Sentence &generateSin(Sentence &result, const Word &variable, int count);
}

#endif
