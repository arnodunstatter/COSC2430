#include "Complex.h"

//constructor
Complex::Complex(double re, double im)
	:re(re), im(im) {}


//destructor
Complex::~Complex() {}


// Accessors
double Complex::real() const
{
	return re;
}

double Complex::imag() const
{
	return im;
}

//Computer functions
double Complex::abs() const
{
	return sqrt(re * re + im * im);
}

Complex Complex::exp() const
{
	double exp_re = std::exp(re);
	return Complex(exp_re * std::cos(im), exp_re * std::sin(im));
}

// Mutators
void Complex::normalize() //makes unit absolute value = 1
{
	if (re == 0 && im == 0) {
		return;
	}

	double absval = abs();
	re /= absval;
	im /= absval;
}
