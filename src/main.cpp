#include		<iostream>
#include		<fstream>
#include		<vector>
#include		<string>
#include		<random>
#include        <chrono>
#include        <thread>
#include        <limits>
#define ERASE   "\x1b[1F\x1b[2K"   // стереть строку после cin
#define BY      "\x1b[2;30;43m"   // вывод черный текст на желтом фоне
#define BG      "\x1b[2;30;42m"  // вывод черный текст на зеленом фоне
#define RESET   "\x1b[0m"       // сбросить цвет

int n = 5;

void read(std::vector<char>& vec) // чтение слова пользователя
{
	for (size_t i = 0; i < 5; ++i)
	{
		std::cin.get(vec[i]);
	}
}

void color_processing(std::vector<char>& vec_user, std::vector<char>& vec_hidden_word) // функция окраски и вывода слов
{
	std::cout << ERASE;
	for (size_t i = 0; i < 5; ++i) // первый цикл для обхода букв по введенному слову
	{
		bool flag = false; // флаг для проверки, выведено ли уже слово

		if (vec_user[i] == vec_hidden_word[i]) // если буква на в загаданном слове есть и на той же позиции, меняем флаг и выводим
		{
			flag = true;
			std::cout << BG << vec_user[i] << RESET;
			continue;
		}
		else // если буква не на той же позиции, обходим остальльные буквы в загаданном слове
		{
			for (size_t j = 0; j < 5; ++j) // воторой цикл для обхода по загаданному слову
			{
				if (vec_user[i] == vec_hidden_word[j])
				{
					flag = true;
					std::cout << BY << vec_user[i] << RESET;
					break;
				}
			}
		}
		if (!flag) std::cout << vec_user[i]; // если буквы нет, выводим без подсветки
	}
	std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////
long long amount_of_words(std::string file_slov) {//Находит количество слов в файле
	long long count = 0;//Задаем счетчик
	std::string line;//Слова, которые будут перебираться(Слова в файле записаны одно в строку)
	std::ifstream fin(file_slov);//Окрываем файл для чтения
	while (fin.peek() != EOF) {//Простым проходом по файлу считаем количесвто строк 
		getline(fin, line);
		count++;
	}
	fin.close();//Закрываем поток
	return count;//Возвращаем количество строк
}

std::vector<char> transform(std::string line) {//Переводит string в вектор char
	std::vector<char> vec_rand_word(n);//Создаем вектор char
	for (int i = 0; i < n; i++) {//Проходим по строке и посимвольно присваиваем каждому элементу вектора char соотвествующй элемент стркои
		vec_rand_word[i] = line[i];
	}
	return vec_rand_word;//возвращаем готовый вектор
}

std::vector<char> choice_of_random_word(std::string file_slov) {//Функция выбиарет псевдослучайным образом слово

	std::string line;//Слова, которые будут перебираться(Слова в файле записаны одно в строку)
	long long count = amount_of_words(file_slov); //Получаем количество строк в файле
	std::random_device rd;   // non-deterministic generator            Кусок кода на 4 строки для получения рангдомного числа
	std::mt19937 gen(rd());  // to seed mersenne twister.
	std::uniform_int_distribution<> dist(1, count);
	long long rand_number = dist(gen);//Генерируем псевдослучайное число
	//std::cout << rand_number << "\n";Для отладки

	std::ifstream fin(file_slov); //Окрываем файл для чтения
	for (int i = 0; i != rand_number; i++) {//Проходимся по файлу считая rand_number строк, то есть находим нужную нам по счету строку
		getline(fin, line);
	}
	fin.close();

	return transform(line);//Преобразуем string в вектор char и возвращаем в полученный вектор char'ов
}

bool check_letters(std::vector<char> line, std::vector<char> user_word) {//Функция проверяет два массива char на равеноство посимвольно
	for (int i = 0; i < n; i++) {//Идем по массиву
		if (line[i] != user_word[i]) {//Срваниваем и если не равны, то возвращаем false
			return false;
		}
	}
	return true;
	//return false;
}

bool check_on_word(std::vector<char> user_word, std::string file_slov) {//Функция которая проверяет сущесвтование слова
	bool condition = false;
	std::string line;//Слова, которые будут перебираться(Слова в файле записаны одно в строку)
	std::ifstream fin(file_slov);//Окрываем файл для чтения
	while (fin.peek() != EOF) {//Просто проходом по файлу 
		getline(fin, line);//Считывем слово с новой строки
		//std::cout << line << "\n";//Для отладки
		if (check_letters(transform(line), user_word)) {//Если слова совпадают, то возвращаем true, иначе проверяем следующее
			fin.close();
			condition = true;
		}
	}
	fin.close();//Закрываем поток
	/*if (!condition) std::cout << "Ошибка, такого слова не существует\n";*/
	return condition;//Возвращаем состояние проверки
}

bool check_to_right_answer(std::vector<char> answer_word, std::vector<char> user_word, std::string file_slov) {//Функция проверяет слово соотвествие отгаданному и на сущесвтование такого слова в целом
	//bool condition = check_letters(answer_word, user_word);//Проверяем, является ли слово, предложенное пользователем отгаданным
	//if (condition) {//если отгадал, то true
	//	return condition;
	//}
	////else {//Если нет, то проверяем, есть ли такое слово в целом
	////	return check_on_word(user_word, file_slov);
	////}
	return check_letters(answer_word, user_word);
}

int main(){
	srand(time(0));
	setlocale(LC_ALL, "RUS");

	int count_of_attemp = 0;
	bool gavno = false;
	
	//std::string file_slov = "fiveletters.txt";
	std::string file_slov = "g.txt";

	std::vector<char> answer_word = choice_of_random_word(file_slov);
	for (auto p : answer_word) { std::cout << p; }
	std::cout << '\n';

	std::vector<char> user_word(5);
	while (count_of_attemp < 6) {
		read(user_word);
		std::cin.clear(); // сброс ошибок и флагов потока
		std::cin.ignore(std::cin.rdbuf()->in_avail()); // очистка всего буфера
		if (check_to_right_answer(answer_word, user_word, file_slov)) {
			color_processing(user_word, answer_word);
			break;
		}
		else if (check_on_word(user_word, file_slov)) {
			color_processing(user_word, answer_word);
			count_of_attemp++;
			continue;
		}
		else {
			std::cout << "Ошибка, такого слова не существует\n";
		}
	}
	if (count_of_attemp == 6) {
		std::cout << "ДОЛБОЕБ\n";
	}
	


	//std::string slovo = "камни";
	//std::cout<<check_to_right_answer(answer_word, transform(slovo), file_slov);
}
