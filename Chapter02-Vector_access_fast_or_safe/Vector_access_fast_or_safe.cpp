#include <iostream>
#include <vector>
#include <array>
#include <numeric> // for std::iota

// std::iota заполняет вектор возрастающими значениями
// [] работают быстрее чем at, но они небезопасны

int main()
{
    constexpr size_t container_size{ 1000 };

#if 1
    std::vector<int> v(container_size);

    // Заполняет вектор возрастающими значениями от указанного (0,1,2,3...)
    std::iota(std::begin(v), std::end(v), 0);
#if 0
    // Скорее всего упадет с ошибкой Debug Assertion Failed
    std::cout << "Out of range element value: "
        << v[container_size + 10] << "\n";
#endif
    try {
        // Метод at кидает исключение, в случае выхода за границы
        std::cout << "Out of range element value: "
            << v.at(container_size + 10) << "\n";

    }
    catch (const std::out_of_range& e) {
        // которое мы успешно перехватываем
        std::cout << "Ooops, out of range access detected: "
            << e.what() << "\n";
    }
#endif

    //Далее все то же самое для std::array

    // Такие же правила работают для std::array:
    std::array<int, container_size> a;

    // Fill the vector with rising numbers
    std::iota(std::begin(a), std::end(a), 0);

    // Chances are, that the following line will not lead to a crash...
    std::cout << "Out of range element value: "
        << a[container_size + 10] << "\n";

#if 0
    try {
#endif
        // This out of bounds access DOES lead to an exception...
        std::cout << "Out of range element value: "
            << a.at(container_size + 10) << "\n";

#if 0
    }
    catch (const std::out_of_range& e) {
        // ...which we catch here.
        std::cout << "Ooops, out of range access detected: "
            << e.what() << "\n";
    }
#endif
}
