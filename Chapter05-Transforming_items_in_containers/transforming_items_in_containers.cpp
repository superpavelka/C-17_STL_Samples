#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

/*
std::transform — Как и copy, он копирует элементы из одного диапазона данных в другой, но дополнительно принимает функцию преобразования. 
Она может изменить значение выходного типа до того, как это значение окажется в выходном диапазоне. 
Более того, данная функция может создать значение совершенно другого типа, что может быть полезно, если входной и выходной диапазоны данных имеют разные типы. 
*/

using namespace std;

int main()
{
    vector<int> v{ 1, 2, 3, 4, 5 };

    transform(begin(v), end(v), ostream_iterator<int>{cout, ", "},
        [](int i) { return i * i; });
    cout << '\n';

    auto int_to_string([](int i) {
        stringstream ss;
        ss << i;
        ss << "^2 = ";
        ss << i * i;
        return ss.str();
        });

    vector<string> vs;

    transform(begin(v), end(v), back_inserter(vs), int_to_string);

    copy(begin(vs), end(vs), ostream_iterator<string>{cout, "\n"});
}