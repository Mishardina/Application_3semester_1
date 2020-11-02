#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>


void writeDisc();  //функция записи файла муз. дисков

void writeGroup(); //функция записи файла муз. групп

void writeHelp(); //вывод меню помощи

bool checkMistake(std::string inpYear);   //проверка введенной даты на ошибку

int main()
{
	setlocale(LC_ALL, "Russian");

	char key;        //клавиша для выбора действия
	bool isInp = true;      //флаг для бесконечного цикла


	while (isInp == true) {
		std::cout << "Введите цифру 1 - если хотите внести данные о музыкальных дисках\n\nЦифру 2 - если хотите внести данные о музыкальных группах\n\nЦифру 0 - если хотите увидеть меню помощи\n\nEsc - если хотите выйти из программы\n\n";
		key = _getch();    //регистрация нажатия клавиши 
		system("cls");
		switch (key) {     //ветвление выбора действия
		case 48:           //случай нажатия "0"
			writeHelp();
			break;
		case 49:           //случай нажатия "1"
			writeDisc();
			break;
		case 50:           //случай нажатия "2"
			writeGroup();
			break;
		case 27:           //случай нажатие "Esc"
			isInp = false;
			break;
		default:           //случай нажатия некорректной клавиши
			Sleep(500);      
			std::cout << "Вы нажали некорректную клавишу, повторите ввод\n\n";
			break;
		}
	}
	std::cout << "Программа завершает работу.\n";
}

void writeDisc() {

	struct str_music_disc {    //структура, содержащая данные о дисках
		char album[255];       //альбом
		char singer[255];      //исполнитель
		char year[5];          //год выпуска альбома
	} disc;


	std::cout << "Пожалуйста, введите название файла музыкальных дисков\n\n";

	std::string filename;      //строка для ввода имени файла с клавиатуры

	std::getline(std::cin, filename);

	if (filename.find(47) != std::string::npos || filename.find(92) != std::string::npos || filename.find(63) != std::string::npos) { //проверка на запрещенные символы
		while (!(filename.find("/") == std::string::npos && filename.find('\\') == std::string::npos && filename.find('?') == std::string::npos)) {
			std::cout << "\nНекорректные символы в названии файла! Введите название заново\n";
			std::getline(std::cin, filename);
		}
	}


	system("cls");

	std::cout << "\nЕсли вы хотите дозаписать файл, то нажмите 1\n\nЕсли хотите перезаписать существующий, то нажмите 2\n\nЕсли необходимый файл не существует, он будет создан\n\n";

	char ch;          //клавиша для выбора режима записи файла
	ch = _getch();

	std::ofstream discFile;  //файловый поток 

	bool isCorrect = false;   //флаг проверки корректности выбора режима записи

	while (isCorrect == false) {
		if (ch == 49) {       //случай нажатия клавиши "1", открытие на дозапись
			discFile.open(filename + ".bin", std::ios::binary | std::ios::app);
			std::cout << "\nВы открыли файл на дозапись!\n";
			isCorrect = true;
		}
		else if (ch == 50) {  //случай нажатия клавиши "2", открытие на перезапись
			discFile.open(filename + ".bin", std::ios::binary | std::ios::trunc);
			std::cout << "\nВы открыли файл на перезапись!\n";
			isCorrect = true;
		}
		else if (!(ch == 49) || !(ch == 50)) {  //случай нажатия некорректной клавиши
			std::cout << "\nВы нажали неправильную клавишу! Повторите ввод!\n";
			ch = _getch();
		}
	}


	std::cout << "\nВведите название альбома\n\n";
	std::cin.getline(disc.album, 255, '\n');

	std::cout << "\nВведите имя/название исполнителя\n\n";
	std::cin.getline(disc.singer, 255, '\n');

	std::cout << "\n------------Внимание! В поле ""год"" должны содержаться только цифры, а число должно быть в четырехзначном формате!------------\n";

	std::cout << "\nВведите год выпуска\n"; 
	std::string buffer;              //буферная строка для обработки ошибки длины в дате
	std::getline(std::cin, buffer);
	buffer = buffer.substr(0,5);     //строка автоматически укорачивается до 4 цифр

	for (int i = 0; i < 5; i++) {
		disc.year[i] = buffer[i];
	}

	if (checkMistake(disc.year) == false) {    //проверка на наличие букв в дате
		while (checkMistake(disc.year) == false) {
			std::cout << "!!!!Ошибка в записи года! Введите год заново!!!!\n";
			std::getline(std::cin, buffer);
			buffer = buffer.substr(0, 5);

			for (int i = 0; i < 5; i++) {
				disc.year[i] = buffer[i];
			}
			checkMistake(disc.year);
		}
	}


	discFile.write((char*)& disc, sizeof(disc));  //запись в файл
	std::cout << "\nИнформация успешно записана!\n";

	discFile.close();

	Sleep(1500);
	system("cls");
}

