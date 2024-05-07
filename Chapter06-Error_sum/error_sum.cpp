#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>

/*
Потенциальная реализация std::inner_product
template<class InIt1, class InIt2, class T, class F, class G>
T inner_product(InIt1 it1, InIt1 end1, InIt2 it2, T val,
F bin_op1, G bin_op2)
{
    while (it1 != end1) {
    val = bin_op1(val, bin_op2(*it1, *it2));
    ++it1;
    ++it2;
}
return value;
}

Алгоритм принимает пару итераторов (начальный и конечный) для первого диапазона данных, а также начальный итератор для второго диапазона. 
В нашем случае они представляют собой векторы, для которых нужно определить ошибку суммы. Следующий символ — исходное значение val. 
Мы инициализировали его значением 0.0. Затем алгоритм принимает две бинарные функции, которые называются bin_op1 и bin_op2.
К этому моменту мы понимаем, что данный алгоритм очень похож на std::accumulate. Единственное отличие состоит в том, что последний работает только для одного диапазона данных. 
Если мы заменим выражение bin_op2(*it1, *it2) на *it, то перейдем к алгоритму accumulate. Поэтому можно считать std::inner_product версией алгоритма std::accumulate, 
которая упаковывает пары входных значений.
В нашем случае функция-упаковщик выглядит как pow(a - b, 2). Для другой функции, bin_op1, мы выбрали std::plus<double>, поскольку хотим сложить сразу все значения, возведенные в квадрат.

*/

using namespace std;

double pi = std::acos(-1.0);

int main()
{
    const size_t sig_len{ 100 };

    // вектора сигналов для которых будем искать ошибку
    // as - аналоговый, ds - цифровой
    vector<double> as(sig_len);
    vector<int>    ds(sig_len);

    // лямбда генерации синусоиды
    auto sin_gen([n{ 0 }]() mutable { return 5.0 * sin(n++ * 2.0 * pi / 100); });

    // генерируем синусоиду в вектор
    generate(begin(as), end(as), sin_gen);
    copy(begin(as), end(as), begin(ds));

    copy(begin(as), end(as), ostream_iterator<double>{cout, " "});
    cout << '\n';
    copy(begin(ds), end(ds), ostream_iterator<double>{cout, " "});
    cout << '\n';

#if 1
    cout << inner_product(begin(as), end(as), begin(ds), 0.0,
        std::plus<double>{},
        [](double a, double b) { return pow(a - b, 2); }) << '\n';
#else
    for (auto it(begin(as)); it != end(as); ++it) {
        cout << inner_product(begin(as), it, begin(ds), 0.0,
            std::plus<double>{},
            [](double a, double b) { return pow(a - b, 2); }) << ' ';
    }
    cout << '\n';
#endif
}