#include "class.h"

int nod(int a, int b) {
	if (a == 0 || b == 0)
		return 1;
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	if (a == b)
		return a;
	if (a > b)
		return nod(a - b, b);
	else
		return nod(b - a, a);
};

Rational::Rational() {
	numer = 0;
	denom = 1;
}

Rational::Rational(int a, int b) {
	numer = a;
	denom = b;
}

Rational::Rational(int a) {
	numer = 1;
	denom = a;
}

Rational Rational::operator - () const {
	Rational new_r = (*this);
	return  new_r *= -1;
}

Rational& Rational::operator ++ () {
	numer += denom;
	this->simplify();
	return *this;
}
Rational& Rational::operator -- () {
	numer -= denom;
	this->simplify();
	return *this;
}
Rational& Rational::operator ++ (int) {
	Rational new_r(*this);
	++(*this);
	this->simplify();
	return new_r;
}
Rational& Rational::operator -- (int) {
	Rational new_r(*this);
	--(*this);
	this->simplify();
	return new_r;
}

Rational& Rational::operator +=(const Rational& r) {
	numer = (numer * r.denom + denom * r.numer);
	denom *= r.denom;
	this->simplify();
	return *this;
}

Rational& Rational::operator +=(const int& num) {
	numer = (numer + denom * num);
	this->simplify();
	return *this;
}

Rational Rational::operator + (const Rational& r) {
	Rational new_r(*this);
	return new_r += r;
}

Rational Rational::operator + (const int& num) {
	Rational new_r(*this); 
	new_r.numer += num * new_r.denom;
	new_r.simplify();
	return new_r;
}



Rational& Rational::operator -=(const Rational& r) {
	numer = (numer * r.denom - denom * r.numer);
	denom *= r.denom;
	this->simplify();
	return *this;
}

Rational& Rational::operator -=(const int& num) {
	numer = (numer - denom * num);
	this->simplify();
	return *this;
}

Rational Rational::operator - (const Rational& r) {
	Rational new_r(*this);
	return new_r -= r;
}
Rational Rational::operator - (const int& num) {
	Rational new_r(*this);
	new_r.numer -= num * new_r.denom;
	new_r.simplify();
	return new_r;
};

Rational& Rational::operator *=(const Rational& r) {
	numer *= r.numer;
	denom *= r.denom;
	this->simplify();
	return *this;
}

Rational& Rational::operator *=(const int& num) {
	numer *= num;
	this->simplify();
	return *this;
}

Rational Rational::operator *(const Rational& r) {
	Rational new_r(*this);
	return new_r *= r;
};
Rational Rational::operator * (const int& num) {
	Rational new_r(*this);
	new_r.numer *= num;
	new_r.simplify();
	return new_r;
};

Rational& Rational::operator /=(const Rational& r) {
	numer *= r.denom;
	denom *= r.numer;
	this->simplify();
	return *this;
}

Rational& Rational::operator /=(const int& num) {
	denom *= num;
	this->simplify();
	return *this;
}

Rational Rational::operator /(const Rational& r) {
	Rational new_r(*this);
	return new_r /= r;
};
Rational Rational::operator / (const int& num) {
	Rational new_r(*this);
	return	new_r /= num;
};


ostream& operator << (ostream& out, const Rational& n) {
	out << n.numer << '/' << n.denom;
	return out;
}

istream& operator >> (istream& in, Rational& n) {
	in >> n.numer >> n.denom;
	return in;
}

void Rational::simplify() {
	int n = nod(numer, denom);
	if (numer < 0 && denom < 0) {
		numer *= -1;
		denom *= -1;
	}
	if (n != 0) {
		numer /= n;
		denom /= n;
	}
}

void Rational::modul() {
	this->simplify();
	if (denom < 0) {
		numer *= -1;
		denom *= -1;
	}
}

void Rational::flip() {
	int b = numer;
	numer = denom;
	denom = b;
}

Rational::operator int() const {
	return numer / denom;
}
Rational::operator double() const {
	return double(numer) / double(denom);
}

bool operator ==(const Rational& r1, const Rational& r2) {
	return r1.numer * r2.denom == r2.numer * r1.denom;
}
bool operator !=(const Rational& r1, const Rational& r2) {
	return r1.numer * r2.denom != r2.numer * r1.denom;
}
bool operator <(const Rational& r1, const Rational& r2) {
	Rational new_r1 = r1, new_r2 = r2;
	new_r1.modul();
	new_r2.modul();
	return new_r1.numer * new_r2.denom < new_r2.numer * new_r1.denom;
}
bool operator >(const Rational& r1, const Rational& r2) {
	Rational new_r1 = r1, new_r2 = r2;
	new_r1.modul();
	new_r2.modul();
	return new_r1.numer * new_r2.denom > new_r2.numer* new_r1.denom;
}

bool operator <=(const Rational& r1, const Rational& r2) {
	return r1 == r2 || r1 < r2;
}
bool operator >=(const Rational& r1, const Rational& r2) {
	return r1 == r2 || r1 > r2;
}

Rational operator +(const int& i_n, const Rational& r_n) {
	Rational new_r = r_n;
	new_r += i_n;
	return new_r;
}