void writeGroup() {

	struct str_music_performer {  //структура, содержащая данные об исполнителях
		char singer[255];         //исполнитель
		char country[255];        //страна происхождения
		char style[255];          //музыкальный стиль
	} perf;

	std::cout << "Пожалуйста, введите название файла исполнителей\n\n";

	std::string filename;  //строка для ввода имени файла с клавиатуры
	std::getline(std::cin, filename);

	if (filename.find(47) != std::string::npos || filename.find(92) != std::string::npos || filename.find(63) != std::string::npos) { //проверка на запрещенные символы
		while (!(filename.find("/") == std::string::npos && filename.find('\\') == std::string::npos && filename.find('?') == std::string::npos)) {
			std::cout << "\nНекорректные символы в названии файла! Введите название заново\n";
			std::getline(std::cin, filename);
		}
	}

	Sleep(1500);
	system("cls");

	std::cout << "\nЕсли вы хотите дозаписать файл, то нажмите 1\n\nЕсли хотите перезаписать существующий, то нажмите 2\n\nЕсли необходимый файл не существует, он будет создан\n\n";

	char ch;          //клавиша для выбора режима записи файла
	ch = _getch();

	std::ofstream performerFile;   //файловый поток

	bool isCorrect = false;   //флаг проверки корректности выбора режима записи

	while (isCorrect == false) {
		if (ch == 49) {       //случай нажатия клавиши "1", открытие на дозапись
			performerFile.open(filename + ".bin", std::ios::binary | std::ios::app);
			std::cout << "\nВы открыли файл на дозапись!\n";
			isCorrect = true;
		}
		else if (ch == 50) {  //случай нажатия клавиши "2", открытие на перезапись
			performerFile.open(filename + ".bin", std::ios::binary | std::ios::trunc);
			std::cout << "\nВы открыли файл на перезапись!\n";
			isCorrect = true;
		}
		else if (!(ch == 49) || !(ch == 50)) {  //случай нажатия некорректной клавиши
			std::cout << "Вы нажали неправильную клавишу! Повторите ввод!\n";
			ch = _getch();
		}
	}

	std::cout << "\nВведите имя группы\n";
	std::cin.getline(perf.singer, 255, '\n');

	std::cout << "\nВведите страну\n";
	std::cin.getline(perf.country, 255, '\n');

	std::cout << "\nВведите стиль\n";
	std::cin.getline(perf.style, 255, '\n');

	performerFile.write((char*)& perf, sizeof(perf));  //запись в файл
	std::cout << "\nИнформация успешно записана!\n";

	performerFile.close();

	Sleep(1500);
	system("cls");
}

void writeHelp() {  //функция вывода на экран меню помощи
	std::cout << "------------------------------------\nВводите текст внимательно, чтобы не допустить ошибки в названии\n!!!!В строке ГОД должны содержаться только цифры!!!!\n------------------------------------\n\n";
}

bool checkMistake(std::string inpYear) {              //функция проверки на ошибку
	for (int i = 0; i < inpYear.length(); i++) {
		if (!(inpYear[i] >= 48 && inpYear[i] <= 57)) {
			return false;
		}
	}
	return true;
}