#include "functions.h"

//extern int n; // количество букв в слове
//extern int count_of_attemp; // количество попыток
//extern std::wstring alf;
//extern std::vector<short> alf_vec;

void read(std::vector<wchar_t>& vec) // чтение слова пользователя
{
	bool flag;
	std::wcout << (count_of_attemp + 1) << "  ";
	do
	{
		flag = false;
		for (auto& i : vec) { i = L'\0'; } // обнуление вектора
		for (size_t i = 0; i < 5; ++i) // считывание слова по буквам из консоли
		{
			std::wcin.get(vec[i]);
			if (vec[i] == 10) // если какой-то из элментов вектора заполнился '\n', значит слово короткое
			{
				std::wcout << BR << L"Ошибка, слово должно состоять из 5 букв" << RESET << L"\nНажмите ENTER, чтобы повторить попытку ..." << std::endl; // вывод предупреждения
				std::wcin.clear();
				std::wcin.ignore(std::wcin.rdbuf()->in_avail()); // очистка буфера входного потока
				while(std::wcin.get() != L'\n') {} // ожидание нажатия
				std::wcin.clear();
				std::wcin.ignore(std::wcin.rdbuf()->in_avail());
				std::wcout << L"\x1b[4F\x1b[0J" << count_of_attemp + 1 << L"  "; // стираем надписи предупреждения и введенное слово
				flag = true;
				break;
			}
		}

		if (vec[4] != L'\0' && vec[4] != 10)
		{
			std::wcin.get(vec[5]);
			if ((vec[5] != 10) && flag == false) // если  пользователь ввел больше 5 букв, должен перепечатать
			{
				std::wcout << BR << L"Ошибка, слово должно состоять из 5 букв" << RESET << L"\nНажмите ENTER, чтобы повторить попытку ..." << std::endl; // вывод предупреждения
				std::wcin.clear();
				std::wcin.ignore(std::wcin.rdbuf()->in_avail()); // очистка буфера
				while(std::wcin.get() != L'\n') {} // ожидание нажатия
				std::wcin.clear();
				std::wcin.ignore(std::wcin.rdbuf()->in_avail());
				std::wcout << L"\x1b[4F\x1b[0J" << count_of_attemp + 1 << L"  "; // очистка консоли от длинного слова и предупреждения
				flag = true;
			}
		}
		std::wcin.clear();
		std::wcin.ignore(std::cin.rdbuf()->in_avail());
	} while (flag); // продолжаем цикл, пока не будет введено слово нормальной длины
} // read

void color_processing(std::vector<wchar_t>& vec_user, std::vector<wchar_t>& vec_hidden_word) // функция окраски и вывода слов
{
	std::wcout << ERASE << (count_of_attemp + 1) << L"  ";
	for (size_t i = 0; i < 5; ++i) // первый цикл для обхода букв по введенному слову
	{
		bool flag = false; // флаг для проверки, выведено ли уже слово

		if (vec_user[i] == vec_hidden_word[i]) // если буква на в загаданном слове есть и на той же позиции, меняем флаг и выводим
		{
			flag = true;
			std::wcout << BG << vec_user[i] << RESET;
			continue;
		}
		else // если буква не на той же позиции, обходим остальльные буквы в загаданном слове
		{
			for (size_t j = 0; j < 5; ++j) // воторой цикл для обхода по загаданному слову
			{
				if (vec_user[i] == vec_hidden_word[j])
				{
					flag = true;
					std::wcout << BY << vec_user[i] << RESET;
					break;
				}
			}
		}
		if (!flag) std::wcout << BGRAY << vec_user[i] << RESET; // если буквы нет, выводим без подсветки
	}
	std::wcout << std::endl;
} // color_processing

///////////////////////////////////////////////////////////////////////
long long amount_of_words(std::string file_slov) {//Находит количество слов в файле
	long long count = 0;//Задаем счетчик
	std::wstring line;//Слова, которые будут перебираться(Слова в файле записаны одно в строку)
	std::wifstream fin(file_slov);//Окрываем файл для чтения
	while (getline(fin, line)) {//Простым проходом по файлу считаем количесвто строк 
		++count;
	}
	fin.close();//Закрываем поток
	return count;//Возвращаем количество строк
}

std::vector<wchar_t> transform(std::wstring line) {//Переводит string в вектор char
	std::vector<wchar_t> vec_rand_word(n);//Создаем вектор char
	for (int i = 0; i < n; ++i) {//Проходим по строке и посимвольно присваиваем каждому элементу вектора char соотвествующй элемент стркои
		vec_rand_word[i] = line[i];
	}
	return vec_rand_word;//возвращаем готовый вектор
}

std::vector<wchar_t> choice_of_random_word(std::string file_slov) {//Функция выбиарет псевдослучайным образом слово
	std::wstring line;//Слова, которые будут перебираться(Слова в файле записаны одно в строку)
	long long count = amount_of_words(file_slov); //Получаем количество строк в файле
	std::random_device rd;   // non-deterministic generator            Кусок кода на 4 строки для получения рангдомного числа
	std::mt19937 gen(rd());  // to seed mersenne twister.
	std::uniform_int_distribution<> dist(1, count);
	long long rand_number = dist(gen);//Генерируем псевдослучайное число
	//std::cout << rand_number << "\n";Для отладки

	std::wifstream fin(file_slov); //Окрываем файл для чтения
	for (int i = 0; i != rand_number; ++i) {//Проходимся по файлу считая rand_number строк, то есть находим нужную нам по счету строку
		getline(fin, line);
	}
	fin.close();

	return transform(line);//Преобразуем string в вектор char и возвращаем в полученный вектор char'ов
}

