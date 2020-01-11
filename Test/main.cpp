#include <iostream>
#include "../Polynomial/Polynomial.h"

using namespace std;
using namespace poly;

int main() {
	int i = 0;
//	Sentence test, test1, test2;
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
	Word w3{.coef=3, .root=5, .power=4};
	{
		cout << "w1 = " << w1 << endl;
		cout << "w2 = " << w2 << endl;
		cout << "w3 = " << w3 << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		cout << "4 = " << (4 * Word::ONE) << endl;
		cout << "5Z = " << (5 * Word::Z) << endl;
		cout << "3Z^2 + 4 = " << (3 * Word::Z2 + (4 * Word::ONE)) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		cout << "w1+w2=      " << (w1 + w2) << endl;
		cout << "w2+w3=      " << (w2 + w3) << endl;
		cout << "w1+w2+w3=   " << (w1 + w2 + w3) << endl;
		cout << "(w1+w2)+w3= " << ((w1 + w2) + w3) << endl;
		cout << "(w2+w3)+w1= " << ((w2 + w3) + w1) << endl;
		cout << "w1+(w2+w3)= " << (w1 + (w2 + w3)) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		cout << "(z+1)(z+2)= " << (Word{.coef=1, .root=1, .power=1} * Word{.coef=1, .root=2, .power=1}) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		cout << "w1*w2= " << (w1 * w2) << endl;
		cout << "2*w1*w2= " << (2 * w1 * w2) << endl;
		cout << "w1*w2*2= " << (w1 * w2 * 2) << endl;
		cout << "w2*w3= " << (w2 * w3) << endl;
		cout << "w1*1= " << (w1 * 1) << endl;
		cout << "5*w1= " << (5 * w1) << endl;
		cout << "w1*0= " << (w1 * 0) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		cout << "w1/w2= " << (w1 / w2) << endl;
		cout << "w2/w3= " << (w2 / w3) << endl;
		cout << "w3/w2= " << (w3 / w2) << endl;
		cout << "w3/1= " << (w3 / 1) << endl;
		cout << "w3/2= " << (w3 / 2) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		Sentence res = Word{.coef=1, .root=2, .power=1} * Word{.coef=2, .root=3, .power=1};
		cout << "(z+2)*2*(z+3)= " << res << endl;
		cout << "res*=2; res=   " << (res *= 2) << endl;
		cout << "res+=1; res=   " << (res += Word::ONE) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		cout << "(z+2)*(2*(z+3))= " << (Word{.coef=1, .root=2, .power=1} * Word{.coef=2, .root=3, .power=1}) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;

		cout << "(w1)+(w2)= " << (Sentence(w1) + Sentence(w2)) << endl;

		Sentence res, res2;
		expand(res, w2);
		expand(res, w1);
		compact(res2, res);
		cout << "w1+w2= " << res << endl;
		cout << "w1+w2= " << res2 << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		auto around = 1, count = 10;
		Sentence s1(Word::ONE);
		Sentence s2(Word::Z + 1 * Word::ONE);
		Sentence result;
		cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		auto around = 0, count = 10;
		Sentence s1(Word::ONE);
		Sentence s2(-1 * Word::Z + 1 * Word::ONE);
		Sentence result;
		cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		auto around = 0, count = 10;
		Sentence s1(Word::Z);
		Sentence s2(-1 * Word::Z + 1 * Word::ONE);
		Sentence result;
		cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		auto around = 0, count = 10;
		Sentence s1(Word::ONE);
		Sentence s2(Word::Z + 1 * Word::ONE);
		Sentence result;
		cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		auto around = 0, count = 10;
		Sentence s1(Word::ONE);
		Sentence s2(Word::Z - 1 * Word::ONE);
		Sentence result;
		cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		auto around = 1, count = 10;
		Sentence s1(Word::ONE);
		Sentence s2(Word::Z);
		Sentence result;
		cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		auto around = 2, count = 10;
		Sentence s1(Word::ONE);
		Sentence s2(Word::Z + 1 * Word::ONE);
		Sentence result;
		cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
	}
	{
		cout << endl << "Test #" << ++i << endl;
		auto around = 1, count = 10;
		Sentence s1(5 * Word::Z2 + 2 * Word::Z + 3 * Word::ONE);
		Sentence s2(2 * Word::Z2 + 4 * Word::Z + 0 * Word::ONE);
		Sentence result;
		cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
	}
	return 0;
}
