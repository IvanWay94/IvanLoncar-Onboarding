#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

template<typename T>
void stampaj_elemente(const T& c) {
	for (const auto& x : c) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<int> ints;

	// 1. Иницијализовати вектор ints вредностима 0 - 99.



	std::cout << "Inicijalna vrednost vektora:\n";
	stampaj_elemente(ints);

	std::vector<int> ints2{ints};  // Копирање оригиналних вредности вектора ints у вектор ints2

	// 2. Модификовати вектор ints (не ints2) квадратима иницијалних вредности.



	std::cout << "\n\nKvadrati:\n";
	stampaj_elemente(ints);

	int initial{};
	int sum_of_squares{

		// 3. Сабрати квадрате елемента вектора ints2.


	};
	std::cout << "\n\nZbir kvadrata = " << sum_of_squares << "\n";
	assert(sum_of_squares == 328350 && "Pogresna vrednost zbira kvadrata!");

	std::cout << "\nParni brojevi:\n";

	// 4. Штампај елементе вектора ints2 чија је вредност паран број.


}

