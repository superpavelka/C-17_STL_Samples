#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>
#include <tuple>
#include <string>
#include <fstream>

/*Алгоритм std::merge принимает две пары начальных и конечных итераторов, обозначающие входные диапазоны данных.
Эти диапазоны должны быть отсортированы.Пятый параметр — итератор вывода, который принимает поступающие элементы во время слияния.
Кроме того, существует вариант алгоритма, который называется std::inplace_merge.
Он делает то же самое, что и предыдущий, но не нуждается в итераторе вывода, поскольку работает на месте, о чем можно догадаться из имени. 
Он принимает три параметра: начальный итератор, итератор для середины и конечный итератор. 
Эти итераторы должны ссылаться на данные в одной структуре. Итератор для середины является одновременно конечным итератором для первого 
диапазона данных и начальным итератором для второго диапазона. Это значит, что алгоритм работает с одним диапазоном данных, 
который на самом деле состоит из двух диапазонов, размещенных один за другим, например {A, C, B, D}. 
Первый поддиапазон — {A, C}, а второй — {B, D}. Алгоритм std::inplace_merge может объединить оба диапазона в одной структуре данных, 
что приведет к результату {A, B, C, D}.
*/

using namespace std;

using dict_entry = pair<string, string>;

namespace std {
    ostream& operator<<(ostream& os, const dict_entry p)
    {
        return os << p.first << " " << p.second;
    }

    istream& operator>>(istream& is, dict_entry& p)
    {
        return is >> p.first >> p.second;
    }
}

// принимает любые объекты потока ввода, будут считываться из потока ввода в deque
template <typename IS>
deque<dict_entry> from_instream(IS&& is)
{
    deque<dict_entry> d{ istream_iterator<dict_entry>{is}, {} };
    sort(begin(d), end(d));
    return d;
}

int main()
{
    ifstream file_in{ "dict.txt" };

    // один словарь из файла, другой из потока ввода
    const auto dict1(from_instream(ifstream{ "dict.txt" }));
    const auto dict2(from_instream(cin));

    merge(begin(dict1), end(dict1),
        begin(dict2), end(dict2),
        ostream_iterator<dict_entry>{cout, "\n"});
}