#include <iostream>

using namespace std;

#ifndef _CLASS_
#define _CLASS_

int nod(int a, int b);

class Rational {
	private:
		int numer, denom;
		void simplify();
	public:
		Rational();
		Rational(int a, int b);
		Rational(int a);

		void flip();
		void modul();

		Rational operator - () const;
		Rational& operator ++ ();
		Rational& operator -- ();
		Rational& operator ++ (int);
		Rational& operator -- (int);

		Rational& operator +=(const Rational& r);
		Rational& operator +=(const int& r);
		Rational operator + (const Rational& r);
		Rational operator + (const int& num);

		Rational& operator -=(const Rational& r);
		Rational& operator -=(const int& r);
		Rational operator - (const Rational& r);
		Rational operator - (const int& num);
		
		Rational& operator *=(const Rational& r);
		Rational& operator *=(const int& r);
		Rational operator *(const Rational& r);
		Rational operator * (const int& num);

		Rational& operator /=(const Rational& r);
		Rational& operator /=(const int& r);
		Rational operator /(const Rational& r);
		Rational operator / (const int& num);

		operator int() const;
		operator double() const;

	friend bool operator ==(const Rational& r1, const Rational& r2);
	friend bool operator !=(const Rational& r1, const Rational& r2);
	friend bool operator <(const Rational& r1, const Rational& r2);
	friend bool operator >(const Rational& r1, const Rational& r2);
	friend bool operator <=(const Rational& r1, const Rational& r2);
	friend bool operator >=(const Rational& r1, const Rational& r2);

	friend ostream& operator << (ostream& out, const Rational& n);
	friend istream& operator >> (istream& in, Rational& n);
	friend Rational operator +(const int& i_n,const Rational& r_n);
};




#endif // !_CLASS_
