#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

/*
std::find
Принимает в качестве аргументов диапазон данных и значение для сравнения. 
Возвращает итератор, который указывает на первый элемент, равный значению для сравнения. Поиск выполняется линейно
std::find_if
Работает точно так же, как и std::find, но использует функцию-предикат вместо конкретного значения
std::binary_search
Принимает в качестве аргументов диапазон данных и значение для сравнения. Выполняет бинарный поиск и возвращает значение true, если диапазон содержит заданное значение
std::lower_bound
Принимает диапазон данных и значение для сравнения, а затем выполняет бинарный поиск первого элемента, чье значение не меньше значения для сравнения. 
Возвращает итератор, указывающий на этот элемент
std::upper_bound
Работает точно так же, как и std::lower_bound, но возвращает итератор на первый элемент, чье значение больше значения для сравнения
std::equal_range
Принимает диапазон данных и значение для сравнения, а затем возвращает пару итераторов. Первый итератор — результат вызова std::lower_bound, а второй — вызова std::upper_bound
*/

using namespace std;

struct city {
    string   name;
    unsigned population;
};

bool operator==(const city& a, const city& b) {
    return a.name == b.name && a.population == b.population;
}

ostream& operator<<(ostream& os, const city& city) {
    return os << "{" << city.name << ", " << city.population << "}";
}

template <typename C>
static auto opt_print(const C& container)
{
    return[end_it(end(container))](const auto& item) {
        if (item != end_it) {
            cout << *item << '\n';
        }
        else {
            cout << "<end>\n";
        }
    };
}

int main()
{
    const vector<city> c{
        {"Aachen",        246000},
        {"Berlin",       3502000},
        {"Braunschweig",  251000},
        {"Cologne",      1060000}
    };

    auto print_city(opt_print(c));

    {
        auto found_cologne(find(begin(c), end(c), city{ "Cologne", 1060000 }));
        print_city(found_cologne);
    }

    {
        auto found_cologne(find_if(begin(c), end(c), [](const auto& item) {
            return item.name == "Cologne";
            }));
        print_city(found_cologne);
    }

    {
        auto population_more_than([](unsigned i) {
            return [=](const city& item) { return item.population > i; };
            });

        auto found_large(find_if(begin(c), end(c), population_more_than(2000000)));
        print_city(found_large);
    }

    const vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto print_int(opt_print(v));

    bool contains_7{ binary_search(begin(v), end(v), 7) };
    cout << contains_7 << '\n';

    auto [lower_it, upper_it](equal_range(begin(v), end(v), 7));
    print_int(lower_it);
    print_int(upper_it);

    print_int(lower_bound(begin(v), end(v), 7));
    print_int(upper_bound(begin(v), end(v), 7));
}