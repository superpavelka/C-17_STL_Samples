#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

// Счетчик слов в строке с реализацией на std::map

using namespace std;

// Функция для обрезки ненужных символов пунктуации
string filter_punctuation(const string& s)
{
	const char* forbidden{ ".,:; " };
	const auto idx_start(s.find_first_not_of(forbidden));
	const auto idx_end(s.find_last_not_of(forbidden));

	return s.substr(idx_start, idx_end - idx_start + 1);
}

int main()
{
	map<string, size_t> words;
	int max_word_len{ 0 };

	string s;
	// преобразование cin в string обрезает лишние пробелы
	while (cin >> s) {
		auto filtered(filter_punctuation(s));
		max_word_len = max<int>(max_word_len, filtered.length());
		++words[filtered];
	}

	// так как map хранит данные в алфавитном порядке, то используем вектор для вывода в порядке частоты встречаемости
	
	vector<pair<string, size_t>> word_counts;
	word_counts.reserve(words.size());
	//std::move выгодно отличается от других: та часть строки, которая находится в куче, не будет продублирована, 
	// а только перемещена из ассоциативного массива в вектор. Это позволит избежать создания множества копий.
	move(begin(words), end(words), back_inserter(word_counts));

	// используем лямбду фильтровки по вторым значениям пары для сортировки вектора
	sort(begin(word_counts), end(word_counts),
		[](const auto& a, const auto& b) { return a.second > b.second; });

	cout << "# " << setw(max_word_len) << "<WORD>" << " #<COUNT>\n";
	for (const auto& [word, count] : word_counts) {
		cout << setw(max_word_len + 2) << word << " #" << count << '\n';
	}
}