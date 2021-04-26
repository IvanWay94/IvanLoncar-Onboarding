#include "MyBigInt.h"

#include <iostream>

MyBigInt operator+(const MyBigInt& lhs, const MyBigInt& rhs)
{
	MyBigInt ret{ 0 };
	const MyBigInt& longerArg = (lhs.size < rhs.size) ? rhs : lhs;
	const MyBigInt& shorterArg = (lhs.size < rhs.size) ? lhs : rhs;
	ret.digits = new int_least8_t[longerArg.size + 1];
	int_least8_t reminder = 0;
	for (int i = 0; i < shorterArg.size; i++) {
		int_least8_t tempSum = longerArg.digits[i] + shorterArg.digits[i] + reminder;
		ret.digits[i] = (tempSum > 9) ? tempSum - 10 : tempSum;
		reminder = (tempSum > 9) ? 1 : 0;
	}
	for (int i = shorterArg.size; i < longerArg.size; i++) {
		int_least8_t tempSum = longerArg.digits[i] + reminder;
		ret.digits[i] = (tempSum > 9) ? tempSum - 10 : tempSum;
		reminder = (tempSum > 9) ? 1 : 0;
	}
	if (reminder == 0) {
		ret.size = longerArg.size;
	} else {
		ret.size = longerArg.size + 1;
	}
	ret.digits[longerArg.size] = reminder;
	return ret;
}

struct MyComplex {
	MyComplex() {};
	MyComplex(const MyBigInt& re, const MyBigInt& img) { real = re; imaginary = img; };
	~MyComplex() {};
	MyComplex(const MyComplex& other)
	{
		this->real = other.real;
		this->imaginary = other.imaginary;
	}
	friend std::ostream& operator<<(std::ostream& os, const MyComplex& Value);
	friend MyComplex operator+(const MyComplex& lhs, const MyComplex& rhs);
private:
	MyBigInt real = 0;
	MyBigInt imaginary = 0;

};

MyComplex operator+(const MyComplex& lhs, const MyComplex& rhs)
{
	MyComplex ret;
	ret.real = lhs.real + rhs.real;
	ret.imaginary = lhs.imaginary + rhs.imaginary;
	return ret;
}
std::ostream& operator<<(std::ostream& os, const MyComplex& Value)
{
	MyBigInt img = Value.imaginary;
	MyBigInt re = Value.real;
	os << re << "+i" << img;
	return os;
}

int main()
{
	MyBigInt k{ 7 };
	MyBigInt a{ 12 };
	
	MyComplex C(k, a);
	MyComplex D(1242, 4313);


	MyComplex sum = C + D;

	std::cout << sum;
	return 0;
}
