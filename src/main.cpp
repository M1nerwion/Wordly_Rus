#include "functions.h"

extern int n = 5; // количество букв в слове
extern int count_of_attemp = 0; // количество попыток

int main(){
	srand(time(0));
	setlocale(LC_ALL, "ru_RU.UTF-8");
	std::ios_base::sync_with_stdio(false); // отключение синхронизации потоков, чтобы на линуксе не ломался вывод
	
	//std::string file_slov = "fiveletters.txt";
	std::string file_slov = "src/g.txt";
	std::vector<char> answer_word = choice_of_random_word(file_slov);
	std::cout << "   ";
	for (auto p : answer_word) { std::cout << p; }
	std::cout << '\n';

	std::vector<char> user_word(n+1); // вектор всегда будет больше 
	while (count_of_attemp < 6) {
		read(user_word);
		if (check_letters(answer_word, user_word)) {
			color_processing(user_word, answer_word);
			break;
		}
		else if (check_on_word(user_word, file_slov)) {
			color_processing(user_word, answer_word);
			++count_of_attemp;
			continue;
		}
		else {
			std::cout << BR << "Ошибка, такого слова не существует" << RESET << "\nНажмите ENTER, чтобы повторить попытку ..." << std::endl;
			std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin.get(); // ожидание нажатия
            std::cout << "\x1b[4F\x1b[0J"; // очистка консоли от длинного слова и предкпреждения
			std::cin.ignore(std::cin.rdbuf()->in_avail());
		}
	}
	if (count_of_attemp == 6) {
		std::cout << "ДОЛБОЕБ\n";
	}
}