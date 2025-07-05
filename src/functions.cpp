#include "functions.h"

extern int n; // ���������� ���� � �����
extern int count_of_attemp; // ���������� �������

void read(std::vector<char>& vec) // ������ ����� ������������
{
	bool flag;
	std::cout << (count_of_attemp + 1) << "  ";
	do
	{
		flag = false;
		for (auto& i : vec) { i = '\0'; } // ��������� �������
		for (size_t i = 0; i < 5; ++i) // ���������� ����� �� ������ �� �������
		{
			std::cin.get(vec[i]);
			if (vec[i] == '\n') // ���� �����-�� �� �������� ������� ���������� '\n', ������ ����� ��������
			{
				std::cout << BR << "������, ����� ������ �������� �� 5 ����" << RESET << "\n������� ENTER, ����� ��������� ������� ..." << std::endl; // ����� ��������������
				std::cin.ignore(std::cin.rdbuf()->in_avail()); // ������� ������ �������� ������
				std::cin.get(); // �������� ������� enter
				std::cout << "\x1b[4F\x1b[0J" << count_of_attemp + 1 << "  "; // ������� ������� �������������� � ��������� �����
				flag = true;
				break;
			}
		}

		if (vec[4] != '\0' && vec[4] != '\n')
		{
			std::cin.get(vec[5]);
			if ((vec[5] != '\n') && flag == false) // ����  ������������ ���� ������ 5 ����, ������ ������������
			{
				std::cout << BR << "������, ����� ������ �������� �� 5 ����" << RESET << "\n������� ENTER, ����� ��������� ������� ..." << std::endl; // ����� ��������������
				std::cin.ignore(std::cin.rdbuf()->in_avail()); // ������� ������
				std::cin.get(); // �������� �������
				std::cout << "\x1b[4F\x1b[0J" << count_of_attemp + 1 << "  "; // ������� ������� �� �������� ����� � ��������������
				flag = true;
			}
		}
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	} while (flag); // ���������� ����, ���� �� ����� ������� ����� ���������� �����
} // read

void color_processing(std::vector<char>& vec_user, std::vector<char>& vec_hidden_word) // ������� ������� � ������ ����
{
	std::cout << ERASE << (count_of_attemp + 1) << "  ";
	for (size_t i = 0; i < 5; ++i) // ������ ���� ��� ������ ���� �� ���������� �����
	{
		bool flag = false; // ���� ��� ��������, �������� �� ��� �����

		if (vec_user[i] == vec_hidden_word[i]) // ���� ����� �� � ���������� ����� ���� � �� ��� �� �������, ������ ���� � �������
		{
			flag = true;
			std::cout << BG << vec_user[i] << RESET;
			continue;
		}
		else // ���� ����� �� �� ��� �� �������, ������� ����������� ����� � ���������� �����
		{
			for (size_t j = 0; j < 5; ++j) // ������� ���� ��� ������ �� ����������� �����
			{
				if (vec_user[i] == vec_hidden_word[j])
				{
					flag = true;
					std::cout << BY << vec_user[i] << RESET;
					break;
				}
			}
		}
		if (!flag) std::cout << BGRAY << vec_user[i] << RESET; // ���� ����� ���, ������� ��� ���������
	}
	std::cout << std::endl;
} // color_processing

///////////////////////////////////////////////////////////////////////
long long amount_of_words(std::string file_slov) {//������� ���������� ���� � �����
	long long count = 0;//������ �������
	std::string line;//�����, ������� ����� ������������(����� � ����� �������� ���� � ������)
	std::ifstream fin(file_slov);//�������� ���� ��� ������
	while (fin.peek() != EOF) {//������� �������� �� ����� ������� ���������� ����� 
		getline(fin, line);
		++count;
	}
	fin.close();//��������� �����
	return count;//���������� ���������� �����
}

std::vector<char> transform(std::string line) {//��������� string � ������ char
	std::vector<char> vec_rand_word(n);//������� ������ char
	for (int i = 0; i < n; ++i) {//�������� �� ������ � ����������� ����������� ������� �������� ������� char ������������� ������� ������
		vec_rand_word[i] = line[i];
	}
	return vec_rand_word;//���������� ������� ������
}

std::vector<char> choice_of_random_word(std::string file_slov) {//������� �������� ��������������� ������� �����
	std::string line;//�����, ������� ����� ������������(����� � ����� �������� ���� � ������)
	long long count = amount_of_words(file_slov); //�������� ���������� ����� � �����
	std::random_device rd;   // non-deterministic generator            ����� ���� �� 4 ������ ��� ��������� ����������� �����
	std::mt19937 gen(rd());  // to seed mersenne twister.
	std::uniform_int_distribution<> dist(1, count);
	long long rand_number = dist(gen);//���������� ��������������� �����
	//std::cout << rand_number << "\n";��� �������

	std::ifstream fin(file_slov); //�������� ���� ��� ������
	for (int i = 0; i != rand_number; ++i) {//���������� �� ����� ������ rand_number �����, �� ���� ������� ������ ��� �� ����� ������
		getline(fin, line);
	}
	fin.close();

	return transform(line);//����������� string � ������ char � ���������� � ���������� ������ char'��
}

bool check_letters(std::vector<char> line, std::vector<char> user_word) {//������� ��������� ��� ������� char �� ���������� �����������
	for (size_t i = 0; i < n; ++i) {//���� �� �������
		if (line[i] != user_word[i]) {//���������� � ���� �� �����, �� ���������� false
			return false;
		}
	}
	return true;
}

bool check_on_word(std::vector<char> user_word, std::string file_slov) {//������� ������� ��������� ������������� �����
	bool condition = false;
	std::string line;//�����, ������� ����� ������������(����� � ����� �������� ���� � ������)
	std::ifstream fin(file_slov);//�������� ���� ��� ������
	while (fin.peek() != EOF) {//������ �������� �� ����� 
		getline(fin, line);//�������� ����� � ����� ������
		//std::cout << line << "\n";//��� �������
		if (check_letters(transform(line), user_word)) {//���� ����� ���������, �� ���������� true, ����� ��������� ���������
			fin.close();
			condition = true;
		}
	}
	fin.close();//��������� �����
	return condition;//���������� ��������� ��������
}