#include <tuple>
#include <string>
#include <type_traits>
#include <iostream>

// CTAD
// Автоматический вывод полученного типа класса шаблона в конструкторе
// Теперь можем не указывать тип данных шаблона в угловых скобках <T>

template <typename T1, typename T2, typename T3>
class my_wrapper {
	T1 t1;
	T2 t2;
	T3 t3;

public:
	my_wrapper(T1 t1_, T2 t2_, T3 t3_)
		: t1{ t1_ }, t2{ t2_ }, t3{ t3_ }
	{}

	/* … */
};
// Делаем свой шаблон
template <typename T>
struct sum 
{
	T value;

	template <typename ... Ts>
	sum(Ts&& ... values) : value{ (values + ...) } {}	
};
// В случае со сверткой будет исключение
// Если не указать явные правила выведения типов, то строки 4 и 5 дадут ошибку
// т.к. компилятор не догадается как вывести тип
template <typename ... Ts>
sum(Ts&& ... values)->sum<std::common_type_t<Ts...>>;

int main()
{
	my_wrapper wrap(123, 4.56, std::string{ "foo" });			//1

	std::pair  pair(123, std::string{ "string" });				//2
	std::tuple tuple(123, 4.56, std::string{ "string" });		//3

	sum s{ 1u, 2.0, 3, 4.0f };									//4
	sum string_sum{ std::string{ "abc" }, "def" };				//5

	std::cout << s.value << '\n'								//6
		<< string_sum.value << '\n';							//7
	std::pair p(2, 4.5);										//8
}