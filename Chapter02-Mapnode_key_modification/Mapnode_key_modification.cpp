#include <iostream>
#include <map>

// Начиная с С++17 можно удалить и снова вставить элементы ассоциативного массива без повторного выделения памяти.

// Функция extract — новая возможность С++17. Она удаляет элементы из массива, 
// притом не вызывая побочных эффектов, связанных с выделением памяти.
// node_type extract(const_iterator position);
// node_type extract(const key_type& x);
// работает также для unordered_map и unordered_multimap, а также set/multiset и, соответственно, unordered_set/unordered_multiset.

// Метод insert контейнера std::map в С++17 получил новую перегруженную версию, 
// которая принимает дескрипторы извлеченных узлов, чтобы вставить их в контейнер, не вызывая выделения памяти

using namespace std;

template <typename M>
void print(const M& m)
{
	cout << "Race placement:\n";
	for (const auto& [placement, driver] : m) {
		cout << placement << ": " << driver << '\n';
	}
}

int main()
{
	map<int, string> race_placement{
		{1, "Mario"}, {2, "Luigi"}, {3, "Bowser"},
		{4, "Peach"}, {5, "Yoshi"}, {6, "Koopa"},
		{7, "Toad"}, {8, "Donkey Kong Jr."}
	};

	print(race_placement);

	{
		auto a(race_placement.extract(3));
		auto b(race_placement.extract(8));
		// Метод key предоставляет неконстантный доступ к ключам и их можно поменять
		swap(a.key(), b.key());
		// Для вставки измененных ключей нужно снова сделать insert
		race_placement.insert(move(a));
		race_placement.insert(move(b));
	}


	print(race_placement);
}