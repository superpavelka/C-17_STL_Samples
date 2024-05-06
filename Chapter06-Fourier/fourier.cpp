#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <valarray>
#include <cmath>

using namespace std;

// Тип csignal может быть вектором, содержащим комплексные числа.Для работы с такими числами 
// в STL существует класс std::complex.Функция std::polar, по сути, выполняет часть exp(–i * 2 * ...).
using cmplx = complex<double>;
using csignal = vector<cmplx>;

double pi = std::acos(-1.0);

class num_iterator {
    size_t i;
public:

    explicit num_iterator(size_t position) : i{ position } {}

    size_t operator*() const { return i; }

    num_iterator& operator++() {
        ++i;
        return *this;
    }

    bool operator!=(const num_iterator& other) const {
        return i != other.i;
    }
};

#if 0
csignal fourier_transform(const csignal& s, bool back = false)
{
    csignal t(s.size());

    const double pol{ 2.0 * M_PI * (back ? -1.0 : 1.0) };
    const double div{ back ? 1.0 : double(s.size()) };

    for (size_t k{ 0 }; k < t.size(); ++k) {
        for (size_t j{ 0 }; j < s.size(); ++j) {
            t[k] += s[j] * polar(1.0, pol * k * j / double(s.size()));
        }
        t[k] /= div;
    }

    return t;
}
#else

csignal fourier_transform(const csignal& s, bool back = false)
{
    csignal t(s.size());

    const double pol{ 2.0 * pi * (back ? -1.0 : 1.0) / s.size() };
    const double div{ back ? 1.0 : double(s.size()) };

    auto sum_up([=, &s](size_t j) {
        return [=, &s](cmplx c, size_t k) {
            return c + s[k] * polar(1.0, pol * k * j);
        };
        });

    auto to_ft([=, &s](size_t j) {
        return accumulate(num_iterator{ 0 }, num_iterator{ s.size() }, cmplx{},
            sum_up(j)) / div;
        });

    transform(num_iterator{ 0 }, num_iterator{ s.size() }, begin(t), to_ft);

    return t;
}

#endif

// Генератор косинусоидального сигнала. Она возвращает лямбда-выражение, 
// способное сгенерировать косинусоидальный сигнал на основе заданной длины периода.
// Сам сигнал может иметь произвольную длину, но его длина периода будет фиксированной.
// Длина периода N означает, что сигнал повторит себя спустя N шагов.Лямбда - выражение не принимает никаких параметров.
// Можно постоянно вызывать его, и для каждого вызова оно будет возвращать точку графика сигнала для следующего момента времени.
static auto gen_cosine(size_t period_len)
{
    return[period_len, n{ 0 }]() mutable {
        return cos(double(n++) * 2.0 * pi / period_len);
    };
}
// Прямоугольная волна.Она колеблется между значениями –1 и + 1 и не имеет других значений.Преобразует линейное увеличивающееся значение n в + 1 или –1, 
// а изменяющаяся длина периода равна period_len.
// Инициализируем n значением, не равным 0. Таким образом, наша прямоугольная волна начинается в фазе, где ее выходные значения начинаются с +1.
static auto gen_square_wave(size_t period_len)
{
    return[period_len, n{ period_len * 7 / 4 }]() mutable {
        return ((n++ * 2 / period_len) % 2) * 2 - 1.0;
    };
}
// Сгенерировать сам сигнал с помощью указанных генераторов можно, выделив память для нового вектора и заполнив его значениями, 
// сгенерированными на основе повторяющихся вызовов функции-генератора. Это делает функция std::generate. 
// Она принимает пару итераторов (начальный и конечный) и функцию-генератор. Для каждой корректной позиции итератора она выполняет операцию *it = gen().
template <typename F>
static csignal signal_from_generator(size_t len, F gen)
{
    csignal r(len);
    generate(begin(r), end(r), gen);
    return r;
}

static void print_signal(const csignal& s)
{
    auto real_val([](cmplx c) { return c.real(); });
    transform(begin(s), end(s), ostream_iterator<double>{cout, " "}, real_val);
    cout << '\n';
}

int main()
{
    // стандартная длина сигнала
    const size_t sig_len{ 100 };

    // генерация косиноидального и прямоугольного сигналов
    auto cosine(signal_from_generator(sig_len, gen_cosine(sig_len / 2)));
    auto square_wave(signal_from_generator(sig_len, gen_square_wave(sig_len / 2)));

    // преобразование фурье для сигнала прямоугольной волны
    auto trans_sqw(fourier_transform(square_wave));
    // заполнение нулями сигнала от 10 до signal_length - 10
    fill(next(begin(trans_sqw), 10), prev(end(trans_sqw), 10), 0);
    // обратное преобразование фурье
    auto mid(fourier_transform(trans_sqw, true));

    print_signal(cosine);
    print_signal(fourier_transform(cosine));

    print_signal(mid);
    print_signal(trans_sqw);

    print_signal(square_wave);
    print_signal(fourier_transform(square_wave));
}