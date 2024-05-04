// Вызываем несколько функций с одинаковыми входными данными
// По сути реализация последовательного вызова нескольких лямбда функций
#include <iostream>

template <typename ... Ts>
static auto multicall(Ts ...functions)
{
    return [=](auto x) {
        (void)std::initializer_list<int>{
            ((void)functions(x), 0)...
        };
    };
}

// Приведение значения(void) в(void)std::initializer_list<int>{ ... } используется для подавления предупреждений компилятора о неиспользуемом возвращаемом значении конструктора initializer_list.
// Выражение ((void)f(xs), 0) применяет функцию f к каждому аргументу xs и отбрасывает возвращаемое значение, используя оператор запятой.Результатом выполнения операции запятой является 0.
// Наконец, конструктор initializer_list используется для инициализации initializer_list значениями, разделенными запятой((void)f(xs), 0). 
// Это приводит к вычислению выражений, разделенных запятой, для каждого элемента в xs.
// В целом, этот шаблон функции позволяет вам применить функцию к каждому аргументу в пакете переменных параметров.

template <typename F, typename ... Ts>
static auto for_each(F f, Ts ...xs) {
    (void)std::initializer_list<int>{
        ((void)f(xs), 0)...
    };
}

static auto brace_print(char a, char b) {
    return [=](auto x) {
        std::cout << a << x << b << ", ";
    };
}

int main()
{
    auto f(brace_print('(', ')'));
    auto g(brace_print('[', ']'));
    auto h(brace_print('{', '}'));
    auto nl([](auto) { std::cout << '\n'; });

    auto call_fgh(multicall(f, g, h, nl));

    for_each(call_fgh, 1, 2, 3, 4, 5);
}