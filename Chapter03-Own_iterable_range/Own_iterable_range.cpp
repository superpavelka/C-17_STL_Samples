#include <iostream>

// —оздание собственного класса итератора

// Ќужно только реализовать оператор префиксного инкремента++, оператор разыменовани€* 
// и оператор сравнени€ объектов == , и получитс€ примитивный итератор, подход€щий дл€ 
// работы с циклом for, основанным на диапазоне, который по€вилс€ в C++11

class num_iterator {
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
};

// —оздание собсвтвенного итерабельного диапазона

class num_range {
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

	for (int i : r) {
		std::cout << i << ", ";
	}
	std::cout << '\n';
}