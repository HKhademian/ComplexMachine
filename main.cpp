#include "Complex/ComplexNum.h"
#include "Computer/Memory.h"
#include "Bash.cpp"

using namespace std;
using namespace Complex;

int main() {
	Computer::FieldMemory mem;
	{
		const auto fields = {'z', 'y', 'x', 'w'};
		char name[5] = {0};
		for (const auto field: fields) {
			for (int i = 0; i < 10; i++) {
				sprintf(name, "%c%d", field, i);
				mem.set(name, 0, strlen(name), C0);
			}
		}
		mem.createNew = false;
	}
//	ComplexNum memory[4 * 10];
	Bash::loop(mem);
	return 0;
}
