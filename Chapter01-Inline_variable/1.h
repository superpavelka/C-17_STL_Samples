#pragma once
#include <string>

//inline переменные

class process_monitor
{
	// Если тут не указать inline то не скомпилируется, т.к.
	// ранее(до C++17) нельзя было инициализировать статический член в классе
	public:
		static inline const std::string standart_string { "some static globally available string" };
};
// если тут не указать inline, то при включении этого хедера в несколько cpp файлов не скомпилируется
inline process_monitor global_process_monitor;