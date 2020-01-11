#ifndef BASH_H
#define BASH_H

namespace bash {

	void cmdStart(int &lineNumber, const Computer::Memory &memory);

	void cmdHelp(int &lineNumber, const Computer::Memory &memory);

	void cmdListCommands(int &lineNumber, const Computer::Memory &memory);

	void cmdExamples(int &lineNumber, Computer::Memory &memory);

	void cmdClearMemory(int &lineNumber, Computer::Memory &memory);

	void cmdListMemory(int &lineNumber, const Computer::Memory &memory);

	void cmdClearScreen(int &lineNumber, const Computer::Memory &memory);

	void cmdPoly(int &lineNumber, const Computer::Memory &memory);

	void loop(Computer::Memory &memory);

}
#endif
