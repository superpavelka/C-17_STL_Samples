#include <iostream>

// Использование итераторов ограничителей (иногда бывают случаи, когда мы не знаем, 
// например, конечную позицию для перебора(поток воода или перебор строки в C стиле))

// В данном примере показан пример создания итератора ограничителя для перебора в range based for на примере C-style строки
// Начиная с C++17 начальный и конечный итераторы не обязаны иметь один тип. 
// В данном разделе мы продемонстрируем, как правильно использовать это небольшое изменение в правилах.

class cstring_iterator_sentinel {};

class cstring_iterator {
	const char* s{ nullptr };

public:
	explicit cstring_iterator(const char* str)
		: s{ str }
	{}

	char operator*() const { return *s; }

	cstring_iterator& operator++() {
		++s;
		return *this;
	}

	// Оператор сравнения сравнивает текущую позицию с ограничителем
	// в данном случае проверяем на конец строки \0
	bool operator!=(const cstring_iterator_sentinel) const {
		return s != nullptr && *s != '\0';
	}
};

// создаем класс диапазона для итерации в цикле for 
// и указываем конечный итератор ограничитель
class cstring_range {
	const char* s{ nullptr };

public:
	cstring_range(const char* str)
		: s{ str }
	{}

	cstring_iterator          begin() const { return cstring_iterator{ s }; }
	cstring_iterator_sentinel end()   const { return {}; }
};

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cout << "Please provide one parameter.\n";
		return 1;
	}

	const char* const param{ argv[1] };

	for (char c : cstring_range(param)) {
		std::cout << c;
	}
	std::cout << '\n';
}