#include <iostream>
#include <algorithm>
#include <iterator>
#include <complex>
#include <numeric>
#include <vector>

using namespace std;

using cmplx = complex<double>;

static auto scaler(int min_from, int max_from,
    double min_to, double max_to)
{
    const int    w_from{ max_from - min_from };
    const double w_to{ max_to - min_to };
    const int    mid_from{ (max_from - min_from) / 2 + min_from };
    const double mid_to{ (max_to - min_to) / 2.0 + min_to };

    return [=](int from) {
        return double(from - mid_from) / w_from * w_to + mid_to;
    };
}

template <typename A, typename B>
static auto scaled_cmplx(A scaler_x, B scaler_y)
{
    return [=](int x, int y) {
        return cmplx{ scaler_x(x), scaler_y(y) };
    };
}

static auto mandelbrot_iterations(cmplx c)
{
    cmplx  z{};
    size_t iterations{ 0 };
    const size_t max_iterations{ 1000 };
    while (abs(z) < 2 && iterations < max_iterations) {
        ++iterations;
        z = pow(z, 2) + c;
    }
    return iterations;
}

int main()
{
    const size_t w{ 100 };
    const size_t h{ 40 };

    auto scale(scaled_cmplx(
        scaler(0, w, -2.0, 1.0),
        scaler(0, h, -1.0, 1.0)
    ));

    // преобразует одномерную координату в комплексные x и y(т.к. обернуто в std::complex)
    auto i_to_xy([=](int x) { return scale(x % w, x / w); });

    // функция to_iteration_count по сути представляет цепочку вызовов от i_to_xy до scale и mandelbrot_iterations
    auto to_iteration_count([=](int x) { return mandelbrot_iterations(i_to_xy(x)); });

    vector<int> v(w * h);
    // заполняет вектор значениями от 0 до v.size()
    iota(begin(v), end(v), 0);

    // все расчеты происходят во время вызова std::transform
    transform(begin(v), end(v), begin(v), to_iteration_count);

    // Предоставим ему(std::accumulate) бинарную функцию, принимающую итератор вывода
    // (который мы свяжем с терминалом на следующем шаге) и отдельное значение из диапазона.
    // Выведем это значение как символ *, если количество итераций превышает 50. 
    // В противном случае выведем пробел.При нахождении в конце строки
    // (поскольку переменная - счетчик n без остатка делится на w) выведем символ разрыва строки
    auto binfunc([w, n{ 0 }](auto output_it, int x) mutable {
        *++output_it = (x > 50 ? '*' : ' ');
        if (++n % w == 0) { ++output_it = '\n'; }
        return output_it;
    });

    accumulate(begin(v), end(v), ostream_iterator<char>{cout}, binfunc);
}