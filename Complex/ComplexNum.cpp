#include <cmath>
#include<iostream>
#include "utils.h"
#include "ComplexNum.h"
#include "ComplexFunction.h"

namespace Complex {
	const ComplexNum C0{true, 0, 0};
//	const ComplexNum C0e{false, 0, 0};
	const ComplexNum C1{true, 1, 0};
//	const ComplexNum C1e{true, 1, 0};
//	const ComplexNum Cn1{true, -1, 0};
//	const ComplexNum Cn1e{true, 1, M_PI};
//	const ComplexNum CP{true, M_PI, 0};
	const ComplexNum CI{true, 0, 1};
	const ComplexNum CIe{false, 1, M_PI / 2.0};
	const ComplexNum CE{false, 1, 1};
//	const ComplexNum CnI{true, 0, -1};
//	const ComplexNum CnIe{false, 1, M_PI * (3.0 / 2.0)};

	ComplexNum::ComplexNum(bool isCart, double left, double right) {
		copyFrom(isCart, left, right);
	}

	ComplexNum::ComplexNum(const ComplexNum &z) {
		copyFrom(z);
	}

	ComplexNum cart(double re, double im) {
		return {true, re, im};
	}

	ComplexNum euler(double radius, double angle) {
		return {false, radius, angle};
	}


	void ComplexNum::copyFrom(bool isCart, double l, double r) {
		this->iscart = isCart;
		this->left = isCart ? l : (l >= 0 ? l : -l);
		this->right = r;//isCart ? r : principle(r);
	}

	void ComplexNum::copyFrom(const ComplexNum &z) {
		copyFrom(z.iscart, z.left, z.right);
	}

	bool ComplexNum::isCartesian() const {
		return iscart;
	}

	bool ComplexNum::isEuler() const {
		return !iscart;
	}

	bool ComplexNum::isZero() const {
		if (iscart)
			return this->left == 0 && this->right == 0;
		else
			return this->left == 0;
	}

	bool ComplexNum::isReal() const {
		return ROUND(this->getImag()) == 0;
	}

	double ComplexNum::getReal() const {
		if (iscart)
			return this->left;
		else
			return this->left * std::cos(this->right);
	}

	double ComplexNum::getImag() const {
		if (iscart)
			return this->right;
		else
			return this->left * std::sin(this->right);
	}

	double ComplexNum::getRadius() const {
		//if (iscart)
		//	return std::sqrt(std::pow(this->left, 2) + std::pow(this->right, 2));
		//else
		//	return this->left;
		return len();
	}

	double ComplexNum::getAngle() const {
		if (iscart)
			return std::atan(this->right / this->left);
		else
			return this->right;
	}

	double ComplexNum::len2() const {
		if (iscart)
			return std::pow(this->left, 2) + std::pow(this->right, 2);
		else
			return std::pow(this->left, 2);
	}

	double ComplexNum::len() const {
		if (iscart)
			return std::sqrt(this->len2());
		else
			return this->left;
	}

	ComplexNum ComplexNum::toCartesian() const {
		return cart(
				this->getReal(),
				this->getImag()
		);
	}

	ComplexNum ComplexNum::toEuler() const {
		return euler(
				this->getRadius(),
				this->getAngle()
		);
	}

	ComplexNum ComplexNum::clone() const {
		return {
				this->iscart,
				this->left,
				this->right,
		};
	}

	ComplexNum ComplexNum::operator+(ComplexNum const &that) const {
		return cart(
				this->getReal() + that.getReal(),
				this->getImag() + that.getImag()
		);
	}

	ComplexNum ComplexNum::operator-(ComplexNum const &that) const {
		return cart(
				this->getReal() - that.getReal(),
				this->getImag() - that.getImag()
		);
	}

	ComplexNum ComplexNum::operator*(ComplexNum const &that) const {
		if (this->isCartesian() && that.isCartesian()) {
			const auto x1 = this->getReal(), y1 = this->getImag();
			const auto x2 = that.getReal(), y2 = that.getImag();
			return cart(
					x1 * x2 - y1 * y2,
					x1 * y2 + x2 * y1
			);
		} else {
			const auto r1 = this->getRadius(), t1 = this->getAngle();
			const auto r2 = that.getRadius(), t2 = that.getAngle();
			return euler(
					r1 * r2,
					t1 + t2
			);
		}
	}

	ComplexNum ComplexNum::operator*(double const &that) const {
		if (this->isCartesian()) {
			return cart(
					this->getReal() * that,
					this->getImag() * that
			);
		} else {
			return euler(
					this->getRadius() * that,
					this->getAngle()
			);
		}
	}

