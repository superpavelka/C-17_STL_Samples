#include <iostream>
#include <queue>
#include <tuple>
#include <string>

// Реализация списка личных дел через очередь с приоритетом

int main()
{
	using item_type = std::pair<int, std::string>;
	// Чтобы приоритет работал автоматически, он должен быть первым членом пары
	std::initializer_list<item_type> il
	{
		{1, "dishes"},
		{0, "watch tv"},
		{2, "do homework"},
		{0, "read comics"},
	};

	std::priority_queue<item_type> q;

	for (const auto& p : il) 
	{
		q.push(p);
	}

	while (!q.empty()) 
	{
		// top возвращает ссылку на первый в очереди на выход, pop выталкивает его
		std::cout << q.top().first << ": " << q.top().second << '\n';
		q.pop();
	}
	std::cout << '\n';
}