#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

using namespace std;
#include <iostream>

class Polynomial {
private:
	int e;
	double *x;

public:
	//Default constructor
	Polynomial() {
		e = 0;
		x = NULL;
	}

	//Constructor With All variables
	Polynomial(int e, double* x) {
		this->e = e;
		this->x = x;
	}

	//Copy Constructor
	Polynomial(const Polynomial& std) {
		e = std.e;
		x = new double[e];
		for (int i = 0; i < e;i++)
			x[i] = std.x[i];
	}

	//Destructor
	~Polynomial() {
		delete[] x;
	}

	//Getter
	int GetE() { return e; }
	double* GetX() { return x; }

	//	>> reads in a polynomial from the user in the form
	friend istream& operator >> (istream &in, Polynomial &polynomial) {
		in >> polynomial.e;
		if (polynomial.e > 21)
			throw "Bad Input!";

		polynomial.x = new double[polynomial.e];
		for (int i = 0; i < polynomial.e; i++) {
			polynomial.x[i] = 0;
			in >> polynomial.x[i];
		}
		
		return in;
	}

	//	<< outputs a polynomial to an ostream object in the exact form such as: 3.1x3  2.0x2 1.3x  5
	friend ostream& operator << (ostream &out, const Polynomial &polynomial) 
	{
		int OutputedNumbers = 0; 

		for (int i = (polynomial.e) - 1; 0 <= i; i--) {
			if (polynomial.x[i] != 0) {			//if (polynomial.x[i] = 0) there is no need to print it

				if (OutputedNumbers != 0)		//after the first number + should be printed.
					out << " + ";

				OutputedNumbers++;

				if (i == 0) {
					out << polynomial.x[i];
				}
				else if (i == 1) {
					if (polynomial.x[i] != 1)	//if (polynomial.x[i] = 1) there is no need to print 1, printing x is enough
						out << polynomial.x[i];
					out << "x";
				}
				else {
					if (polynomial.x[i] != 1)	//if (polynomial.x[i] = 1) there is no need to print 1, printing x^n is enough
						out << polynomial.x[i];
					out << "x^" << i;
				}	
			}
		}
		return out;
	}

	//	+ adds two polynomials and returns the sum to another polynomial
	Polynomial operator + (const Polynomial& std) {
		Polynomial polynomial;
		
		if (this->e > std.e)
			polynomial.e = this->e;
		else
			polynomial.e = std.e;

		double* temp;
		temp = new double[polynomial.e];
		for (int i = 0; i < polynomial.e; i++) {
			temp[i] = 0;
			if (this->e >= i)
				temp[i] += this->x[i];
			if (std.e >= i)
				temp[i] += std.x[i];
		}

		polynomial.x = temp;
		return polynomial;
	}

	//	- subtracts the second polynomial from the first one and returns the result to another polynomia
	Polynomial operator - (const Polynomial& std) {
		Polynomial polynomial;

		if (this->e > std.e)
			polynomial.e = this->e;
		else
			polynomial.e = std.e;

		double* temp;
		temp = new double[polynomial.e];
		for (int i = 0; i < polynomial.e; i++) {
			temp[i] = 0;
			if (this->e >= i)
				temp[i] += this->x[i];
			if (std.e >= i)
				temp[i] -= std.x[i];
		}

		polynomial.x = temp;
		return polynomial;
	}

	//	* multiplies two polynomials and returns the result to another polynomial //exception handling for multiplication degree
	Polynomial operator * (const Polynomial& std) {
		Polynomial polynomial;

		if ((this->e + std.e)-1 > 21)//exception
			throw "Bad Multiplication!";

		polynomial.e = this->e + std.e - 1;

		double* temp;
		temp = new double[polynomial.e];
		for (int i = 0; i < polynomial.e; i++)
			temp[i] = 0;

		for (int i = 0; i < this->e; i++)
			for (int j = 0; j < std.e; j++)
				temp[i + j] += this->x[i] * std.x[j];
		
		polynomial.x = temp;
		return polynomial;
	}

	//	= copies the contents of one polynomial to another one
	void operator = (const Polynomial& std) {
		this -> e = std.e;

		double *temp;
		temp = new double[this->e];
		for (int i = 0; i < this->e; i++)
			temp[i] = std.x[i];

		this->x = temp;
	}

	//	== compares two polynomials and returns true if they are the same
	bool operator == (const Polynomial& std) {
		if (this->e != std.e)
			return false;

		for (int i = (this->e) - 1; 0 <= i; i--)
			if (this->x[i] != std.x[i])
				return false;

		return true;
	}

	//	!= compares two polynomials and returns true if they are not the same
	bool operator != (const Polynomial& std) {
		if (this->e != std.e)
			return true;

		for (int i = (this->e) - 1; 0 <= i; i--)
			if (this->x[i] != std.x[i])
				return true;

		return false;
	}

	//	+= adds two polynomials and assigns the sum to the first polynomial
	void operator += (const Polynomial& std) { // void becase requirements doesnt say returns the result to another polynomial
		if (std.e > this->e)
			this->e = std.e;

		double* temp;
		temp = new double[this->e];
		for (int i = 0; i < this->e; i++) {
			temp[i] = 0;
			if (this->e >= i)
				temp[i] += this->x[i];
			if (std.e >= i)
				temp[i] += std.x[i];
		}

		delete[] x;//delete garbage
		this->x = temp;
	}

	//	! returns to the degree of a polynomial
	int operator ! () {
		return e;
	}

	//	/ takes two operands (the polynomial and the value of x) and returns to the result of polynomial evaluated at x.
	Polynomial operator / (double div) {
		Polynomial polynomial(*this);

		for (int i = 0; i < e; i++)
			polynomial.x[i] = polynomial.x[i] / div;

		return polynomial;
	}
	
};
#endif
