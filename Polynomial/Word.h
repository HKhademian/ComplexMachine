#ifndef POLYNOMIAL_WORD_H
#define POLYNOMIAL_WORD_H

#include <iostream>

namespace poly {
	struct Sentence;

/** each Word is coef*(Z+root)^power */
	struct Word {
		static const Word ZERO, ONE, Z, Z2;
		double coef = 0.0;
		double root = 0.0; // TODO: use Complex
		long long power = 0; // TODO: support negative powers

		[[nodiscard]] bool isConstant() const { return power == 0; }

		[[nodiscard]] bool isZero() const { return coef == 0; }

		[[nodiscard]] bool isFirst() const { return coef != 0 && power == 1; }

		[[nodiscard]] bool isNeg() const { return coef < 0; }

		/** pretty print word to given ostream */
		friend std::ostream &print(std::ostream &stream, const Word &me, bool sign);

		/** pretty print word to given ostream */
		friend std::ostream &operator<<(std::ostream &stream, const Word &me);

		/** add two words and returns a sentence contains result */
		friend Sentence operator+(const Word &lhs, const Word &rhs);

		friend Sentence operator-(const Word &lhs, const Word &rhs);

		/** multiplies a coef into word and returns new word */
		friend Word operator*(const Word &lhs, const double &rhs);

		/** multiplies a coef into word and returns new word */
		friend Word operator*(const double &lhs, const Word &rhs);

		/** multiplies a coef into word and save in it */
		friend Word &operator*=(Word &lhs, const double &rhs);

		/** multiplies two words and returns a sentence as result */
		friend Sentence operator*(const Word &lhs, const Word &rhs);

		/** divide a word by coef and returns new word */
		friend Word operator/(const Word &lhs, const double &rhs);

		/** divide a word by coef and save in it */
		friend Word &operator/=(Word &lhs, const double &rhs);

		/** divide two words and returns quotient as new */
		friend Sentence operator/(const Word &lhs, const Word &rhs);

		/** divide two words and returns remainder as new */
		friend Sentence operator%(const Word &lhs, const Word &rhs);

		/** expands a word by pascal series in sentence */
		friend Sentence &expand(Sentence &result, const Word &me);

		/** adds two words and INSERT result in result */
		friend Sentence &plus(Sentence &result, const Word &lhs, const Word &rhs);

		/** subtracts two words and INSERT result in result */
		friend Sentence &minus(Sentence &result, const Word &lhs, const Word &rhs);

		/** multiplies two words and INSERT result in result */
		friend Sentence &mul(Sentence &result, const Word &lhs, const Word &rhs);

		/** divides two words and INSERT result into quotient and remainder also returns quotient */
		friend Sentence &div(Sentence &quotient, Sentence &remainder, const Word &lhs, const Word &rhs);

	};

}
#endif
