#include <iostream>
#include "../Polynomial/Poly.h"

using namespace std;
using namespace poly;

int main() {
	Sentence test, test1, test2;
//	Word w1{.coef=5, .root=2, .power=3};
//	Word w{.coef=2, .root=3, .power=2};
//	cout << w << endl;
//	expand(test, w);
//	cout << test << endl;
//
//	cout << endl
//			 << Word{.coef=0, .root=0, .power=1} << endl // zero
//			 << Word{.coef=0, .root=1, .power=1} << endl // also zero
//			 << Word{.coef=0, .root=1, .power=0} << endl // also zero
//			 << Word{.coef=5, .root=0, .power=0} << endl // const 5
//			 << Word{.coef=5, .root=1, .power=0} << endl // also const 5
//			 << Word{.coef=1, .root=0, .power=1} << endl
//			 << Word{.coef=1, .root=0, .power=2} << endl
//			 << Word{.coef=1, .root=2, .power=1} << endl
//			 << Word{.coef=1, .root=2, .power=2} << endl
//			 << Word{.coef=5, .root=2, .power=2} << endl
//			 << Word{.coef=5, .root=2, .power=1} << endl
//			 << Word{.coef=5, .root=0, .power=1} << endl
//			 << Word{.coef=5, .root=0, .power=2} << endl
//			 << endl;

	Word w1{.coef=1, .root=1, .power=3};
	Word w2{.coef=2, .root=5, .power=2};
	{
		test.clear();
		test1.clear();
		expand(test, w2);
		expand(test, w1);
		compact(test1, test);
		cout << w1 << " + " << w2 << " = " << test << endl;
		cout << w1 << " + " << w2 << " = " << test1 << endl;
	}
	{
		test2.clear();
		poly::plus(test2, Sentence {w1}, Sentence {w2});
		cout << w1 << " + " << w2 << " = " << test2 << endl;

	}
	return 0;
}
