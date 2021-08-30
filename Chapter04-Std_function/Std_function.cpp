#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <functional>

// Упаковка лямбда выражений в std::function (полиморфизм через лямбды)
// std::function - полиморфическая вспомогательная библиотечная функция, которая полезна для оборачивания лямбда-выражений и сокрытия различий в их типах
// Функция возвращает лямбду с разными контейнерами
template <typename C>
static auto consumer(C& container)
{
	return [&](auto value) {
		container.push_back(value);
	};
}

template <typename C>
static void print(const C& c)
{
	for (auto i : c) {
		std::cout << i << ", ";
	}
	std::cout << '\n';
}


int main()
{
	std::deque<int>  d;
	std::list<int>   l;
	std::vector<int> v;
	// Вектор функциональных объектов с разными контейнерами

	// При захвате все большего и большего количества переменных лямбда - выражение будет увеличиваться.
	// Если его размер относительно мал, то std::function может хранить его внутри себя.
	// Если же размер сохраненного объекта функций слишком велик, то std::function выделит фрагмент памяти в куче и сохранит объект там
	const std::vector<std::function<void(int)>> consumers{ consumer(d), consumer(l), consumer(v) };

	for (size_t i{ 0 }; i < 10; ++i) {
		for (auto&& consume : consumers) {
			consume(i);
		}
	}

	print(d);
	print(l);
	print(v);
}