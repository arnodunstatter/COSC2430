#ifndef COMPLEX_H
#define COMPLEX_H
#include <cmath>

class Complex {
private:
    double re, im;

public:
    Complex(double = 0.0, double = 0.0);
    ~Complex();

    // Accessors
    double real() const;
    double imag() const;

    //computational functions
    double abs() const;
    Complex exp() const;

    // Mutators
    void normalize();
};

#endif