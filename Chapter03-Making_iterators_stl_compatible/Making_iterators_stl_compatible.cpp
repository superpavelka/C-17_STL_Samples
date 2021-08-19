#include <iostream>
#include <algorithm>

// ќбеспечение совместимости нашего итератора с STL

class num_iterator
{
	int i;
public:

	explicit num_iterator(int position = 0) : i{ position } {}

	int operator*() const { return i; }

	num_iterator& operator++() 
	{
		++i;
		return *this;
	}

	bool operator!=(const num_iterator& other) const 
	{
		return i != other.i;
	}

	bool operator==(const num_iterator& other) const 
	{
		return !(*this != other);
	}
};

// ќдним алгоритмам STL нужно знать характеристики типа итератора, примен€емого вместе с ними, 
// другим Ч тип элементов, среди которых выполн€етс€ перебор. ќт этого завис€т варианты реализации алгоритмов.
// ќднако все алгоритмы STL будут получать эту информацию о типе с помощью std::iterator_traits<my_iterator>, 
// предполага€, что итератор имеет тип my_iterator. Ётот класс типажа содержит до п€ти разных определений членов.

namespace std 
{
	// ѕерегружа€ эту структуру признаков, мы помогаем алгоритмам STL получать доступ к определени€м 
	// типов дл€ нашего настраиваемого итератора. ƒругой способ - поместить следующие определени€ типов в класс итератора. 

	// ƒо по€влени€ C++17 поощр€лось наследование итераторами типа std::iterator<...>, 
	// что автоматически заполн€ет наш класс всеми описани€ми типов.Ётот механизм все еще работает, 
	// но, начина€ с —++17, больше не рекомендуетс€.

	template <>
	struct iterator_traits<num_iterator> 
	{
		// к какой категории принадлежит итератор
		using iterator_category = std::forward_iterator_tag;
		// какой тип имеет элемент, к которому мы получаем доступ с помощью* it
		// (внимание : дл€ чистых итераторов вывода этот тип будет void)
		using value_type = int;

		// Ётот тип можно использовать дл€ определени€ разницы между двум€ итераторами. 
		// Ёто, конечно, имеет смысл только в том случае, если мы определим операцию 
		// разности дл€ нашего итератора (и оператора + и т.д.) 
		using difference_type = int;

		// “ип указател€ дл€ итерируемых объектов		
		using pointer = int*;

		// “оже самое дл€ ссылки
		using reference = int&;
	};

}

class num_range 
{
	int a;
	int b;

public:
	num_range(int from, int to)
		: a{ from }, b{ to }
	{}

	num_iterator begin() const { return num_iterator{ a }; }
	num_iterator end()   const { return num_iterator{ b }; }
};

int main()
{
	num_range r{ 100, 110 };

	auto [min_it, max_it](std::minmax_element(std::begin(r), std::end(r)));
	std::cout << *min_it << " - " << *max_it << '\n';
}