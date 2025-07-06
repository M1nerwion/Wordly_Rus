#pragma once
#include		<iostream>
#include		<fstream>
#include		<vector>
#include		<string>
#include		<random>
#include        <locale>
#define ERASE   L"\x1b[1F\x1b[2K"   				// ������� ������ ����� cin
#define BY      L"\x1b[2;30;43m"   				// ����� ������ ����� �� ������ ����
#define BG      L"\x1b[2;30;42m"  				// ����� ������ ����� �� ������� ����
#define BR      L"\x1b[2;30;41m"                 // ����� ������ ����� �� ������� ����
#define BGRAY   L"\x1b[38;5;0m\x1b[48;5;245m"    // ������ ����� �� ����� ����
#define RESET   L"\x1b[0m"						// �������� ����

//extern int n; // ���������� ���� � �����
//extern int count_of_attemp; // ���������� �������

void read(std::vector<wchar_t>& vec);
void color_processing(std::vector<wchar_t>& vec_user, std::vector<wchar_t>& vec_hidden_word);
long long amount_of_words(std::string file_slov);
std::vector<wchar_t> transform(std::wstring line);
std::vector<wchar_t> choice_of_random_word(std::string file_slov);
bool check_letters(std::vector<wchar_t> line, std::vector<wchar_t> user_word);
bool check_on_word(std::vector<wchar_t> user_word, std::string file_slov);