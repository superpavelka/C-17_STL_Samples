#include <iostream>
#include <list>
#include <iterator>

// примеры использования обратных итераторов

using namespace std;

int main()
{
	list<int> l{ 1, 2, 3, 4, 5 };

	copy(l.rbegin(), l.rend(), ostream_iterator<int>{cout, ", "});
	std::cout << '\n';

	// если у контейнера нет rbegin или rend но он выдает двунаправленные итераторы
	// то можно преобразовать прямые итераторы в обратные с помощью make_reverse_iterator
	copy(make_reverse_iterator(end(l)),
		make_reverse_iterator(begin(l)),
		ostream_iterator<int>{cout, ", "});
	std::cout << '\n';
}