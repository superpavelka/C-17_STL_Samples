#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <map>
#include <sstream>
#include <iomanip>

/*
template<class InIterator, class OutIterator,
    class Distance, class UniformRandomBitGenerator>
    OutIterator sample(InIterator first, InIterator last,
        SampleIterator out, Distance n,
        UniformRandomBitGenerator&& g);
Входной диапазон данных обозначается итераторами first и last, в то время как out — итератор вывода.
Эти итераторы выполняют ту же функцию, что и для функции std::copy; элементы копируются из одного диапазона в другой.
Алгоритм std::sample является особенным с той точки зрения, что копирует только часть входного диапазона, поскольку делает выборку только n элементов.
Он использует равномерное распределение внутри системы, поэтому каждая точка на графике во входном диапазоне данных может быть выбрана с одинаковой вероятностью.
*/

using namespace std;

int main()
{
    // размер большого вектора и размер выборки
    const size_t data_points{ 100000 };
    const size_t sample_points{ 100 };

    // математическое ожидание и квадратическое отклонение
    const int    mean{ 10 };
    const size_t sigma{ 3 };

    // настройка генератора случайных чисел
    random_device rd;
    mt19937 gen{ rd() };

    // объект нормального распределения
    normal_distribution<> d{ mean, sigma };

    vector<int> v;
    v.reserve(data_points);

    // алгоритм generate_n вызывает объект функции генератора случайных чисел и передает значение в вектор
    // благодаря итератору back_inserter
    generate_n(back_inserter(v), data_points, [&] { return d(gen); });

    vector<int> samples;
    v.reserve(sample_points);

    // Алгоритм std::sample работает аналогично алгоритму std::copy, 
    //но при этом принимает два дополнительных параметра — количество точек, 
    //получаемых из входного диапазона данных, и объект генератора случайных чисел, 
    //к которому он будет обращаться, чтобы получить случайные позиции пробных точек
    sample(begin(v), end(v), back_inserter(samples), sample_points, mt19937{ random_device{}() });

    map<int, size_t> hist;

    for (int i : samples) { ++hist[i]; }

    for (const auto& [value, count] : hist) {
        cout << setw(2) << value << " "
            << string(count, '*') << '\n';
    }
}