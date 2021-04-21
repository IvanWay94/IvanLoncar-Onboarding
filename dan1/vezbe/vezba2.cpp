#include <iostream>

// Овде написати следећу функцију:
// int fibo(int n)


int main()
{
	static_assert(fibo(7) == 13, "Greska!");
	const int k = fibo(9);
	std::cout << k << std::endl;
	constexpr int l = fibo(300); // 300. Фибоначијев број је превелик за int
}
