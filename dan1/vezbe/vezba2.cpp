#include <iostream>

constexpr int fibo(int n)
{
	if (n >= 300 || n < 0)
	{		
		return -1;
	}
	return (n <= 2) ? 1 : (fibo(n - 1) + fibo(n - 2));
}

int main()
{
	static_assert(fibo(7) == 13, "Greska!");
	const int k = fibo(9); 
	//constexpr int k = fibo(9); 
	std::cout << k << std::endl;	
	constexpr int l = fibo(300); // 300. Fibonacci is too big	
	static_assert(fibo(300) == 0, "Error input value is too big");
}
