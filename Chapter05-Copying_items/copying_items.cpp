#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <iterator>
#include <algorithm>

// Разбор различных вариантов алгоритма std::copy

using namespace std;

// перегрузка оператора потока для красивого вывода пар
namespace std {
    ostream& operator<<(ostream& os, const pair<int, string>& p)
    {
        return os << "(" << p.first << ", " << p.second << ")";
    }
}

int main()
{
    vector<pair<int, string>> v{
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };

    map<int, string> m;

    // копируем три пары из вектора пар в map, inserter нужен для для преобразования элементов вектора в элементы map(возвращает insert_iterator)
    copy_n(begin(v), 3, inserter(m, begin(m)));
    // итератор ostream_iterator позволяет считать выходные данные пользовательской консоли контейнером в который можно скопировать данные
    auto shell_it(ostream_iterator<pair<int, string>>{cout, ", "});
    copy(begin(m), end(m), shell_it);
    cout << '\n';

    m.clear();
    // а теперь перемещаем а не копируем
    move(begin(v), end(v), inserter(m, begin(m)));

    copy(begin(m), end(m), shell_it);
    cout << '\n';
    // выводим на экран значения вектора т.к. std::move изменяет источник данных
    // увидим, что строки не выводятся
    copy(begin(v), end(v), shell_it);
    cout << '\n';
}