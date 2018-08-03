#pragma once
#include <iostream>
#include <string>
#include <utility> //for std::swap

class Fraction {
private:
	int num = 1; //default value of 1
	int den = 1; //default value of 1
	void reduce();
	void fix_negative(); //called by constructors, if denominator ever gets negative by going around this things will break

public:
	int getNumerator() const;
	int getDenominator() const;
	Fraction(); //initializes as 1/1
	Fraction(int num);
	Fraction(int num, int den);
	std::string print() const;

	//unary overloading member operators
	Fraction& operator= (int set_value);
	Fraction& operator= (Fraction set_value);

	Fraction& operator+=(int to_add);
	Fraction& operator+=(Fraction to_add);

	Fraction& operator-=(int to_subtract);
	Fraction& operator-=(Fraction to_subtract);

	Fraction& operator*=(int to_multiply);
	Fraction& operator*=(Fraction to_multiply);

	Fraction& operator/=(int to_divide);
	Fraction& operator/=(Fraction to_divide);
	
	Fraction operator-() const;

	//overloading casts
	operator int();
	operator float();
	operator double();

	//static helper functions people may use independantly from the class
	static int gcd(int first, int second);
	static int lcm(int first, int second);

//friend functions to overload operators
friend bool operator==(const Fraction &first, const Fraction &second);
friend bool operator!=(const Fraction &first, const Fraction &second);
friend bool operator<=(const Fraction &first, const Fraction &second);
friend bool operator< (const Fraction &first, const Fraction &second);
friend bool operator>=(const Fraction &first, const Fraction &second);
friend bool operator> (const Fraction &first, const Fraction &second);

friend Fraction operator+(const Fraction &first, const Fraction &second);
friend Fraction operator+(const Fraction &first, int second);
friend Fraction operator+(int first, const Fraction &second);

friend Fraction operator-(const Fraction &first, const Fraction &second);
friend Fraction operator-(const Fraction &first, int second);
friend Fraction operator-(int first, const Fraction &second);

friend Fraction operator*(const Fraction &first, const Fraction &second);
friend Fraction operator*(const Fraction &first, int second);
friend Fraction operator*(int first, const Fraction &second);

friend Fraction operator/(const Fraction &first, const Fraction &second);
friend Fraction operator/(const Fraction &first, int second);
friend Fraction operator/(int first, const Fraction &second);

friend std::ostream& operator<<(std::ostream &out, const Fraction &fraction);
};