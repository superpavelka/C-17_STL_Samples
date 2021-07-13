#include <string>
#include <stdio.h>
// ������ �����
// �������� ��� � � 2.cpp ������ ��� ���������� ���������� ��������� inline 
#include "1.h"
struct C {
#if 1
	static const inline std::string N{ "abc" };
};
#else
	static std::string& N() {
		static std::string s{ "abc" };
		return s;
	}
};
#endif

int main()
{
	printf("%s\n", C::N.c_str());
}