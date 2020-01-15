#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include "../Complex/ComplexNum.h"
#include "../Computer/Computer.h"
#include "../Polynomial/Polynomial.h"

using namespace std;

namespace bash {
	void cmdStart(int &lineNumber, const Computer::Memory &memory) {
		lineNumber = 0;
		cout << "* Welcome to ComplexBash v0.01" << endl
				 << "* type \\h or `help` to show help" << endl
				 //<< "* type \\e or `examples` to show examples" << endl
				 //<< "* type \\c or `clear` to clear memory" << endl
				 //<< "* type \\l or `list` to list memory" << endl
				 << "* type \\x or `exit` to exit ComplexBash" << endl
				 << "* Please enter your commands" << endl;
		cout.flush();
	}

	void cmdHelp(int &lineNumber, const Computer::Memory &memory) {
		cout
			<< "* Here you can input any common ComplexNum world equation" << endl
			<< "* type `\\h` or `help` to show help" << endl
			<< "* type `\\x` or `exit` to exit ComplexBash" << endl
			<< "* type `\\c` or `cmd` to list commands" << endl
			<< "* type `cls` to clear screen" << endl
			<< "* type `clear` to clear memory" << endl
			<< "* type `list` to list memory" << endl
			<< "* type `poly` and `laurent` to launch to Polynomial APP" << endl
			<< "* type `examples` to show examples" << endl
			<< "* this program supports both cartesian and euler computation" << endl
			<< "* Also you can memorize your data in 'x[0-9], y[0-9], z[0-9], w[0-9]" << endl
			<< "* (((USE PARENTHESIS AS YOU CAN)))" << endl
			<< "*" << endl
			<< "* Math OP: plus(+), minus(-), mul(*), div(/), power(^), mod(%)" << endl
			<< "* ComplexNum Func: cart( <comp> ), euler( <comp> ) to switch" << endl
			<< "* ComplexNum Func: arg( <cmplx> ), len( <cmplx> ), re( <cmplx> ), im( <cmplx> )" << endl
			<< "* ComplexNum Func: ln( <cmplx> ), exp( <cmplx> ), sqrt( <cmplx> ), pow2( <cmplx> )," << endl
			<< "* ComplexNum Func: cart( <cmplx> ), euler( <cmplx> )" << endl
			<< "* Tri Func: cos( <cmplx> ), cosh( <cmplx> ), acos( <cmplx> ), acosh( <cmplx> )," << endl
			<< "* Tri Func: sin( <cmplx> ), sinh( <cmplx> ), asin( <cmplx> ), asinh( <cmplx> )," << endl
			<< "* Tri Func: tan( <cmplx> ), tanh( <cmplx> ), atan( <cmplx> ), atanh( <cmplx> )," << endl
			<< "*" << endl
			<< "* Constants:" << endl
			<< "* i=cart(i)=0+1i" << endl
			<< "* I=euler(i)=1*exp(i.π/2)" << endl
			<< "* e=E=" << M_E << endl
			<< "* pi=π=" << M_PI << endl
			<< "* pi2=π/2=" << M_PI_2 << endl
			<< "* pi4=π/4=" << M_PI_4 << endl
			<< "* ln2=" << M_LN2 << endl
			<< "* ln10=" << M_LN10 << endl
			<< "* sqrt2=√2" << M_SQRT2 << endl
			<< endl;
	}

	void cmdListCommands(int &lineNumber, const Computer::Memory &memory) {
		// TODO: list commands
	}

	void cmdExamples(int &lineNumber, Computer::Memory &memory) {
		const static string examples[] = {
			"cart(i+1)",
			"euler(z2=5i)",
			"1 + 4*3 + 9",
			"1 + ((4*3) + 9",
			"1 + ) + 9",
			"z = 10+4i",
			"w = z+5",
			"y7 = cos(w)",
			"sinh((z5=z/y7)+6i)"
		};

		for (const auto &cmd : examples) {
			cout << "#) " << cmd << endl
					 << "#: " << Computer::calc(cmd.c_str(), memory) << endl
					 << "#" << endl;
		}
	}

	void cmdClearMemory(int &lineNumber, Computer::Memory &memory) {
		memory.clear();
	}

	void cmdListMemory(int &lineNumber, const Computer::Memory &memory) {
		const auto fields = {'z', 'y', 'x', 'w'};
		char name[5] = {0};
		ComplexNum mem;
		for (const auto field:fields) {
			cout << "#";
			for (int i = 0; i < 10; i++) {
				if (i % 5 == 0) {
					cout << endl << "# ";
				}
				sprintf(name, "%c%d", field, i);
				memory.get(name, 0, strlen(name) - 1, mem);
				stringstream buffer;
				buffer << mem;
				cout << setw(3) << right << name << "=";
				cout << setw(20) << left << buffer.str();
				cout << "   ";
			}
			cout << endl << "#";
		}
	}

	void cmdClearScreen(int &lineNumber, const Computer::Memory &memory) {
		cin.clear();
		cin.ignore(INT32_MAX, '\n');
		system("cls");
		cmdStart(lineNumber, memory);
	}

	void cmdPoly(int &lineNumber, const Computer::Memory &memory) {
		poly::appPoly();
		cmdClearScreen(lineNumber, memory);
	}

	void cmdPolyLaurent(int &lineNumber, const Computer::Memory &memory) {
		poly::appPolyLaurent();
		cmdClearScreen(lineNumber, memory);
	}

	void loop(Computer::Memory &memory) {
		char line[1000];
		int lineNumber = 0;
		cmdStart(lineNumber, memory);
		while (true) {
			cout << "\r" << ++lineNumber << ") ";
			cout.flush();
			fgets(line, 1000, stdin);
			printf("\r");
			if (strcasecmp(line, "\\x\n") == 0 || strcasecmp(line, "exit\n") == 0) {
				cout << "# See you soon" << endl;
				break;
			}
			if (strcasecmp(line, "\\h\n") == 0 || strcasecmp(line, "help\n") == 0) {
				cmdHelp(lineNumber, memory);
				cout << "# Show Help done" << endl;
				continue;
			}
			if (strcasecmp(line, "\\c\n") == 0 || strcasecmp(line, "cmd\n") == 0) {
				cmdHelp(lineNumber, memory);
				cout << "# List Commands done" << endl;
				continue;
			}
			if (strcasecmp(line, "examples\n") == 0) {
				cmdExamples(lineNumber, memory);
				cout << "# Show Examples done" << endl;
				continue;
			}
			if (strcasecmp(line, "cls\n") == 0) {
				cmdClearScreen(lineNumber, memory);
				continue;
			}
			if (strcasecmp(line, "poly\n") == 0) {
				cmdPoly(lineNumber, memory);
				continue;
			}
			if (strcasecmp(line, "laurent\n") == 0) {
				cmdPolyLaurent(lineNumber, memory);
				continue;
			}
			if (strcasecmp(line, "clear\n") == 0) {
				cmdClearMemory(lineNumber, memory);
				cout << "# Clear Memory done" << endl;
				continue;
			}
			if (strcasecmp(line, "list\n") == 0) {
				cmdListMemory(lineNumber, memory);
				cout << "# List Memory done" << endl;
				continue;
			}

			try {
				ComplexNum res = Computer::calc(line, memory);
				cout << lineNumber << ": " << res << endl;
			} catch (std::invalid_argument &err) {
				cout << lineNumber << ": ERR " << err.what() << endl;
			} catch (std::exception &err) {
				cout << lineNumber << ": ERR UNKNOWN" << endl;
			}
		}
	}
}