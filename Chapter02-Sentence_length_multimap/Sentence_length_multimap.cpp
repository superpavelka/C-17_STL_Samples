#include <iostream>
#include <iterator>
#include <map>
#include <algorithm>

// Токенизация предложений из строки и подсчет их длины в словах через std::multimap

using namespace std;

// При токенизации строк путем извлечения их содержимого, стоящего между точками, 
// получим предложения текста, окруженные пробелами, символами перехода на новую строку
// и т.д.Это нежелательным образом увеличивает их размер, так что отбросим лишние 
// символы с помощью вспомогательной функции

string filter_ws(const string& s)
{
	const char* ws{ " \r\n\t" };
	const auto a(s.find_first_not_of(ws));
	const auto b(s.find_last_not_of(ws));
	if (a == string::npos) {
		return {};
	}
	return s.substr(a, b - a + 1);
}

multimap<size_t, string> get_sentence_stats(const string& content)
{

	multimap<size_t, string> ret;

	const auto end_it(end(content));
	auto it1(begin(content));         // start at beginning of string
	auto it2(find(it1, end_it, '.')); // Start at first '.' dot character
	// итератор it2 всегда будет указывать на одну точку дальше, чем итератор it1.
	// До тех пор пока итератор it1 не достигнет конца текста, все будет в порядке.
	// Второе условное выражение проверяет, действительно ли итератор it2 указывает на позицию, 
	// стоящую на несколько символов дальше
	while (it1 != end_it && distance(it1, it2) > 0) {

		// токенизируем предложение и удаляем все лишние символы пробелов и переноса строки
		string s{ filter_ws({it1, it2}) };

		if (s.length() > 0) {
			const auto words(count(begin(s), end(s), ' ') + 1);
			ret.emplace(make_pair(words, move(s)));
		}

		if (it2 == end_it) 
			break;

		// Цифра 1 совпадает со значением аргумента по умолчанию.Кроме того, это еще одно 
		// ограничение на вводимый текст — точка не обязательно обозначает конец.
		// Это может быть часть многоточия, сокращение, разделитель дробной части числа и т.п.
		it1 = next(it2, 1);
		it2 = find(it1, end_it, '.');
	}

	return ret;
}

int main()
{
	// Обратите внимание, что использование istreambuf_iterator может быть быстрее для чтения всего файла за один шаг.

	// Для чтения больших файлов также лучше заранее знать их размер, чтобы зарезервировать место в памяти.
	// Таким образом, буфер не нужно увеличивать, что приводит к частым перераспределениям.
	// См.Также Chapter10 / dupe_compress.cpp, где показан такой пример.

	// говорим cin не пропускать пробельные символы
	cin.unsetf(ios::skipws);
	string content{ istream_iterator<char>{cin}, {} };

	for (const auto& [word_count, sentence]
		: get_sentence_stats(content)) {
		cout << word_count << " words: " << sentence << ".\n";
	}
}