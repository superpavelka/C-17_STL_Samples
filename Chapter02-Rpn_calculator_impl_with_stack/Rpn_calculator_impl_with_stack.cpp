 #include <iostream>
#include <stack>
#include <iterator>
#include <map>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <cmath>

// ОПН - обратная польская нотация (используется для удобства анализа выражений) - сначала операнды потом операторы
// Примеры: 1 + 2 - ОПН: 1 2 + , (1 + 2) * 3  - ОПН: 1 2 + 3 *

using namespace std;

template <typename IT>
double evaluate_rpn(IT it, IT end)
{
	// Класс std::stack — класс - адаптер, который позволяет помещать в себя объекты, словно в реальную стопку объектов, а также получать их.
	stack<double> val_stack;

	map<string, double (*)(double, double)> ops{
		{"+", [](double a, double b) { return a + b; }},
		{"-", [](double a, double b) { return a - b; }},
		{"*", [](double a, double b) { return a * b; }},
		{"/", [](double a, double b) { return a / b; }},
		{"^", [](double a, double b) { return pow(a, b); }},
		{"%", [](double a, double b) { return fmod(a, b); }},
	};

	auto pop_stack([&]() 
		{ 
		auto r(val_stack.top());		// Получаем копию верхнего значения
		val_stack.pop();				// Удаляем верхнее значение
		return r;						// Возвращаем копию
		}
					);

	for (; it != end; ++it) {
		// stringstream — это такой же stream, как и, например, cin, 
		// только его содержимое берётся не из входного потока программы, а из данной ему строки
		stringstream ss{ *it };
		// если строка может быть преобразована в переменную типа double, то данное число операнд
		if (double val; ss >> val) 
		{
			val_stack.push(val);
		}
		else {
			assert(val_stack.size() >= 2);

			const auto r{ pop_stack() };
			const auto l{ pop_stack() };

			try {
				val_stack.push(ops.at(*it)(l, r));
			}
			catch (const out_of_range&) {
				throw invalid_argument(*it);
			}
		}
	}

	return val_stack.top();
}

int main()
{
	try {
		cout << evaluate_rpn(istream_iterator<string>{cin}, {}) << '\n';
	}
	catch (const invalid_argument & e) {
		cout << "Invalid operator: " << e.what() << '\n';
	}

#if 0
	stringstream s{ "3 2 1 + * 2 /" };
	cout << evaluate_rpn(istream_iterator<string>{s}, {}) << '\n';

	vector<string> v{ "3", "2", "1", "+", "*", "2", "/" };
	cout << evaluate_rpn(begin(v), end(v)) << '\n';
#endif
}