#ifndef _MY_BIG_INT_
#define _MY_BIG_INT_

#include <cstdint>
#include <iostream>
#include <ostream>


struct MyBigInt {

	constexpr MyBigInt() {};
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
	
	MyBigInt(MyBigInt&& other)
	{
		this->digits = other.digits;
		other.digits = nullptr;
		this->size = other.size;
		other.size = 0;
	}

	MyBigInt& operator=(const char* other) {
		size = strlen(other);
		delete[] digits;
		digits = new int_least8_t[size+1];
		for(int i=0; i<size; i++)
        {
			digits[size-i-1] = other[i] - 48;
		}
		return *this;
	}
	friend bool operator!=(const MyBigInt& lhs, const MyBigInt& rhs);
	friend MyBigInt operator+(const MyBigInt& lhs, const MyBigInt& rhs);
	friend MyBigInt operator"" _mbi(const char *t);
	friend std::ostream& operator<<(std::ostream& os, const MyBigInt& Value);
private:
	int_least8_t* digits = nullptr;
	int size = 0;
};

bool operator!=(const MyBigInt& lhs, const MyBigInt& rhs)
{
	if (lhs.size != rhs.size)
	{
		return true;
	}

	int res = std::memcmp(lhs.digits, rhs.digits, lhs.size); // or rhs.size since both are same
	return res != 0;
}

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

MyBigInt operator"" _mbi(const char* other)
{
	MyBigInt ret{ 0 };
	ret = other;
	return ret;
}


#endif
