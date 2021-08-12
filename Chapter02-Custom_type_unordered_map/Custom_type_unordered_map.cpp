#include <iostream>
#include <unordered_map>

// Реализация хеш-функции для пользовательского типа данных в unordered_map

struct coord {
	int x;
	int y;
};

bool operator==(const coord& l, const coord& r)
{
	return l.x == r.x && l.y == r.y;
}

// Чтобы расширить возможности хеширования, предоставляемые STL, добавим 
// в пространство имен std свою специализацию шаблонной структуры std::hash.
// Оно содержит такие же псевдонимы(задаваемые с помощью using), как и другие специализации типа hash.

/*
Под капотом у unordered_map
template<
	class Key,
	class T,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>,
	class Allocator = std::allocator< std::pair<const Key, T> >
> class unordered_map;

Для основных типов std::hash<key_type> определен в STL но для пользовательских надо определять самостоятельно
*/

namespace std
{

	template <>
	struct hash<coord>
	{
		using argument_type = coord;
		using result_type = size_t;

		// в примере компоненты вектора просто складываются
		// для хеш-функции не очень хорошо т.к. будут коллизии, но для примера сойдет
		result_type operator()(const argument_type& c) const
		{
			return static_cast<result_type>(c.x)
				+ static_cast<result_type>(c.y);
		}
	};

}
// Если бы мы не добавили новую специализацию std::hash<coord>, а назвали бы имеющуюся вместо этого my_hash_type, 
// то нам пришлось бы использовать следующую строку для создания объекта :
// std::unordered_map<coord, value_type, my_hash_type> my_unordered_map;

int main()
{
	std::unordered_map<coord, int> m{ {{0, 0}, 1}, {{0, 1}, 2}, {{2, 1}, 3} };

	for (const auto& [key, value] : m) {
		std::cout << "{(" << key.x << ", " << key.y << "): " << value << "} ";
	}
	std::cout << "\n";
}

