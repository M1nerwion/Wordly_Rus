#include "functions.h"

int n = 5; // количество букв в слове
int count_of_attemp = 0; // количество попыток

int main(){
	srand(time(0));//Для того, чтобы каждый раз было разное семечко для генерации ПСЧ
	std::locale::global(std::locale("ru_RU.UTF-8"));//Веселуха с кодировками
	//std::wcout.setf(std::ios_base::unitbuf);
	//std::wcin.ignore(std::wcin.rdbuf()->in_avail());
	//setlocale(LC_ALL, "ru_RU.UTF-8");
	std::ios_base::sync_with_stdio(false); // отключение синхронизации потоков, чтобы на линуксе не ломался вывод

	//Вывод приветствия
	std::wcout  << "  ____                     __   \n"
				<< " |  _ \\                    \\_\\  \n"
				<< " | |_) |   ___    _ __    / _ \\    ____   _   _ \n"
				<< " |  _ <   / _ \\  | '_ \\  | | | |  / _  | | | | |\n"
				<< " | |_) | | (_) | | |_) | | |_| | / / | | | |_| |\n"
				<< " |____/   \\___/  | .__/   \\___/ /_/  |_|  \\__,_|\n"
				<< "                 | |    \n"
				<< "                 |_|     \n";
	std::wcout << L"\n  Добро пожаловать в WORDLE на РУССКОМ!\n\n";

	std::string file_slov = "src/fiveletters.txt";//Выбор файла
	//std::string file_slov = "src/g.txt";

	std::vector<wchar_t> answer_word = choice_of_random_word(file_slov);
	//std::wcout << "   ";//Для отладки вывод загаданного слова в начале
	//for (auto p : answer_word) { std::wcout << p; }
	//std::wcout << '\n';

	std::vector<wchar_t> user_word(n+1); // вектор всегда будет больше 
	while (count_of_attemp < 6) {//Оснвоной цикл программы
		read(user_word);//Считываем слово, введенное пользователем
		if (check_letters(answer_word, user_word)) {//Проверка на совпадение с отгаданным
			color_processing(user_word, answer_word);//Процесс окрашивания клеточек
			break;
		}
		else if (check_on_word(user_word, file_slov)) {//Проверка на существование данного слова
			color_processing(user_word, answer_word);//Процесс окрашивания клеточек
			++count_of_attemp;//Увеличиваем счетчик принятых слов(попыток)
			continue;
		}
		else {//Случай, если слова не существует
			std::wcout << BR << L"Ошибка, такого слова не существует" << RESET << L"\nНажмите ENTER, чтобы повторить попытку ..." << std::endl;//Вывод предупреждения
			std::wcin.clear();//Очистка буфера
			std::wcin.ignore(std::wcin.rdbuf()->in_avail());
            while(std::wcin.get() != L'\n') {} // ожидание нажатия
			std::wcin.clear();//Очистка буфера
			std::wcin.ignore(std::wcin.rdbuf()->in_avail());
			//std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
            std::wcout << L"\x1b[4F\x1b[0J"; // очистка консоли от длинного слова и предупреждения
		}
	}
	if (count_of_attemp == 6) {//Случай, когда израсходованы все попытки
		//std::wcout << L"ДОЛБОЕБ\n" << BG;
		//std::wcout << L'\n' << L"  " << BR << L"Поражение!\n" << RESET;//В случае если хотим фон сделать цветным
		std::wcout << L'\n' << L"  " << LR << L"Поражение!\n" << RESET;//В случае если хотим текст сделать цветным
		//std::wcout << RESET << L"  " << BM << L"Загаданное слово: " << RESET;//В случае если хотим фон сделать цветным
		std::wcout << RESET << L"  " << LM << L"Загаданное слово: " << RESET;//В случае если хотим текст сделать цветным
		for (size_t i = 0; i < n; i++) { std::wcout << LG << answer_word[i] << RESET; }// вывод загаданного слова
		std::wcout << RESET << L" " << L'\n' << L'\n' << RESET;//перевод на новую строку и сброс фильтров
	}
}