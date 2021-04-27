#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
#include <math.h>

template<typename T>
void stampaj_elemente(const T& c) {
	for (const auto& x : c) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}

template<typename T>
T square(const T& Left, const T& Right)
{
	return (Left + Right * Right);
}
int main()
{
	std::vector<int> ints;

	// 1. Иницијализовати вектор ints вредностима 0 - 99.

	std::generate_n(
		std::back_insert_iterator<std::vector<int>>(ints), 
		100, [n = 0]() mutable { return n++; }             
	);

	std::cout << "Inicijalna vrednost vektora:\n";
	stampaj_elemente(ints);

	std::vector<int> ints2{ ints };  // Копирање оригиналних вредности вектора ints у вектор ints2

	// 2. Модификовати вектор ints (не ints2) квадратима иницијалних вредности.

	std::transform(ints.begin(), ints.end(), ints.begin(), [](int n) {return n * n; });

	std::cout << "\n\nKvadrati:\n";
	stampaj_elemente(ints);

	int initial{};
	int sum_of_squares{

		// 3. Сабрати квадрате елемента вектора ints2.
		//std::accumulate(ints2.begin(), ints2.end(), 0, [](int n, int m) {return n  + m * m; })
		std::accumulate(ints2.begin(), ints2.end(), 0, square<int>)

	};
	std::cout << "\n\nZbir kvadrata = " << sum_of_squares << "\n";
	assert(sum_of_squares == 328350 && "Pogresna vrednost zbira kvadrata!");

	std::cout << "\nParni brojevi:\n";

	// 4. Штампај елементе вектора ints2 чија је вредност паран број.

	std::copy_if(ints2.begin(), ints2.end(), std::ostream_iterator<int>(std::cout, " "), [](int x) { return (x % 2) == 0; });
}

