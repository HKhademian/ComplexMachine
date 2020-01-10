#ifndef COMPLEX_H
#define COMPLEX_H

#include<iostream>

namespace Complex {
	class ComplexNum {

	private:
		bool iscart = true;
		double left = 0;
		double right = 0;

	public:
		ComplexNum() = default;

		ComplexNum(bool iscart, double left, double right);

		ComplexNum(const ComplexNum &z);

		void copyFrom(bool isCart, double l, double r);

		void copyFrom(const ComplexNum &z);

		bool isCartesian() const;

		bool isEuler() const;

		bool isZero() const;

		bool isReal() const;

		double getReal() const;

		double getImag() const;

		double getRadius() const;

		double getAngle() const;

		double len2() const;

		double len() const;

		ComplexNum toCartesian() const;

		ComplexNum toEuler() const;

		ComplexNum clone() const;

		ComplexNum operator+(const ComplexNum &that) const;

		ComplexNum operator-(const ComplexNum &that) const;

		ComplexNum operator*(const ComplexNum &that) const;

		ComplexNum operator/(const ComplexNum &that) const;

		ComplexNum operator%(const ComplexNum &c) const;

		ComplexNum operator^(const ComplexNum &that) const;

		ComplexNum operator*(const double &c) const;

		ComplexNum operator/(const double &c) const;

		ComplexNum operator%(const double &c) const;

		ComplexNum operator^(const double &c) const;

		ComplexNum &operator=(const double &c);

		std::ostream &printCartesian(std::ostream &os = std::cout) const;

		std::ostream &printEuler(std::ostream &os = std::cout) const;

		std::ostream &print(std::ostream &os = std::cout) const;
	};

	extern const ComplexNum C0, C1, CI, CIe, CE;

	ComplexNum cart(double re, double im);

	ComplexNum euler(double radius, double angle);


	std::ostream &operator<<(std::ostream &os, const ComplexNum &comp);

	double principle(double angle);

	double len(const ComplexNum &z);

	double len2(const ComplexNum &z);

	double arg(const ComplexNum &z);

	double re(const ComplexNum &z);

	double im(const ComplexNum &z);


	ComplexNum neg(const ComplexNum &z);

	ComplexNum conj(const ComplexNum &z);

	ComplexNum lenComplex(const ComplexNum &z);

	ComplexNum len2Complex(const ComplexNum &z);

	ComplexNum argComplex(const ComplexNum &z);

	ComplexNum reComplex(const ComplexNum &z);

	ComplexNum imComplex(const ComplexNum &z);
}

#endif //COMPLEX_H