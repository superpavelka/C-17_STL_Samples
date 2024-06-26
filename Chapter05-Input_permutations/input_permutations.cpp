#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

/*
std::next_permutation алгоритм делающий лексикографические перестановки(т.к. лексикографические то вектор надо сначала отсортировать)
Алгоритм, с помощью которого функция std::next_permutation находит следующий лексикографический порядок элементов, работает таким образом.
1. Найдем самое большое значение индекса i, для которого выполняется условие v[i - 1] < v[i].Если такого значения нет, то вернем значение false.
2. Теперь найдем самое большое значение индекса j, для которого выполняются условия j >= i и v[j] > v[i - 1].

3. Меняем местами элементы на позициях j и i - 1.
4. Изменим порядок элементов, находящихся между позицией i и концом диапазона данных, на противоположный.
5. Вернем значение true.
Отдельные порядки перестановки, которые мы получим в результате вызова этой функции, всегда будут появляться в одинаковой последовательности. 
Чтобы найти все возможные перестановки, мы поначалу отсортировали массив. Это было сделано потому, что если бы ввели строку "c b a", например, 
то алгоритм завершил бы работу немедленно, так как данная строка представляет собой последний возможный лексикографический порядок элементов.
*/
using namespace std;

int main()
{
    vector<string> v{ istream_iterator<string>{cin}, {} };
    sort(begin(v), end(v));

    do {
        copy(begin(v), end(v), ostream_iterator<string>{cout, ", "});
        cout << '\n';
    } while (next_permutation(begin(v), end(v)));
}