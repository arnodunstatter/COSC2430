#include "Complex.h"
#include <iostream>

using namespace std;

int main()
{
	double real, imagi;

	cout << "Let's make a complex number!\nPlease enter the real portion of your complex number: ";
	cin >> real;
	cout << "Now enter the imaginary portion: ";
	cin >> imagi;

	Complex cNum = Complex(real, imagi); //calls our constructor


	cout << "Let's confirm that your values loaded correctly by using our accessor functions...\n";
	cout << "Your complex number's real portion appears to be: " << cNum.real() << endl;
	cout << "Your complex number's imaginary portion appears to be: " << cNum.imag() << endl;

	cout << "Now let's check that our computational functions work by using them...\n";
	cout << "Your complex number's absolute value is " << cNum.abs() << endl;
	Complex expCNum = cNum.exp();
	cout << "Your complex number's exponential has a real portion of " << expCNum.real() << endl;
	cout << "and an imaginary portion of " << expCNum.imag() << endl;
	
	cout << "Now let's check our mutator function...\n";
	cNum.normalize();
	cout << "We just called our normalize function, so let's check our complex number's constituents:\n";
	cout << "Now our complex number's real portion is " << cNum.real() << endl;
	cout << "and its imaginary portion is " << cNum.imag() << endl; 

	return 0;
}