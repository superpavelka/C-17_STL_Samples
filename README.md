### Примеры из книги "C++17 STL Стандартная библиотека шаблонов" Яцек Галовиц
### с моими дополнениями и комментариями на русском
### Взято отсюда https://github.com/PacktPublishing/Cpp17-STL-Cookbook

### 1. Новые возможности C++17
### 1.1 [Структурированные привязки для распаковки набора возвращаемых значений](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter01-Structured_bindings/1.cpp)
### 1.2 [Ограничение области видимости переменных в выражениях if и switch](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter01-if_switch_initializer/1.cpp)
### 1.3 [Новые правила инициализатора с фигурными скобками](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter01-New_iniatialiazer_rules/1.cpp)
### 1.4 [Автоматический вывод полученного типа класса шаблона в конструкторе(CTAD)](https://github.com/superpavelka/C-17_STL_Samples/tree/main/Chapter01-Template_class_type_deduction/1.cpp)
### 1.5 [Упрощение выбора специализации шаблона во время компиляции if constexpr](https://github.com/superpavelka/C-17_STL_Samples/tree/main/Chapter01-if_constexpr/1.cpp)
### 1.6 [Встраиваемые(inline) переменные](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter01-Inline_variable/1.h)
### 1.7 [Выражения свертки](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter01-Fold_expressions/1.cpp)
### 2. Контейнеры STL
### 2.1 [Идиома erase-remove для std::vector](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Erase_remove_idiom/Erase-remove-idiom.cpp)
### 2.2 [Удаление элементов из неотсортированного объекта класса std::vector за время O(1)(std::move и pop_back)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Quick_delete_from_unordered_vector_O(1)/Quick_delete_from_unordered_vector_O(1).cpp)
### 2.3 [Доступ к экземплярам std::vector быстрым или безопасным способом([] или at)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Vector_access_fast_or_safe/Vector_access_fast_or_safe.cpp)
### 2.4 [Сохранение сортировки std::vector при вставке элементов(std::lower_bound)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Keep_vector_sorted/Keep_vector_sorted.cpp)
### 2.5 [Вставка в std::map без лишнего создания объекта при наличии ключа(try_emplace)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Efficient_insert_or_reassign_to_map/Chapter02-Efficient_insert_or_reassign_to_map.cpp)
### 2.6 [Новая семантика подсказок для вставки элементов в std::map за амортизированное O(1)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Map_insertion_hint/Map_insertion_hint.cpp)
### 2.7 [Эффективное изменение ключей std::map(без перевыделения памяти, extract, новая перегруженная версия insert для ключей)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Mapnode_key_modification/Mapnode_key_modification.cpp)
### 2.8 [Применение unordered_map для пользовательских типов ключей (пользовательская версия std::hash)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Custom_type_unordered_map/Custom_type_unordered_map.cpp)
### 2.9 [Пример использования std::set для фильтрации уникальных элементов в потоке ввода(пример вывода std::copy + std::inserter, пример ввода std::istream_iterator)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Filter_unique_user_input/Filter_unique_user_input.cpp)
### 2.10 [Реализация ОПН калькулятора (реализация через std::stack, ввод через std::stringstream)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Rpn_calculator_impl_with_stack/Rpn_calculator_impl_with_stack.cpp)
### 2.11 [Подсчет частоты встречаемости слов через std::map (фильтр от ненужных символов с помощью std::find_first_not_of, std::find_last_not_of, вывод в порядке частоты реализован через std::vector, std::move, std::back_inserter)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Word_frequency_counter_impl_map/Word_frequency_counter_impl_map.cpp)
### 2.12 [Разбиение текста на предложения, подсчет количества слов в предложениях (реализация через std::multimap, итерация через std::next, std::distance, std::find, вставка в контейнер через std::emplace, std::move)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Sentence_length_multimap/Sentence_length_multimap.cpp)
### 2.13 [Реализация списка личных дел через std::priority_queue](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter02-Personal_organiser_priority_queue/Personal_organiser_priority_queue.cpp)
### 3. Итераторы
### 3.1 [Создание собственного итерабельного диапазона данных](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter03-Own_iterable_range/Own_iterable_range.cpp)
### 3.2 [Реализация совместимости собственного итератора с категориями итераторов STL (std::iterator_traits)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter03-Making_iterators_stl_compatible/Making_iterators_stl_compatible.cpp)
### 3.3 [Использование оболочек итераторов для заполнения обобщенных структур данных(ввод std::istream_iterator, заполнение с помощью std::copy + std::insert_iterator, std::back_insert_iterator, std::front_insert_iterator, вывод с помощью std::copy + std::ostream_iterator)](https://github.com/superpavelka/C-17_STL_Samples/blob/main/Chapter03-Iterator_wrapper/Iterator_wrapper.cpp)
