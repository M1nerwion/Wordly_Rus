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
extern std::wstring alf;
extern std::vector<short> alf_vec;

void read(std::vector<wchar_t>& vec);//Функция считывания слова введеног пользователем
void color_processing(std::vector<wchar_t>& vec_user, std::vector<wchar_t>& vec_hidden_word);//Процедура вывода введеных слова пользователем и окрашевание его буквы в нужные цвета
long long amount_of_words(std::string file_slov); //Подсчет количесвтва слов в файле
std::vector<wchar_t> transform(std::wstring line);//Перевод wstring в вектор wchar_t
std::vector<wchar_t> choice_of_random_word(std::string file_slov);//Выбор случайног ослова из списка
bool check_letters(std::vector<wchar_t> line, std::vector<wchar_t> user_word);//Проверка на совпадение двух слов
bool check_on_word(std::vector<wchar_t> user_word, std::string file_slov);//Проверка на существование такого слова в списке

int pos_in_alf_wchar(wchar_t liter);//Возвращает позицию данной буквы в алфавите
bool ravenstvo_liter(wchar_t a, wchar_t b);//Проверка на равенство двух букв
bool availability_of_liter_in_word(wchar_t liter, std::vector<wchar_t> answer_word);//Проверка на наличие данной буквы в слове
void transformation_of_condition_of_alf_vec(std::vector<wchar_t> user_word, std::vector<wchar_t> answer_word, std::vector<wchar_t> &alf_vec);//Преобразовние вектора alf_vec после ввода пользователем слова
void transformation_of_alf();//Раскраска алфавита по уже преобразованному вектору alf_vec
void color_alf(std::vector<wchar_t> user_word, std::vector<wchar_t> answer_word, std::vector<short>& alf_vec);//ОФункция, расскрашивания алфавита