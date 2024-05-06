#include <iostream>
#include <optional>
#include <algorithm>
#include <iterator>
#include <functional>
#include <map>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class trie
{
    map<T, trie> tries;

public:
    template <typename It>
    // it и end_it представляют собой вставляемую последовательность слов
    void insert(It it, It end_it) {
        //прерывание рекурсии
        if (it == end_it) { return; }
        // выполняет поиск первого слова последовательности в поддереве
        // insert(next(it), end_it) перезапуск той же функции для найденного нижнего поддерева, перемещая итератор на одно слово вперед
        tries[*it].insert(next(it), end_it);
    }

    template <typename C>
    void insert(const C& container) {
        insert(begin(container), end(container));
    }

    void insert(const initializer_list<T>& il) {
        insert(begin(il), end(il));
    }

    void print(vector<T>& v) const {
        if (tries.empty()) {
            copy(begin(v), end(v), ostream_iterator<T>{cout, " "});
            cout << '\n';
        }
        for (const auto& p : tries) {
            v.push_back(p.first);
            p.second.print(v);
            v.pop_back();
        }
    }

    void print() const {
        vector<T> v;
        print(v);
    }

    // возвращается std::optional т.к. не факт что такое дерево найдется
    // необязательному экземпляру, имеющему переменную-член с типом trie&, нельзя повторно присвоить значение и поэтому код не скомпилируется. 
    // Реализация ссылки с помощью reference_wrapper приведет к тому, что у вас появится возможность присваивать значения объектам повторно.
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

int main()
{
    trie<string> t;

    t.insert({ "hi", "how", "are", "you" });
    t.insert({ "hi", "i", "am", "great", "thanks" });
    t.insert({ "what", "are", "you", "doing" });
    t.insert({ "i", "am", "watching", "a", "movie" });

    cout << "recorded sentences:\n";
    t.print();

    cout << "\npossible suggestions after \"hi\":\n";

    if (auto st(t.subtrie(initializer_list<string>{"hi"})); st) {
        st->get().print();
    }
}