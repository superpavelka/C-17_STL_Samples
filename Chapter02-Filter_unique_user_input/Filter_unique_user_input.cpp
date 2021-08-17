#include <iostream>
#include <set>
#include <string>
#include <iterator> // for ostream_iterator

// Пример использования std::set для фильтрации уникальных элементов в потоке ввода

using namespace std;

int main()
{
	set<string> s;
	// позволяет обрабатывать большие объемы однотипных данных, 
	// получаемых из потока и работатать с ними как с обычным итератором

	istream_iterator<string> it{ cin };

	//Конечный итератор — это экземпляр std::istream_iterator, созданный с помощью стандартного 
	// конструктора без параметров. Он нужен для сравнения в условии остановки, проверяемом на каждой итерации цикла

	istream_iterator<string> end;

	// std::inserter - это функция, возвращающая итератор std::insert_iterator, 
	// который ведет себя как итератор, но при этом делает что - то отличное от того, 
	// что делают обычные итераторы.Выполнение операции инкремента для данного итератора 
	// ничего не даст.Когда мы его разыменовываем и присваиваем значение, он берет контейнер, 
	// прикрепленный к нему, и добавляет в него заданное значение как новый элемент

	copy(it, end, inserter(s, s.end()));

	for (const auto word : s) 
	{
		cout << word << ", ";
	}
	cout << '\n';
}