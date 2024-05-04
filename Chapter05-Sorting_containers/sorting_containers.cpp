#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <random>

/*std::sort
Принимает в качестве аргумента диапазон данных и попросту
сортирует их
std::is_sorted
Принимает в качестве аргумента диапазон данных и сообщает, отсортирован ли он
std::shuffle
Выполняет операцию, похожую на сортировку наоборот : принимает диапазон данных и перемешивает его элементы
std::partial_sort
Принимает в качестве аргумента диапазон данных и еще один итератор, который указывает, 
до какой позиции следует сортировать все элементы.
Остальные элементы, стоящие после этого итератора, останутся неотсортированными
std::partition
Принимает диапазон данных и функцию - предикат.Все элементы, для которых данная функция возвращает значение true, 
перемещаются в начало диапазона.Остальные элементы переходят в его конец
*/
/*Существуют и другие алгоритмы, такие как std::stable_sort, которые сортируют элементы, 
но сохраняют порядок элементов с одинаковым ключом сортировки, и std::stable_partition.
*/
using namespace std;

static void print(const vector<int>& v)
{
    copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
    cout << '\n';
}

int main()
{
    vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // генератор случайных чисел
    random_device rd;
    mt19937 g{ rd() };
    // было ли отсортировано?
    cout << is_sorted(begin(v), end(v)) << '\n';
    // перемешиваем значения вектора с помощью генератора случайных чисел
    shuffle(begin(v), end(v), g);
    
    cout << is_sorted(begin(v), end(v)) << '\n';
    print(v);

    // сортировка по возрастанию
    sort(begin(v), end(v));

    cout << is_sorted(begin(v), end(v)) << '\n';
    print(v);

    shuffle(begin(v), end(v), g);
    // секционируем вектор - перемещаем все элементы < 5 в начало
    partition(begin(v), end(v), [](int i) { return i < 5; });

    print(v);

    shuffle(begin(v), end(v), g);

    auto middle(next(begin(v), int(v.size()) / 2));
    // частичная сортировка, в данном случае поместит 5 самых маленьких элементов в начало контейнера, т.к до size() / 2
    partial_sort(begin(v), middle, end(v));

    print(v);

    // хотим отсортировать структуру не поддерживающую оператора сравнения
    struct mystruct {
        int a;
        int b;
    };    
    vector<mystruct> mv{ {5, 100}, {1, 50}, {-123, 1000}, {3, 70}, {-10, 20} };
    // sort может принимать функцию сравнения
    sort(begin(mv), end(mv),
        [](const mystruct& lhs, const mystruct& rhs) {
            return lhs.b < rhs.b;
        });

    for (const auto& [a, b] : mv) {
        cout << "{" << a << ", " << b << "} ";
    }
    cout << '\n';
}