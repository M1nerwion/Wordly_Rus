#include "functions.h"

int n = 5; // количество букв в слове
int count_of_attemp = 0; // количество попыток

int main(){
	srand(time(0));
	std::locale::global(std::locale("ru_RU.UTF-8"));
	//std::wcout.setf(std::ios_base::unitbuf);
	//std::wcin.ignore(std::wcin.rdbuf()->in_avail());
	//setlocale(LC_ALL, "ru_RU.UTF-8");
	std::ios_base::sync_with_stdio(false); // отключение синхронизации потоков, чтобы на линуксе не ломался вывод
	std::wcout << L"\n  Добро пожаловать в WORDLE на РУССКОМ!\n\n";
	std::string file_slov = "src/fiveletters.txt";
	//std::string file_slov = "src/g.txt";
	std::vector<wchar_t> answer_word = choice_of_random_word(file_slov);
	//std::wcout << "   ";
	//for (auto p : answer_word) { std::wcout << p; }
	//std::wcout << '\n';

	std::vector<wchar_t> user_word(n+1); // вектор всегда будет больше 
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
			std::wcout << BR << L"Ошибка, такого слова не существует" << RESET << L"\nНажмите ENTER, чтобы повторить попытку ..." << std::endl;
			std::wcin.clear();
			std::wcin.ignore(std::wcin.rdbuf()->in_avail());
            while(std::wcin.get() != L'\n') {} // ожидание нажатия
			std::wcin.clear();
			std::wcin.ignore(std::wcin.rdbuf()->in_avail());
			//std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
            std::wcout << L"\x1b[4F\x1b[0J"; // очистка консоли от длинного слова и предкпреждения
			//std::wcin.ignore(std::wcin.rdbuf()->in_avail());
		}
	}
	if (count_of_attemp == 6) {
		//std::wcout << L"ДОЛБОЕБ\n" << BG;
		for (auto p : answer_word) { std::wcout << p; } // вывод загаданного слова
		std::wcout << RESET << L'\n';
	}
}