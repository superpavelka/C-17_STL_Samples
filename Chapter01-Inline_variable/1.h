#pragma once
#include <string>

//inline ����������

class process_monitor
{
	// ���� ��� �� ������� inline �� �� ��������������, �.�.
	// �����(�� C++17) ������ ���� ���������������� ����������� ���� � ������
	public:
		static inline const std::string standart_string { "some static globally available string" };
};
// ���� ��� �� ������� inline, �� ��� ��������� ����� ������ � ��������� cpp ������ �� ��������������
inline process_monitor global_process_monitor;