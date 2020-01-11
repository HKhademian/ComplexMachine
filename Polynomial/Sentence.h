#ifndef POLYNOMIAL_SENTENCE_H
#define POLYNOMIAL_SENTENCE_H

#include <vector>
#include <iostream>

namespace poly {
	struct Word;

	//typedef std::vector<Word> Sentence;

	/** a sentence is a sum of some words */
	struct Sentence : private std::vector<Word> {
		Sentence() = default;

		Sentence(Sentence const &) = default;

		explicit Sentence(const Word &word);

		[[nodiscard]] const std::vector<Word> &words() const;

		/*/ pretty print sequence to given ostream */
		friend std::ostream &operator<<(std::ostream &stream, const Sentence &rhs);

		/** adds two sentences and return new sentence */
		friend Sentence operator+(const Sentence &lhs, const Sentence &rhs);

		/** adds a word to LHS sentence and return new sentence */
		friend Sentence operator+(const Sentence &lhs, const Word &rhs);

		/** adds a word to LHS sentence and return new sentence */
		friend Sentence operator+(const Word &rhs, const Sentence &lhs);

		/** adds a word to LHS sentence and store in it */
		friend Sentence &operator+=(Sentence &lhs, const Word &rhs);

		/** adds two sentences and store in LHS */
		friend Sentence &operator+=(Sentence &lhs, const Sentence &rhs);

		/** multiplies a coef in sentence and return new */
		friend Sentence operator*(const Sentence &lhs, const double &rhs);

		/** multiplies a coef in sentence and store in it */
		friend Sentence &operator*=(Sentence &lhs, const double &rhs);

		/** multiplies a coef in sentence and return new */
		friend Sentence operator*(const Sentence &lhs, const Sentence &rhs);

		/** divides two sentences and returns quotient as new sentence */
		friend Sentence operator/(const Sentence &lhs, const Sentence &rhs);

		/** divides two sentences and returns remainder as new sentence */
		friend Sentence operator%(const Sentence &lhs, const Sentence &rhs);

		/** INSERT a word to result without duplicate, (previous data in result remains) */
		friend Sentence &plus(Sentence &result, const Word &rhs);

		/** INSERT a Sentence to result without duplicate, (previous data in result remains) */
		friend Sentence &plus(Sentence &result, const Sentence &rhs);

		// /// sort words by power and store in result
		// friend Sentence &sort(Sentence &result, const Sentence &rhs);

		/** expands words of sentences in result */
		friend Sentence &expand(Sentence &result, const Sentence &rhs);

		/** join redundant words (which only differs in coef) */
		friend Sentence &compact(Sentence &result, const Sentence &rhs);

		/** adds two sentences and insert into result (do not clear previous words) */
		friend Sentence &plus(Sentence &result, const Sentence &lhs, const Sentence &rhs);

		/** subtracts two sentences */
		friend Sentence &minus(Sentence &result, const Sentence &lhs, const Sentence &rhs);

		/** change root to new point */
		friend Sentence &around(Sentence &result, const Sentence &rhs, double around); // TODO: use Complex

		/** multiplies two sentences */
		friend Sentence &mul(Sentence &result, const Sentence &lhs, const Sentence &rhs);

		/** divides two sentences and INSERT result into quotient and remainder also returns quotient */
		friend Sentence &div(Sentence &quotient, Sentence &remainder, const Sentence &lhs, const Sentence &rhs);

			/** creates its taylor/laurent series */
		friend Sentence &series(Sentence &result, const Sentence &lhs, const Sentence &rhs, double around, int count);
	};


}
#endif
