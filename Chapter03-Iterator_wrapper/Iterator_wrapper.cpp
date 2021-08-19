#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <deque>

// Использование оберток итераторов для заполнения обощенных структур данных

using namespace std;

int main()
{
	istream_iterator<int> it_cin{ cin };
	istream_iterator<int> end_cin;

	deque<int> v;
	// back_inserter автоматически вставляет в конец 
	// эта оболочка итератора по сути выполняет метод push_back 
	// для каждого элемента полученного из потока ввода
	copy(it_cin, end_cin, back_inserter(v));

	istringstream sstr{ "123 456 789" };
	// делаем указатель на середину деки
	auto deque_middle(next(begin(v), static_cast<int>(v.size()) / 2));
	// используем inserter чтобы указать место вставки
	copy(istream_iterator<int>{sstr}, {}, inserter(v, deque_middle));

	initializer_list<int> il2{ -1, -2, -3 };
	// front_inserter соответственно вставляет в начало деки
	copy(begin(il2), end(il2), front_inserter(v));
	// ostream_iterator итератор вывода - перенаправляет данные в cout и разделяет запятой
	copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
	cout << '\n';
}