bool check_letters(std::vector<wchar_t> line, std::vector<wchar_t> user_word) {//Функция проверяет два массива char на равеноство посимвольно
	for (size_t i = 0; i < n; ++i) {//Идем по массиву
		if (line[i] != user_word[i]) {//Срваниваем и если не равны, то возвращаем false
			return false;
		}
	}
	return true;
}

bool check_on_word(std::vector<wchar_t> user_word, std::string file_slov) {//Функция которая проверяет сущесвтование слова
	bool condition = false;
	std::wstring line;//Слова, которые будут перебираться(Слова в файле записаны одно в строку)
	std::wifstream fin(file_slov);//Окрываем файл для чтения
	while (getline(fin, line)) {//Просто проходом по файлу 
		//Считывем слово с новой строки
		//std::cout << line << "\n";//Для отладки
		if (check_letters(transform(line), user_word)) {//Если слова совпадают, то возвращаем true, иначе проверяем следующее
			condition = true;
			break;
		}
	}
	fin.close();//Закрываем поток
	return condition;//Возвращаем состояние проверки
}

int pos_in_alf_wchar(wchar_t liter){//Возвращает позицию данной буквы в алфавите
	for (size_t i = 0; i < alf_vec.size(); i++){
		if (liter == alf[i])
			return i;
	}
	return (alf_vec.size()-1);	
}

bool ravenstvo_liter(wchar_t a, wchar_t b){//Проверка на равенство двух wchar_t
	return (a == b);
}

bool availability_of_liter_in_word(wchar_t liter, std::vector<wchar_t> answer_word){//Фкункция проверки наличия буквы в слове
	bool flag = false;
	for (size_t i = 0; i < n; i++){//Просто проходка по слову, если случилось совпадение, то флаг == true
		if (answer_word[i] == liter){
			flag = true;
		}
	}
	return flag;
}

void transformation_of_condition_of_alf_vec(std::vector<wchar_t> user_word, std::vector<wchar_t> answer_word, std::vector<short> &alf_vec){//Функция преобразования вектора alf_vec, после введенного пользователем слова
	//0 - буква не выбиралась пользователем (черный)
	//1 - буква выбиралась пользователем, но нет в загаданном слове(серый)
	//2 - буква выбиралась пользователем, есть в загаданном слове, но не на своем месте(желтый)
	//3 - буква выбиралась пользователем, есть в загаданном слове и совпадает по местоположению(зеленый)
	int condition_of_this_liter = 0;
	int  pos_liter_in_alf;
	for (size_t i = 0; i < n; i++) //Проход по слову
	{ 
		pos_liter_in_alf = pos_in_alf_wchar(user_word[i]);
		condition_of_this_liter = alf_vec[pos_in_alf_wchar(user_word[i])];//Возвращает состояние данной буквы
		if ((condition_of_this_liter % 2) == 1){//Если данная буква в состоянии 1(серый) или 3(зеленый)
			continue;
		}
		else if (condition_of_this_liter == 2){//Если данная буква в состоянии 2(желтый)
			if (ravenstvo_liter(user_word[i],answer_word[i])) {//Проверяем находится ли дананя буква в нужном месте
				alf_vec[pos_liter_in_alf] = 3;//переводим в состояние 3
			}
		}
		else {
			if (ravenstvo_liter(user_word[i],answer_word[i])) {//Проверяем находится ли дананя буква в нужном месте
				alf_vec[pos_liter_in_alf] = 3;//переводим в состояние 3
			}
			else if (availability_of_liter_in_word(user_word[i], answer_word)){//Проверяем есть ли данная буква в слове(не проверяем на равенство i-ыъ символов, так как это было сделано на один if выше)
				alf_vec[pos_liter_in_alf] = 2;//переводим в состояние 2
			}
			else{//Если не находится в слове, то делаем серым
				alf_vec[pos_liter_in_alf] = 1;//переводим в состояние 1
			}
		}
	}
}

void transformation_of_alf(){
	int count_of_peremeshenia = 2 + count_of_attemp;//Количесвто строк, на которое надо поднятся
	std::wcout << L"\x1b[" << count_of_peremeshenia << "F";//Перемещаемся к строчке с алфавитом
	//for (size_t i = 0; i < count_of_attemp; i++) { std::wcout << L"\x1b[1F"; }
	//std::wcout << L"\x1b[0K";
	//std::wcout << L"\x1b[1F"; 

	std::wcout << L"  " << RESET;
	for (size_t i = 0; i < alf_vec.size(); i++){
			switch(alf_vec[i]){
				case 0:
					std::wcout << RESET << alf[i] << RESET;
					break;
				case 1:
					std::wcout << RESET << BGRAY << alf[i] << RESET;
					break;
				case 2:
					std::wcout << RESET << BY << alf[i] << RESET;
					break;
				case 3:
					std::wcout << RESET << BG << alf[i] << RESET;
					break;
				default: 
            		std::wcout << RESET << "\tError, fun: transformation_of_alf, fix pls\t" << RESET;
            		break;	
			}
	}

	std::wcout << L"\x1b[" << (count_of_peremeshenia-1) << "E";//Перемещаем курсор обратно на такое же количество строк вниз
}

void color_alf(std::vector<wchar_t> user_word, std::vector<wchar_t> answer_word, std::vector<short>& alf_vec){
	transformation_of_condition_of_alf_vec(user_word, answer_word, alf_vec);//Преобразуем вектор alf_vec в соотвествии введеному слову
	transformation_of_alf();//Переход к алфавиту, его раскраска, возврат обратно в конец
}