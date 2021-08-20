#include <iostream>

// Пример реализации итерации по алгоритму на примере чисел Фибоначчи

// Итератор по числам Фибоначчи
class fibit
{
	// индекс позиции
	size_t i{ 0 };
	// два последних значения
	size_t a{ 0 };
	size_t b{ 1 };

public:
	fibit() = default;

	explicit fibit(size_t i_)
		: i{ i_ }
	{}

	size_t operator*() const { return b; }

	constexpr fibit& operator++() {
		const size_t old_b{ b };
		b += a;
		a = old_b;
		++i;
		return *this;
	}

	bool operator!=(const fibit& o) const { return i != o.i; }
};

//класс диапазона Фибоначчи, чтобы использовать в for range based
class fib_range
{
	size_t end_n;

public:
	fib_range(size_t end_n_)
		: end_n{ end_n_ }
	{}

	fibit begin() const { return fibit{}; }
	fibit end()   const { return fibit{ end_n }; }
};

int main()
{
	for (size_t i : fib_range(10)) {
		std::cout << i << ", ";
	}
	std::cout << '\n';
}