	ComplexNum ComplexNum::operator/(ComplexNum const &that) const {
		if (this->isCartesian() && that.isCartesian()) {
			const auto x1 = this->getReal(), y1 = this->getImag();
			const auto x2 = that.getReal(), y2 = that.getImag();
			const auto l2 = that.len2();
			return cart(
					(x1 * x2 + y1 * y2) / l2,
					(x2 * y1 - x1 * y2) / l2
			);
		} else {
			const auto r1 = this->getRadius(), t1 = this->getAngle();
			const auto r2 = that.getRadius(), t2 = that.getAngle();
			return euler(
					r1 / r2,
					t1 - t2
			);
		}
	}

	ComplexNum ComplexNum::operator/(double const &c) const {
		if (this->isCartesian()) {
			return cart(
					this->getReal() / c,
					this->getImag() / c
			);
		} else {
			return euler(
					this->getRadius() / c,
					this->getAngle()
			);
		}
	}

	ComplexNum ComplexNum::operator^(double const &c) const {
		return Complex::pow(*this, c);
	}

	ComplexNum ComplexNum::operator^(ComplexNum const &that) const {
		return Complex::pow(*this, that);
	}

	ComplexNum ComplexNum::operator%(double const &c) const {
		if (this->isCartesian()) {
			return cart(
					(int) (this->getReal()) % (int) c,
					(int) (this->getReal()) % (int) c
			);
		} else {
			return euler(
					(int) (this->getRadius()) % (int) c,
					this->getAngle()
			);
		}
	}

	ComplexNum ComplexNum::operator%(const ComplexNum &that) const {
		return *this % that.getReal();
	}

//	ComplexNum &ComplexNum::operator=(const ComplexNum &that) {
//		this->iscart = that.iscart;
//		this->left = that.left;
//		this->right = that.right;
//		return *this;
//	}

	ComplexNum &ComplexNum::operator=(const double &c) {
		this->iscart = true;
		this->left = c;
		this->right = 0;
		return *this;
	}

	std::ostream &ComplexNum::printCartesian(std::ostream &os) const {
		const auto re = ROUND(this->getReal());
		const auto im = ROUND(this->getImag());
		if (im == 0) {
			os << "(" << re << ")";
		} else if (re == 0) {
			os << "i(" << im << ")";
		} else {
			os << "(" << re << ")+i(" << im << ")";
		}
		return os;
	}

	std::ostream &ComplexNum::printEuler(std::ostream &os) const {
		const auto ra = ROUND(this->getRadius());
		const auto te = ROUND(this->getAngle() / M_PI);
		if (ra == 0 || te == 0) {
			os << "(" << ra << ")";
		} else {
			//os << "(" << ra << ").e^iπ(" << te << ")";
			os << "(" << ra << ").exp(PI.(" << te << "))";
		}
		return os;
	}

	std::ostream &ComplexNum::print(std::ostream &os) const {
		if (isCartesian())
			return printCartesian(os);
		else
			return printEuler(os);
	}

	std::ostream &operator<<(std::ostream &os, const ComplexNum &comp) {
		return comp.print(os);
	}

	double len(const ComplexNum &z) {
		return z.len();
	}

	double len2(const ComplexNum &z) {
		return z.len2();
	}

	double arg(const ComplexNum &z) {
		return z.getAngle();
	}

	double re(const ComplexNum &z) {
		return z.getReal();
	}

	double im(const ComplexNum &z) {
		return z.getImag();
	}

	ComplexNum neg(const ComplexNum &z) {
		if (z.isCartesian()) {
			return cart(
					-z.getReal(),
					-z.getImag()
			);
		} else {
			return euler(
					z.getRadius(),
					z.getAngle() + M_PI
			);
		}
	}

	ComplexNum conj(const ComplexNum &z) {
		if (z.isCartesian()) {
			return cart(
					z.getReal(),
					-z.getImag()
			);
		} else {
			return euler(
					z.getRadius(),
					-z.getAngle()
			);
		}
	}

	ComplexNum lenComplex(const ComplexNum &z) {
		return cart(len(z), 0);
	}

	ComplexNum len2Complex(const ComplexNum &z) {
		return cart(len2(z), 0);
	}

	ComplexNum argComplex(const ComplexNum &z) {
		return cart(arg(z), 0);
	}

	ComplexNum reComplex(const ComplexNum &z) {
		return cart(re(z), 0);
	}

	ComplexNum imComplex(const ComplexNum &z) {
		return cart(im(z), 0);
	}

	double principle(double angle) {
		return inrange(angle, -M_PI, +M_PI);
	}
}
