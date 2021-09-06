#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

//g++ -O2 rational2.cpp -o rational2

int gcd(int a, int b) {
  if (a < 0) {a = -a;}
  if (b < 0) {b = -b;}
  //assert(a > 0 && b > 0);
  int max_a_b = a >= b ? a : b;
  int min_a_b = a <= b ? a : b; 
  if(max_a_b % min_a_b == 0){return min_a_b;}
  else{return gcd((max_a_b % min_a_b), min_a_b);}
}

class Rational {
public:
    Rational() { num = 0; denom = 1; }
    Rational(int numerator, int denominator) {
		if (abs(numerator) > 0){
			num = numerator / gcd(numerator, denominator);
			denom = denominator / gcd(numerator, denominator);
		} else {
			num = 0;
			denom = 1;
		}
        // Реализуйте конструктор
		if (numerator > 0 && denominator < 0 || numerator < 0 && denominator < 0) {
			num = -num;
			denom = -denom;
		}
	}

    int Numerator() const {return num;}
    int Denominator() const { return denom; }
	friend istream& operator>> (istream &stream, Rational &r);
private:
	int num;
	int denom;
};

Rational operator+ (const Rational& r1, const Rational& r2) {
		int d = r1.Denominator() * r2.Denominator();
		int n = r1.Numerator() * r2.Denominator() + r2.Numerator() * r1.Denominator();
		return Rational(n, d);
}
	
Rational operator- (const Rational& r1, const Rational& r2) {
		int d = r1.Denominator() * r2.Denominator();
		int n = r1.Numerator() * r2.Denominator() - r2.Numerator() * r1.Denominator();
		return Rational(n, d);
}

Rational operator* (const Rational& r1, const Rational& r2) {
		int d = r1.Denominator() * r2.Denominator();
		int n = r1.Numerator() * r2.Numerator();
		return Rational(n, d);
}

Rational operator/ (const Rational& r1, const Rational& r2) {
		int d = r1.Denominator() * r2.Numerator();
		int n = r1.Numerator() * r2.Denominator();
		return Rational(n, d);
}

bool operator== (const Rational& r1, const Rational& r2) {
		 if (r1.Numerator() == r2.Numerator() && r1.Denominator() == r2.Denominator()) {return true;}
		 else {return false;}
}

ostream& operator<< (std::ostream& stream, const Rational& r){
	stream << r.Numerator() << "/" << r.Denominator();
	return stream;
}

istream& operator>> (std::istream &in, Rational &r){
	int n = 0, d = 0;
	char c = 0;
	if (!in) {return in;}
	in >> n;  
	in >> c;
	if (c == '/'){
		in >> d;
		if (in) {
			Rational tmp(n, d);
			r.num = tmp.num;
			r.denom = tmp.denom;
		}	
	} else {
		in.ignore(1);
	}	
	return in;
}


int main() {
    {
        std::ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            std::cout << "Rational(-6, 8) should be written as \"-3/4\"" << std::endl;
            return 1;
        }
    }

    {
        std::istringstream input(" 5 / 7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            std::cout << "5/7 is incorrectly read as " << r << std::endl;
            return 2;
        }
    }

    {
        std::istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            std::cout << "Read from empty stream works incorrectly" << std::endl;
            return 3;
        }
    }

    {
        std::istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            std::cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << std::endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            std::cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << std::endl;
            return 5;
        }
    }

    {
        std::istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            std::cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << std::endl;

            return 6;
        }
    }
	
	{
		std::istringstream input("5/ 7 -1/");	
		Rational r1, r2; 
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational();
		if (!correct){
			std::cout << "aaaa" << r1 << " " << r2 << " " << std::endl;
			return 7;
		}
	}
	/*
	cout << "Enter rational: " << endl; 
	{
		Rational r;
		while (cin >> r) {
			cout << "entered rational" << " ";
			cout << r << endl;
		} 
	}
    */
    std::cout << "OK" << std::endl;
    return 0;
}


