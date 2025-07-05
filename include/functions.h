#pragma once
#include		<iostream>
#include		<fstream>
#include		<vector>
#include		<string>
#include		<random>
#define ERASE   "\x1b[1F\x1b[2K"   				// ������� ������ ����� cin
#define BY      "\x1b[2;30;43m"   				// ����� ������ ����� �� ������ ����
#define BG      "\x1b[2;30;42m"  				// ����� ������ ����� �� ������� ����
#define BR      "\x1b[2;30;41m"                 // ����� ������ ����� �� ������� ����
#define BGRAY   "\x1b[38;5;0m\x1b[48;5;245m"    // ������ ����� �� ����� ����
#define RESET   "\x1b[0m"						// �������� ����

//extern int n; // ���������� ���� � �����
//extern int count_of_attemp; // ���������� �������

void read(std::vector<char>& vec);
void color_processing(std::vector<char>& vec_user, std::vector<char>& vec_hidden_word);
long long amount_of_words(std::string file_slov);
std::vector<char> transform(std::string line);
std::vector<char> choice_of_random_word(std::string file_slov);
bool check_letters(std::vector<char> line, std::vector<char> user_word);
bool check_on_word(std::vector<char> user_word, std::string file_slov);