#ifndef POLY_H
#define POLY_H

#include "../Complex/utils.h"
#include <vector>
#include <iostream>

void appPoly();

namespace poly {
	// use "" or " " to remove/insert space in poly printing
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
	//typedef std::vector<Word> Sentence;
	class Sentence : public std::vector<Word> {
	};


#if true  /* Word functions */

	/// pretty print word to given ostream
	std::ostream &operator<<(std::ostream &stream, const Word &me);

	/// add two words and returns a sentence contains result
	Sentence operator+(const Word &lhs, const Word &rhs);

	Sentence operator-(const Word &lhs, const Word &rhs);

	/// multiplies a coef into word and return new word
	Word operator*(const Word &lhs, const double &rhs);

	/// multiplies a coef into word and save in it
	Word &operator*=(Word &lhs, const double &rhs);

	/// multiplies two words and returns a sentence as result
	Sentence operator*(const Word &lhs, const Word &rhs);

	/// expands a word by pascal series in sentence
	Sentence &expand(Sentence &result, const Word &me);

	/// adds two words and INSERT result in result
	Sentence &plus(Sentence &result, const Word &lhs, const Word &rhs);

	/// subtracts two words and INSERT result in result
	Sentence &minus(Sentence &result, const Word &lhs, const Word &rhs);

	/// multiplies two words and INSERT result in result
	Sentence &mul(Sentence &result, const Word &lhs, const Word &rhs);

#endif

#if true  /* Sentence functions */

	/// pretty print sequence to given ostream
	std::ostream &operator<<(std::ostream &stream, const Sentence &me);

	/** adds two sentences and return new sentence */
	Sentence operator+(const Sentence &lhs, const Sentence &rhs);

	/** adds a word to LHS sentence and return new sentence */
	Sentence operator+(const Sentence &lhs, const Word &rhs);

	/** adds a word to LHS sentence and return new sentence */
	Sentence operator+(const Word &rhs, const Sentence &lhs);

	/** adds a word to LHS sentence and store in it */
	Sentence &operator+=(Sentence &lhs, const Word &rhs);

	/** adds two sentences and store in LHS */
	Sentence &operator+=(Sentence &lhs, const Sentence &rhs);

	/** multiplies a coef in sentence and return new */
	Sentence operator*(const Sentence &lhs, const double &rhs);

	/** multiplies a coef in sentence and store in it */
	Sentence &operator*=(Sentence &lhs, const double &rhs);

	/** multiplies a coef in sentence and return new */
	Sentence operator*(const Sentence &lhs, const Sentence &rhs);

	/// INSERT a word to result without duplicate, (previous data in result remains)
	Sentence &plus(Sentence &result, const Word &me);

	/// INSERT a Sentence to result without duplicate, (previous data in result remains)
	Sentence &plus(Sentence &result, const Sentence &me);

	/// sort words by power and store in result
	Sentence &sort(Sentence &result, const Sentence &me);

	/// expands words of sentences in result
	Sentence &expand(Sentence &result, const Sentence &me);

	/** join redundant words (which only differs in coef) */
	Sentence &compact(Sentence &result, const Sentence &me);

	/** adds two sentences and insert into result (do not clear previous words) */
	Sentence &plus(Sentence &result, const Sentence &lhs, const Sentence &rhs);

	/** subtracts two sentences */
	Sentence &minus(Sentence &result, const Sentence &lhs, const Sentence &rhs);

	/** change root to new point */
	Sentence &around(Sentence &result, const Sentence &me, double around); // TODO: use Complex

	/** multiplies two sentences */
	Sentence &mul(Sentence &result, const Sentence &lhs, const Sentence &rhs);

	/** creates its taylor/laurent series */
	Sentence &div(Sentence &result, const Sentence &lhs, const Sentence &rhs, double around, int count);

#endif

}

#endif
