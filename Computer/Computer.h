#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "../Complex/ComplexNum.h"
#include "Memory.h"

using namespace Complex;

namespace Computer {
	ComplexNum calc(const char *eql, Memory &memory);

	ComplexNum calc(const char *eql, int start, int end, Memory &memory);

	ComplexNum calc(const char *eql, int start, int end, Memory &memory, const ComplexNum &natural);

// ComplexNum calc(const char *eql, int start, int end, const ComplexNum &natural, ComplexNum *memory);
}

#endif
