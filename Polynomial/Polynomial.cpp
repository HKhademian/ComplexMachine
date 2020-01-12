#include <iostream>
#include "../Complex/utils.h"
#include "Polynomial.h"

using namespace std;

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

	void appPoly() {
		cerr << "Sorry in this limited time I cant implement Bash support to interact with Polynomial Api so feel free to enjoy some hard coded examples: " << endl;
		appPolyExample();
	}

	void appPolyExample() {
		cout << "POLYNOMIAL EXAMPLES: " << endl;
		cout << "here you see some example to test and see how this api works" << endl;
		cout << "A word is simply coef*(Z+root)^power" << endl;
		cout << "these three variables in a word has major impact on how data are calculated" << endl;
		cout << "some where it depends on POWER somewhere on its root" << endl;
		cout << "A Sentence is sum of some words (can have different powers,roots and coefs)" << endl;
		cout << "I also implement expand(WORD/SENTENCE) to expand single/multiple word by PASCAL series to a zero-root sum of words" << endl;
		cout << "this how, I can add or multiply in some operations" << endl;
		cout << "basic operation (add, subtract, multiply, divide) are works normally as you expect from Polynomials" << endl;
		cout << "there is a laurent function that use another method of dividend to generate taylor/laurent series of a Fraction" << endl;
		cout << "there is working TODO to calculate residual of these laurent series" << endl;
		cout << "also I implement generateXXX(BASE, count) to generate laurent series for known functions like exp, ..." << endl;
		cout << endl;

		int i = 0;
		Word w1{.coef=1, .root=1, .power=3};
		Word w2{.coef=2, .root=5, .power=2};
		Word w3{.coef=3, .root=5, .power=4};
		{
			cout << "w1 = " << w1 << endl;
			cout << "w2 = " << w2 << endl;
			cout << "w3 = " << w3 << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Words and Sentences)" << endl;
			cout << "4 = " << (4 * Word::ONE) << endl;
			cout << "5Z = " << (5 * Word::Z) << endl;
			cout << "3Z^2 + 4 = " << (3 * Word::Z2 + (4 * Word::ONE)) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Word Addition)" << endl;
			cout << "w1+w2=      " << (w1 + w2) << endl;
			cout << "w2+w3=      " << (w2 + w3) << endl;
			cout << "w1+w2+w3=   " << (w1 + w2 + w3) << endl;
			cout << "(w1+w2)+w3= " << ((w1 + w2) + w3) << endl;
			cout << "(w2+w3)+w1= " << ((w2 + w3) + w1) << endl;
			cout << "w1+(w2+w3)= " << (w1 + (w2 + w3)) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Sentence Addition)" << endl;
			Sentence res = Word{.coef=1, .root=2, .power=1} * Word{.coef=2, .root=3, .power=1};
			cout << "(z+2)*2*(z+3)= " << res << endl;
			cout << "res*=2; res=   " << (res *= 2) << endl;
			cout << "res+=1; res=   " << (res += Word::ONE) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Multiplication)" << endl;
			cout << "(z+1)(z+2)= " << (Word{.coef=1, .root=1, .power=1} * Word{.coef=1, .root=2, .power=1}) << endl;
			cout << "w1*w2= " << (w1 * w2) << endl;
			cout << "2*w1*w2= " << (2 * w1 * w2) << endl;
			cout << "w1*w2*2= " << (w1 * w2 * 2) << endl;
			cout << "w2*w3= " << (w2 * w3) << endl;
			cout << "w1*1= " << (w1 * 1) << endl;
			cout << "5*w1= " << (5 * w1) << endl;
			cout << "w1*0= " << (w1 * 0) << endl;
			cout << "(z+2)*(2*(z+3))= " << (Word{.coef=1, .root=2, .power=1} * Word{.coef=2, .root=3, .power=1}) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Sentence Addition)" << endl;

			cout << "(w1)+(w2)= " << (Sentence(w1) + Sentence(w2)) << endl;

			Sentence res, res2;
			expand(res, w2);
			expand(res, w1);
			compact(res2, res);
			cout << "w1+w2= " << res << endl;
			cout << "w1+w2= " << res2 << endl;
		}

		{
			cout << endl << "Test #" << ++i << " (Divide)" << endl;
			cout << "w1/w2= " << (w1 / w2) << endl;
			cout << "w2/w3= " << (w2 / w3) << endl;
			cout << "w3/w2= " << (w3 / w2) << endl;
			cout << "w3/1= " << (w3 / 1) << endl;
			cout << "w3/2= " << (w3 / 2) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Divide)" << endl;
			Word x1{.coef=6, .root = 0, .power=3};
			Word x2{.coef=2, .root = 0, .power=1};
			Sentence quotient, remainder;
			div(quotient, remainder, x1, x2);
			cout << x1 << " / " << x2 << " = " << endl << quotient << " + [ " << remainder << " ]" << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Divide)" << endl;
			Sentence s1(5 * Word::Z2 + 2 * Word::Z + 3 * Word::ONE);
			Sentence s2(0 * Word::Z2 + 1 * Word::Z + 1 * Word::ONE);
			Sentence quotient, remainder;
			div(quotient, remainder, s1, s2);
			cout << s1 << " / " << s2 << " = " << endl << quotient << " + [ " << remainder << " ]" << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Divide)" << endl;
			Sentence s1(5 * Word::Z2 + 2 * Word::Z + 3 * Word::ONE);
			Sentence s2(2 * Word::Z2 + 4 * Word::Z + 1 * Word::ONE);
			Sentence quotient, remainder;
			div(quotient, remainder, s1, s2);
			cout << s1 << " / " << s2 << " = " << endl << quotient << " + [ " << remainder << " ]" << endl;
		}

		{
			cout << endl << "Test #" << ++i << " (Laurent)" << endl;
			auto around = 1, count = 10;
			Sentence s1(Word::ONE);
			Sentence s2(Word::Z + 1 * Word::ONE);
			Sentence result;
			cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Laurent)" << endl;
			auto around = 0, count = 10;
			Sentence s1(Word::ONE);
			Sentence s2(-1 * Word::Z + 1 * Word::ONE);
			Sentence result;
			cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Laurent)" << endl;
			auto around = 0, count = 10;
			Sentence s1(Word::Z);
			Sentence s2(-1 * Word::Z + 1 * Word::ONE);
			Sentence result;
			cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Laurent)" << endl;
			auto around = 0, count = 10;
			Sentence s1(Word::ONE);
			Sentence s2((-1 * Word::Z + 1 * Word::ONE) * Sentence(Word::Z));
			Sentence result;
			cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Laurent)" << endl;
			auto around = 0, count = 10;
			Sentence s1(Word::ONE);
			Sentence s2(Word::Z + 1 * Word::ONE);
			Sentence result;
			cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Laurent)" << endl;
			auto around = 0, count = 10;
			Sentence s1(Word::ONE);
			Sentence s2(Word::Z - 1 * Word::ONE);
			Sentence result;
			cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Laurent)" << endl;
			auto around = 1, count = 10;
			Sentence s1(Word::ONE);
			Sentence s2(Word::Z);
			Sentence result;
			cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Laurent)" << endl;
			auto around = 2, count = 10;
			Sentence s1(Word::ONE);
			Sentence s2(Word::Z + 1 * Word::ONE);
			Sentence result;
			cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Laurent)" << endl;
			auto around = 1, count = 10;
			Sentence s1(5 * Word::Z2 + 2 * Word::Z + 3 * Word::ONE);
			Sentence s2(2 * Word::Z2 + 4 * Word::Z + 0 * Word::ONE);
			Sentence result;
			cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
		}
		{
			cout << endl << "Test #" << ++i << " (Laurent)" << endl;
			auto around = 0, count = 10;
			Sentence s1(3 * Word::ONE);
			Sentence s2(2 * Word::Z2 + 4 * Word::Z);
			Sentence result;
			cout << "around:" << around << endl << s1 << " / " << s2 << " = " << endl << laurent(result, s1, s2, around, count) << endl;
		}

		{
			cout << endl << "Test #" << ++i << " (generate Exp Taylor)" << endl;
			auto count = 5;
			{
				Sentence s, ss;
				Word w = Word::Z;
				generateExp(s, w, count);
				expand(ss, s);
				cout << "exp(" << w << ")=" << endl << s << endl << ss << endl;
			}
			{
				Sentence s, ss;
				Word w = Word::Z2;
				generateExp(s, w, count);
				expand(ss, s);
				cout << "exp(" << w << ")=" << endl << s << endl << ss << endl;
			}
			{
				Sentence s, ss;
				Word w{.coef =1, .root = 2, .power=1};
				generateExp(s, w, count);
				expand(ss, s);
				cout << "exp(" << w << ")=" << endl << s << endl << ss << endl;
			}
		}
	}
}
