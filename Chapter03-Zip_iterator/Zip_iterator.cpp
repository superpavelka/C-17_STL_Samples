#include <iostream>
#include <vector>
#include <numeric>
#include <valarray>

// Воссоздание функции zip из Python, Haskell (только для векторов типа double)
// (функция попарно склеивает значения двух векторов)
// реализация в виде итератора, который будет итерироваться одновременно по двум контейнерам

// Библиотека ranges. Это очень интересная библиотека для языка C++, которая поддерживает упаковщики и все прочие виды волшебных адаптеров итераторов, фильтров и т. д. 
// https://ericniebler.github.io/range-v3/

class zip_iterator
{
	using it_type = std::vector<double>::iterator;

	it_type it1;
	it_type it2;

public:
	zip_iterator(it_type iterator1, it_type iterator2)
		: it1{ iterator1 }, it2{ iterator2 }
	{}

	zip_iterator& operator++()
	{
		++it1;
		++it2;
		return *this;
	}

	bool operator!=(const zip_iterator& o) const
	{
		return it1 != o.it1 && it2 != o.it2;
	}

	bool operator==(const zip_iterator& o) const 
	{
		return !operator!=(o);
	}

	std::pair<double, double> operator*() const 
	{
		return { *it1, *it2 };
	}
};

namespace std {

	template <>
	struct iterator_traits<zip_iterator> 
	{
		using iterator_category = std::forward_iterator_tag;
		using value_type = std::pair<double, double>;
		using difference_type = long int;
	};

}

class zipper {
	using vec_type = std::vector<double>;
	vec_type& vec1;
	vec_type& vec2;

public:
	zipper(vec_type& va, vec_type& vb)
		: vec1{ va }, vec2{ vb }
	{}

	zip_iterator begin() const { return { std::begin(vec1), std::begin(vec2) }; }
	zip_iterator end()   const { return { std::end(vec1),   std::end(vec2) }; }
};

using namespace std;

int main()
{
	vector<double> vec_a{ 1.0, 2.0, 3.0 };
	vector<double> vec_b{ 4.0, 5.0, 6.0 };

	zipper zipped{ vec_a, vec_b };

	// складывает произведение пары и предыдущую сумму
	const auto add_product([](double sum, const auto& p) 
		{
		return sum + p.first * p.second;
		});
	// std::accumulate складывает элементы диапазона данных
	const auto scalar_product(accumulate(begin(zipped), end(zipped), 0.0, add_product));

	cout << scalar_product << '\n';

	// пример скалярного произведения через valarray
	std::valarray<double> a{ 1.0, 2.0, 3.0 };
	std::valarray<double> b{ 4.0, 5.0, 6.0 };
	std::cout << (a * b).sum() << '\n';
}