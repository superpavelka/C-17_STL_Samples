#include <iostream>
#include <tuple>
#include <map>
#include <stdexcept>

// Структурированные привязки
// По сути распаковка параметров структуры

// До C++17 использовалась tie: Минус надо объявлять переменные до использования, 
// Плюс можно использовать ignore - переменные пустышки


// вычисляем целую часть fraction и остаток remainder при делении dividend на divisor
bool divide_remainder(int dividend, int divisor, int &fraction, int &remainder)
{
	if (divisor == 0) {
		return false;
	}
	fraction = dividend / divisor;
	remainder = dividend % divisor;
	return true;
}
// вычисляем целую часть fraction и остаток remainder и делаем из них пару pair при делении dividend на divisor
std::pair<int, int> divide_remainder(int dividend, int divisor)
{
	if (divisor == 0) {
		throw std::runtime_error{ "Attempt to divide by 0" };
	}
	return { dividend / divisor, dividend % divisor };
}

int main()
{
	{ // старый способ до C++11
		int fraction, remainder;
		const bool success{ divide_remainder(16, 3, fraction, remainder) };
		if (success) {
			std::cout << "16 / 3 is " << fraction << " with a remainder of " << remainder << "\n";
		}
	}

	{ // C++11
		const auto result(divide_remainder(16, 3));
		std::cout << "16 / 3 is " << result.first << " with a remainder of " << result.second << "\n";
	}

	{ // C++11 пример использования tie 
		int remainder;
		std::tie(std::ignore, remainder) = divide_remainder(16, 5);
		std::cout << "16 % 5 is " << remainder << "\n";
	}

	{ // C++17 пример использования структурированных привязок
		auto[fraction, remainder] = divide_remainder(16, 3);
		std::cout << "16 / 3 is " << fraction << " with a remainder of " << remainder << "\n";
	}

	{ // C++17 пример распаковки кортежа
		std::tuple<int, float, long> tup{ 1, 2.0, 3 };
		auto[a, b, c] = tup;
		std::cout << a << ", " << b << ", " << c << "\n";
	}

	{ // C++17 использование распаковки в цикле

		std::map<std::string, size_t> animal_population{
		{ "humans",   7000000000 },
		{ "chickens", 17863376000 },
		{ "camels",   24246291 },
		{ "sheep",    1086881528 }
		/* … */
		};

		for (const auto &[species, count] : animal_population) {
			std::cout << "There are " << count << " " << species.c_str() << " on this planet.\n";
		}
	}
}