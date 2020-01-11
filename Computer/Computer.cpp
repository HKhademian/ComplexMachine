#include <cstdio>
#include <cstring>
#include <sstream>
#include <cmath>
#include "Computer.h"
#include "Memory.h"
#include "../Complex/utils.h"
#include "../Complex/ComplexNum.h"
#include "../Complex/ComplexFunction.h"

using namespace Complex;
namespace Computer {
	struct need_natural : public std::exception {
	};

	ComplexNum err(const char *msg, unsigned int start, unsigned int end) {
		std::stringstream buffer;
		buffer << "{error: " << msg << " in [" << start << "," << end << "]}";
		throw std::invalid_argument(buffer.str());
	}

	ComplexNum calc(const char *eql, int start, int end, Memory &memory, const ComplexNum &natural) {
		try {
			return calc(eql, start, end, memory);
		} catch (need_natural &e) {
			return natural;
		}
	}

	ComplexNum calc(const char *eql, int start, int end, Memory &memory) {
		const auto len = trim(eql, start, end);
		if (len <= 0) {
			throw need_natural();
		}

		int depth = 0, startDepth = -1, endDepth = -1, opIndex = -1, opRank = 0;
		for (auto i = start; i <= end && eql[i]; i++) {
			const char ch = eql[i];
			const char chl = i <= 0 ? '0' : eql[i - 1];
			const char chr = i >= end ? '0' : eql[i + 1];

			if (ch == '(') {
				if (depth == 0) {
					startDepth = i;
				}
				depth++;
				continue;
			}
			if (ch == ')') {
				depth--;
				if (depth < 0) {
					return err("extra close paran", start, end);
				}
				if (depth == 0) {
					endDepth = i;
				}
			}
			if (depth != 0) {
				continue;
			}

			int rank;
			/* we use recursive so higher ranks (less priority) and right most one must calculated first */

			rank = 1;
			if ((ch == '*' || ch == '/' || ch == '%') && chl != '=') { // Multiplicative
				if (opIndex < start || opRank <= rank) {
					opIndex = i;
					opRank = rank;
				}
				continue;
			}

			rank = 2;
			if ((ch == '^') && chl != '=') { // Power
				if (opIndex < start || opRank <= rank) {
					opIndex = i;
					opRank = rank;
				}
				continue;
			}

			rank = 3;
			if ((ch == '+' || ch == '-') && chl != '=') { // Additive
				if (opIndex < start || opRank <= rank) {
					opIndex = i;
					opRank = rank;
				}
				continue;
			}

			rank = 4;
			if (ch == '=') { // Assignment (=, +=, -=, *=, /=, ^=, %=)
				if (opIndex < start || opRank <= rank) {
					opIndex = i;
					opRank = rank;
				}
				continue;
			}
		}

		if (depth != 0) {
			return err("few close paran", start, end);
		}

		if (opIndex >= start && opIndex <= end) {
			const char op = eql[opIndex];
			const char opl = opIndex <= 0 ? '0' : eql[opIndex - 1];
			const char opr = opIndex >= end ? '0' : eql[opIndex + 1];

			if (op == '=') {
				bool hasOpL = (
						opl == '+' || opl == '-' || opl == '*' || opl == '/' || opl == '^' || opl == '%'
						// || opl=='!'|| opl=='='|| opl=='<'|| opl=='>' //compare
				);

				//auto memI = selectMem(eql, start, opIndex - (hasOpL ? 2 : 1), memory);
				ComplexNum mem;
				if (!memory.get(eql, start, opIndex - (hasOpL ? 2 : 1), mem)) {
					return err("wrong mem", start, end);
				}

				const auto rhs = calc(eql, opIndex + 1, end, memory);
				if (!hasOpL) {
					mem = rhs;
				} else {
					if (opl == '+') {
						mem = mem + rhs;
					} else if (opl == '-') {
						mem = mem - rhs;
					} else if (opl == '*') {
						mem = mem * rhs;
					} else if (opl == '/') {
						mem = mem / rhs;
					} else if (opl == '^') {
						mem = mem ^ rhs;
					} else if (opl == '%') {
						mem = mem % rhs;
					}
				}
				memory.set(eql, start, opIndex - (hasOpL ? 2 : 1), mem);
				return mem;
			}


			if (op == '/') {
				const auto lhs = calc(eql, start, opIndex - 1, memory);
				const auto rhs = calc(eql, opIndex + 1, end, memory);
				if (rhs.isZero()) {
					return err("div by 0", start, end);
				}
				return lhs / rhs;
			}

			if (op == '*') {
				const auto lhs = calc(eql, start, opIndex - 1, memory);
				const auto rhs = calc(eql, opIndex + 1, end, memory);
				return lhs * rhs;
			}

			if (op == '^') {
				const auto lhs = calc(eql, start, opIndex - 1, memory);
				const auto rhs = calc(eql, opIndex + 1, end, memory);
				if (lhs.isZero() && rhs.isZero()) {
					return err("0^0 is not possible", start, end);
				}
				return pow(lhs, rhs);
			}

			if (op == '+') {
				const auto lhs = calc(eql, start, opIndex - 1, memory, C0);
				const auto rhs = calc(eql, opIndex + 1, end, memory);
				return lhs + rhs;
			}

			if (op == '-') {
				const auto lhs = calc(eql, start, opIndex - 1, memory, C0);
				const auto rhs = calc(eql, opIndex + 1, end, memory);
				return lhs - rhs;
			}
		}

		if (startDepth >= start) {
			const ComplexFun1 func1 = selectFunc1(eql, start, startDepth - 1);
			if (func1 == nullptr && startDepth != start) {
				return err("wrong function", start, end);
			}
			if (func1 != nullptr && endDepth - startDepth <= 1) {
				return err("wrong function parameter", start, end);
			}
			const auto mhs = calc(eql, startDepth + 1, endDepth - 1, memory);
			if (func1 == nullptr) {
				return mhs;
			}
			const auto res = (*func1)(mhs);
			return res;
		}

		ComplexNum base = C1;
		if (memory.get(eql, start, end, base)) {// memory
			return base;
		}
		if (len >= 1 && strncasecmp((eql + end + 1) - 1, "e", 1) == 0) {
			base = cart(M_E, 0);
			end -= 1;
		} else if (len >= 3 && strncasecmp((eql + end + 1) - 3, "pi2", 3) == 0) {
			base = cart(M_PI_2, 0);
			end -= 3;
		} else if (len >= 3 && strncasecmp((eql + end + 1) - 3, "pi4", 3) == 0) {
			base = cart(M_PI_4, 0);
			end -= 3;
		} else if (len >= 2 && strncasecmp((eql + end + 1) - 2, "pi", 2) == 0) {
			base = cart(M_PI, 0);
			end -= 2;
		} else if (len >= 3 && strncasecmp((eql + end + 1) - 3, "ln2", 3) == 0) {
			base = cart(M_LN2, 0);
			end -= 3;
		} else if (len >= 4 && strncasecmp((eql + end + 1) - 4, "ln10", 4) == 0) {
			base = cart(M_LN10, 0);
			end -= 4;
		} else if (len >= 5 && strncasecmp((eql + end + 1) - 5, "sqrt2", 5) == 0) {
			base = cart(M_SQRT2, 0);
			end -= 5;
		} else if (len >= 1 && strncasecmp((eql + end + 1) - 1, "i", 1) == 0) {
			base = eql[end] == 'i' ? CI : CIe;
			end -= 1;
		}

		if (trim(eql, start, end) <= 0) {
			return base;
		}

		char *endptr = nullptr;
		const auto value = strtod(eql + start, &endptr);
		if (endptr != eql + end + 1) {
			return err("bad constant data", start, end);
		}
		return base * value;
	}

	ComplexNum calc(const char *eql, Memory &memory) {
		return calc(eql, 0, (int) strlen(eql) - 1, memory);
	}
}
