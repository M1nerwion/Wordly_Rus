#pragma once
#include    <iostream>
#include    <fstream>
#include    <vector>
#include    <string>
#include    <random>
#include    <locale>
#include    <limits>
#define ERASE   L"\x1b[1F\x1b[2K"           // стереть строку после cin
#define BY      L"\x1b[2;30;43m"           // вывод черный текст на желтом фоне
#define BG      L"\x1b[2;30;42m"          // вывод черный текст на зеленом фоне
#define BM      L"\x1b[2;30;45m"          // вывод черный текст на магента фоне
#define BR      L"\x1b[2;30;41m"                 // вывод черный текст на красном фоне
#define BGRAY   L"\x1b[38;5;0m\x1b[48;5;245m"    // черный текст на сером фоне
#define LR      L"\x1b[1;31m"             // вывод красный текст на текущем фоне
#define LM      L"\x1b[1;35m"             // вывод Магента текст на текущем фоне
#define LG      L"\x1b[1;32m"             // вывод Магента текст на текущем фоне
#define RESET   L"\x1b[0m"            // сбросить цвет

extern int n; // количество букв в слове
extern int count_of_attemp; // количество попыток

void read(std::vector<wchar_t>& vec);
void color_processing(std::vector<wchar_t>& vec_user, std::vector<wchar_t>& vec_hidden_word);
long long amount_of_words(std::string file_slov);
std::vector<wchar_t> transform(std::wstring line);
std::vector<wchar_t> choice_of_random_word(std::string file_slov);
bool check_letters(std::vector<wchar_t> line, std::vector<wchar_t> user_word);
bool check_on_word(std::vector<wchar_t> user_word, std::string file_slov);