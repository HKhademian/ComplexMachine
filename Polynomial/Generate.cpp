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

}