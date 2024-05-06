#include <iostream>
#include <optional>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <fstream>

// Генератор поисковых подсказок с помощью префиксных деревьев

using namespace std;

template <typename T>
class trie
{
    map<T, trie> tries;

public:
    template <typename It>
    void insert(It it, It end_it) {
        if (it == end_it) { return; }
        tries[*it].insert(next(it), end_it);
    }

    template <typename C>
    void insert(const C& container) {
        insert(begin(container), end(container));
    }

    void insert(const initializer_list<T>& il) {
        insert(begin(il), end(il));
    }

    void print(list<T>& l) const {
        if (tries.empty()) {
            copy(begin(l), end(l), ostream_iterator<T>{cout, " "});
            cout << '\n';
        }
        for (const auto& p : tries) {
            l.push_back(p.first);
            p.second.print(l);
            l.pop_back();
        }
    }

    void print() const {
        list<T> l;
        print(l);
    }

    template <typename It>
    optional<reference_wrapper<const trie>> subtrie(It it, It end_it) const {
        if (it == end_it) { return ref(*this); }

        auto found(tries.find(*it));
        if (found == end(tries)) { return {}; }

        return found->second.subtrie(next(it), end_it);
    }

    template <typename C>
    auto subtrie(const C& c) const { return subtrie(begin(c), end(c)); }
};


static void prompt()
{
    cout << "Next input please:\n > ";
}

int main()
{
    trie<string> t;

    // Цикл заполняет строку line содержимым текстового файла строка за строкой.Затем мы копируем строку в объект istringstream.
    // Из этого объекта можно создать итератор istream_iterator, который нам еще пригодится, поскольку наше дерево принимает не 
    // только экземпляр контейнера для поиска поддеревьев, но и итераторы.Таким образом, нет нужды создавать вектор или список слов 
    // и можно непосредственно принять строку.Избежать последней части ненужных выделений памяти позволит перемещение содержимого строки в iss.
    // К сожалению, объект типа std::istringstream не предоставляет конструктор, который принимает перемещаемые значения типа std::string. 
    // Тем не менее он скопирует свою входную строку.
    fstream infile{ "db.txt" };
    for (string line; getline(infile, line);) {
        istringstream iss{ move(line) };
        t.insert(istream_iterator<string>{iss}, {});
    }


    prompt();

    // При чтении пользовательских входных данных, которые нужно найти в дереве, мы применяем точно такую же стратегию, 
    // но не задействуем файловый поток ввода.Вместо этого мы прибегаем к std::cin.В нашем случае это сработает аналогично, 
    // поскольку trie::subtrie работает для итераторов точно так же, как и trie::insert.
    for (string line; getline(cin, line);) {
        istringstream iss{ move(line) };

        if (auto st(t.subtrie(istream_iterator<string>{iss}, {})); st) {
            cout << "Suggestions:\n";
            st->get().print();
        }
        else {
            cout << "No suggestions found.\n";
        }
        cout << "----------------\n";
        prompt();
    }
}