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

MyBigInt fibo(int n);

int main()
{
	MyBigInt k{ 7 };
	k = std::move(fibo(9));
	k = k + 5;
	std::cout << k << std::endl;
	k = 7 + fibo(11);
	std::cout << k << std::endl;
	k = 13_mbi;
	std::cout << k << std::endl;
	MyBigInt l = fibo(300);
	if (l != 222232244629420445529739893461909967206666939096499764990979600_mbi) {
		std::cout << "Greska!" << std::endl;
		return 1;
	}
	std::cout << l << std::endl;
	return 0;
}

MyBigInt fibo(int n)
{
	MyBigInt fib_1n = 0;
	MyBigInt fib_2n = 1;
	MyBigInt fib_n = 1;
	//for (int i = 2; i <= n; i++)
	int i = 0;
	do{

		fib_2n = fib_1n;
		fib_1n = fib_n;
		fib_n = fib_2n + fib_1n;
		/*fib_2n = std::move(fib_1n);
		fib_1n = std::move(fib_n);
		fib_n = std::move(fib_2n + fib_1n);*/

		i++;
	} while (i < n - 1);

	return fib_n;
}