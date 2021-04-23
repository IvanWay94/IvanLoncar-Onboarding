#ifndef _MY_BIG_INT_
#define _MY_BIG_INT_

#include <cstdint>
#include <iostream>
#include <ostream>


struct MyBigInt {

	MyBigInt() {};
	MyBigInt(int n) {
		int len = 0;
		int var = n;
		int_least8_t digit = 0;
		while (var > 0)
		{
			var /= 10;
			len++;
		}
		size = len;
		digits = new int_least8_t[size + 1];
		var = n;
		len = 0;
		while (var > 0)
		{
			digits[len] = (int_least8_t)(var % 10);
			var /= 10;
			len++;
		}
		/*len = len / 2;
		var = 0;
		while (len > 0)
		{
			digit = digits[var];
			digits[var] = digits[size - 1 - var];
			digits[size - 1 - var] = digit;
			var++;
			len--;
		}*/
	}
	~MyBigInt() { delete (digits); }

	const MyBigInt& operator=(const MyBigInt& other) {
		if (this == &other)
			return *this;
		size = other.size;
		delete[] digits;
		digits = new int_least8_t[other.size];
		memcpy(digits, other.digits, size);
		return *this;
	}

	const MyBigInt& operator=(int n) {
		*this = MyBigInt(n);
		return *this;		
	}

	MyBigInt(const MyBigInt& other)
	{
		size = other.size;
		digits = new int_least8_t[other.size];
		memcpy(digits, other.digits, size);
	}
	

	MyBigInt(MyBigInt&& other) {
		//std::cout << "Move Constructor" << std::endl;
		size = other.size;
		digits = other.digits;
		other.digits = nullptr;
	}
	//MyBigInt(int n, const char* t) { size = n; digits = (int_least8_t*)t; }
	friend MyBigInt operator+(const MyBigInt& lhs, const MyBigInt& rhs);
	//friend MyBigInt operator!=(const MyBigInt& lhs, const MyBigInt& rhs);
	//friend MyBigInt operator"" _mbi(char t);
	friend std::ostream& operator<<(std::ostream& os, const MyBigInt& Value);
private:
	int_least8_t* digits = nullptr;
	int size = 0;
};

std::ostream& operator<<(std::ostream& os, const MyBigInt& Value)
{
	int size = Value.size;
	char* arr = new char[size+1];
	int i = 0;
	while (size)
	{
		arr[i] =  (Value.digits[Value.size - i -1] + 48);
		i++;
		size--;
	}
	arr[i] = (char)0;
	std::string s(arr);
	os << s;
  	return os;
}

/*bool operator!=(const MyBigInt& lhs, const MyBigInt& rhs){
	//To be implemented
	return true;
}*/

/*MyBigInt operator"" _mbi(const char* t)
{
	return MyBigInt(sizeof(t), t);
}*/


#endif
