#include "fraction.hpp"

//constructors
Fraction::Fraction(int num, int den) {
	this->num = num;
	this->den = den;
	reduce();
	fix_negative();
}
Fraction::Fraction() {

}
Fraction::Fraction(int num) {
	this->num = num;
}

//member functions
std::string Fraction::print() const {
	if(den == 1) {
		return std::to_string(num);
	} else {
		return std::to_string(num) + "/" + std::to_string(den);
	}
}


int Fraction::getNumerator() const {
	return num;
}
int Fraction::getDenominator() const{
	return den;
}

void Fraction::reduce() {
	int gcd = Fraction::gcd(num,den);
	num /= gcd;
	den /= gcd;
}

void Fraction::fix_negative() {
	if (den < 0) {
		den *= -1;
		num *= -1;
	}
}

//overloading unary operators as members
Fraction Fraction::operator-() const {
	return Fraction{num*-1,den};
}

Fraction& Fraction::operator=(int value) {
	num = value;
	den = 1;
}
Fraction& Fraction::operator=(Fraction value) {
	// self-assignment guard
    if (this == &value)
        return *this;
	num = value.num;
	den = value.den;
}
Fraction& Fraction::operator+=(int to_add){
	num += to_add * den;
	reduce();
}
Fraction& Fraction::operator+=(Fraction to_add){
	int lcm_temp = Fraction::lcm(den,to_add.den);
	num = num * (lcm_temp / den) + to_add.num * (lcm_temp / to_add.den);
	den = lcm_temp;
	reduce();
}
Fraction& Fraction::operator-=(int to_subtract) {
	num -= to_subtract * den;
	reduce();
}
Fraction& Fraction::operator-=(Fraction to_subtract) {
	int lcm_temp = Fraction::lcm(den,to_subtract.den);
	num = num * (lcm_temp / den) - to_subtract.num * (lcm_temp / to_subtract.den);
	den = lcm_temp;
	reduce();
}
Fraction& Fraction::operator*=(int to_multiply) {
	num *= to_multiply;
	reduce();
}
Fraction& Fraction::operator*=(Fraction to_multiply) {
	num *= to_multiply.num;
	den *= to_multiply.den;
	reduce();
}
Fraction& Fraction::operator/=(int to_divide) {
	den *= to_divide;
	reduce();
}
Fraction& Fraction::operator/=(Fraction to_divide) {
	den *= to_divide.num;
	num *= to_divide.den;
	reduce();
}

//overloading casts as members
Fraction::operator int() {
	return num / den;
}
Fraction::operator float() {
	return static_cast<float>(num) / static_cast<float>(den);
}
Fraction::operator double() {
	return static_cast<double>(num) / static_cast<double>(den);
}

//static member functions
int Fraction::gcd(int larger, int smaller) {
	if(larger < 0) {
		larger *= -1;
	}
	if(smaller < 0) {
		smaller *= -1;
	}
	//with correct names
	if(larger > smaller) {
		while (larger % smaller != 0) {
			std::swap(larger,smaller);
			smaller = smaller % larger;
		}
		return smaller;
	} else { //with switched around names to avoid doing an extra swap
		while (smaller % larger != 0) {
			std::swap(smaller,larger);
			larger = larger % smaller;
		}
		return larger;
	}
	
}

int Fraction::lcm(int first, int second) {
	return first * second / gcd(first,second);
}

//friend function overloading operators
//addition
Fraction operator+(const Fraction &first, const Fraction &second) {
	int lcm_temp = Fraction::lcm(first.den,second.den);
	return Fraction{first.num * (lcm_temp / first.den) + second.num * (lcm_temp / second.den), lcm_temp};
}
Fraction operator+(int first, const Fraction &second) {
	return Fraction{first * second.den + second.num, second.den};
}
Fraction operator+(const Fraction &first, int second) {
	return Fraction{first.den * second + first.num, first.den};
}
//subtraction
Fraction operator-(const Fraction &first, const Fraction &second) {
	int lcm_temp = Fraction::lcm(first.den,second.den);
	return Fraction{first.num * (lcm_temp / first.den) - second.num * (lcm_temp / second.den), lcm_temp};
}
Fraction operator-(int first, const Fraction &second) {
	return Fraction{first * second.den - second.num, second.den};
}
Fraction operator-(const Fraction &first, int second) {
	return Fraction{first.num - first.den * second, first.den};
}
//multiplication
Fraction operator*(const Fraction &first, const Fraction &second) {
	return Fraction{first.num * second.num, first.den * second.den};
}
Fraction operator*(int first, const Fraction &second) {
	return Fraction{first * second.num, second.den};
}
Fraction operator*(const Fraction &first, int second) {
	return Fraction{first.num * second, first.den};
}
//division
Fraction operator/(const Fraction &first, const Fraction &second) {
	return Fraction{first.num * second.den, first.den * second.num};
}
Fraction operator/(const Fraction &first, int second) {
	return Fraction{first.num, first.den * second};
}
Fraction operator/(int first, const Fraction &second) {
	return Fraction{first * second.den, second.den};
}

//comparisons
bool operator==(const Fraction &first, const Fraction &second) {
	if(first.num == second.num && first.den == second.den) {
		return true;
	} else {
		return false;
	}
}
bool operator!=(const Fraction &first, const Fraction &second) {
	return !(first == second);
}
bool operator<(const Fraction &first, const Fraction &second) {
	int lcm = Fraction::lcm(first.den,second.den);
	return (first.num * (lcm / first.den) < second.num * (lcm / second.den));
}
bool operator>(const Fraction &first, const Fraction &second) {
	int lcm = Fraction::lcm(first.den,second.den);
	return (first.num * (lcm / first.den) > second.num * (lcm / second.den));
}
bool operator<=(const Fraction &first, const Fraction &second) {
	int lcm = Fraction::lcm(first.den,second.den);
	return (first.num * (lcm / first.den) <= second.num * (lcm / second.den));
}
bool operator>=(const Fraction &first, const Fraction &second) {
	int lcm = Fraction::lcm(first.den,second.den);
	return (first.num * (lcm / first.den) >= second.num * (lcm / second.den));
}

//printing
std::ostream& operator<<(std::ostream &out, const Fraction &to_print) {
	if(to_print.den == 1) {
		out << to_print.num;
	} else {
		out << to_print.num << "/" << to_print.den;
	}
}