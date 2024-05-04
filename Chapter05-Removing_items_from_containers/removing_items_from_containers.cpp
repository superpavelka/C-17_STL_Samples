#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

/*
std::remove
Принимает в качестве аргументов диапазон значений и удаляемое значение, затем удаляет из диапазона заданное значение. 
Возвращает новый конечный итератор измененного диапазона данных
std::replace
Принимает в качестве аргументов диапазон значений и два значения, а затем заменяет в диапазоне данных первое указанное значение на второе
std::remove_copy
Принимает в качестве аргументов диапазон данных, итератор вывода и значение, а затем копирует из диапазона все значения, не равные заданному, в конечный итератор
std::replace_copy
Работает аналогично std::replace и std::remove_copy. Исходный диапазон данных не изменяется
std::copy_if
Работает как std::copy, но дополнительно принимает в качестве аргумента функцию-предикат, чтобы скопировать только те значения, которые соответствуют заданному предикатом условию
*/

using namespace std;

void print(const vector<int>& v)
{
    copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
    cout << '\n';
}

int main()
{
    vector<int> v{ 1, 2, 3, 4, 5, 6 };

    print(v);

    {
        // по сути remove перемещает ненужные элементы и возвращает новый конечный итератор
        const auto new_end(remove(begin(v), end(v), 2));
        // элементы между новым и старым конечным итератором считаются мусором и требуется удалить их
        v.erase(new_end, end(v));
    }
    print(v);

    {
        auto odd_number([](int i) { return i % 2 != 0; });
        const auto new_end(remove_if(begin(v), end(v), odd_number));
        v.erase(new_end, end(v));
    }
    print(v);

    replace(begin(v), end(v), 4, 123);
    print(v);

    v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    vector<int> v2;
    vector<int> v3;

    auto odd_number([](int i) { return i % 2 != 0; });
    auto even_number([](int i) { return i % 2 == 0; });

    // копирует из исходного контейнера в другой контейнер то, что не соответствует условию предиката
    remove_copy_if(begin(v), end(v), back_inserter(v2), odd_number);
    // копирует из исходного контейнера в другой контейнер то, что соответствует условию предиката
    copy_if(begin(v), end(v), back_inserter(v3), even_number);

    print(v2);
    print(v3);
}