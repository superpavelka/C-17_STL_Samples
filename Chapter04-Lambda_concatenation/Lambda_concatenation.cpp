#include <iostream>
#include <functional>

// Пример конкатенации лямбда функций(по сути пайплайн из списка функций где возвращаемое значение предыдущей подается на вход следующей)
// f(g(h(...)))
// Реализовано через рекурсию f( concat(g, h) ) -> g( concat(h) ) ) - последний шаг рекурсии concat для одной функции
template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts)
{
	// конструкция if constexpr проверяет, находимся ли мы на шаге рекурсии, требующем сконкатенировать более чем одну функцию
	if constexpr (sizeof...(ts) > 0) 
	{
		return [=](auto ...parameters) { return t(concat(ts...)(parameters...)); };
	}
	// последний шаг рекурсии - просто возвращаем последнюю функцию
	else 
	{
		return t;
	}
}

int main()
{
	auto twice([](int i) { return i * 2; });
	auto thrice([](int i) { return i * 3; });

	// выполняется справа налево, сначала складываются два числа - plus, потом thrice, потом twice 
	auto combined(concat(twice, thrice, std::plus<int>{}));

	std::cout << combined(2, 3) << '\n';
}