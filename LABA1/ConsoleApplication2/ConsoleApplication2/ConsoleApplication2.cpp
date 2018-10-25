#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
string Cezar(string a, int k) { // Функция шифрования. Аргументы функции - строка из файла для шифрования и ключ - число смещений по алфавиту
	string TC; 
	for (int i = 0; i<(a.length()); i++) { //Формируется новая строка - шифртекст. Берется каждый символ из строки и смещается по таблице ASCII на k шагов
		TC = TC + (char)((a[i] + k));
	}
	return TC; //функция возвращает шифрстроку
}
string nCezar(string TC, int k) { // Функция расшифрования
	string nTC;
	for (int i = 0; i < TC.length(); i++) { //Аналогично функции шифрования, только смещение по таблице происходит в обратную сторону
		nTC = nTC + (char)(TC[i] - k);
	}
	return nTC;
}
bool pred(const std::pair< char, int > &a, const std::pair< char, int > &b) //компоратор для функции сортировки. возвращает результат сравнения количества встреч двух символов в тексте
{
    return a.second > b.second;
}
int main() // Главная Функция программы
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); //Для корректного отображения русских символов
		string a; //переменная для одной строки файла
		int key = 1; //Переменная, которая будет ключом в меню навигации
		while (key != 7) //Цикл, пока в меню не будет выбран 6 пункт - выход из программы
		{
			system("cls"); //Отчистка консоли
			cout << "\tМЕНЮ" << endl;
			cout << "1. Зашифровать текст в файле" << endl;
			cout << "2. Расшифровать текст из файла" << endl;
			cout << "3. Получить частотную таблицу текста из файла" << endl;
			cout << "4. Получить две частотные таблицы текстов из файлов" << endl;
			cout << "5. Расшифровать с помощью частотного анализа" << endl;
			cout << "6. Расшифровать с помощью биграмм" << endl;
			cout << "7. Выход из программы" << endl;
			cout << "Введите нужный пункт меню: ";
			cin >> key; //ввод нужного пункта меню
			switch (key) //В зависимости от введенного числа выполняется:
			{
			case 1: //Если введено число 1, то происходит шифрования текста из входного файла
			{
				system("cls");
				char s[20]; //Для названия входного файла
				cout << "Введите название файла для зашифрования: ";
				cin >> s; //Ввод названия
				ifstream in(s, ios::in); //Создание файлового потока на чтение
				ofstream out("crypt.txt", ios::out); //На запись 
				if (!in) { //Если такого входного файла нет, то вывод ошибки
					cerr << "Указаного файла не существует!\n";
					system("pause");
					break;
				}
				else //Иначе
				{
					cout << "Введите ключ для шифра (цифра - количество сдвигов по таблице): ";
					int k;
					cin >> k; //Вводим ключ - количество смещений по алфавиту
					while (getline(in, a)) //Цикл до тех пор, пока из входного файла считываются строки. Строку считываем в "a" 
					{
						string TC = Cezar(a, k); //Вызываем функцию шифрования строки
						out << TC << endl; //Выводим в файл результат шифрования строки
					}
					cout << "Результат записан в файл crypt.txt" << endl;
					system("pause");  //Задержка консоли
				}
				break;
			}
			case 2: //Если введено 2, то происходит расшифровка текста из входного файла. Все делается аналогично с шифрованием, только вызывается функция расшифровки
			{
				system("cls");
				char s[20];
				cout << "Введите название файла для расшифровки: ";
				cin >> s;
				ifstream in(s, ios::in);
				ofstream out("decrypt.txt", ios::out);
				if (!in) {
					cerr << "Указаного файла не существует!\n";
					system("pause");
					break;
				}
				else
				{
					cout << "Введите ключ для шифра (цифра - количество сдвигов по таблице): ";
					int k;
					cin >> k;
					while (getline(in, a))
					{
						string TC = nCezar(a, k);
						out << TC << endl;
					}
					cout << "Результат записан в файл decrypt.txt" << endl;
					system("pause");
				}
				break;
			}
			case 3: //Если введено 3, то вызывается функция создания частотной таблицы для текста из входного файла
			{
				system("cls");
				char s[20]; //для имени входного файла
				int kol = 0; //переменная для общего количества символов в тексте. Нужно для нахождения частоты в процентах
				cout << "Введите название файла, для которого будет составлена частотная таблица: ";
				cin >> s; //Ввод названия файла
				ifstream in(s, ios::in); 
				ofstream out("table.txt", ios::out); //Создание файловых потоков на чтение и запись
				if (!in) { //Ошибка, если входного файла нет
					cerr << "Указаного файла не существует!\n";
					system("pause");
					break;
				}
				else //Иначе создаем частотную таблицу
				{
					std::map<char, int> map; //Объявляем контейнер map. В одном элементе контейнера хранится пара: символ алфавита и число - количество встреч данного символа в тексте
					while (getline(in, a)) //Цикл, пока из файла считываются строки
					{
						for (int i = 0; i < (a.length()); i++) { //Идем по считанной строке
							map[a[i]]++; //Увеличиваем элемент контейнера map с данным символом на единицу 
							kol++; //Общее число символов увеличиваем на единицу
						}
					}
					std::vector< std::pair< char, int > > vec(map.begin(), map.end()); //Переносим сформированный ранее контейнер map в вектор. В векторе удобно произвести сортировку по частоте
					std::sort(vec.begin(), vec.end(), pred); //Вызываем стандартную функцию сортировки вектора. В нее передаются начало вектора, конец и компоратор, объявленный выше. Таким образом произведется сортировка по убыванию
					for (auto it : vec) //Цикл по всему вектору
					{
						cout << it.first << '=' << float(it.second) / kol * 100 << "%" << endl; //Выводим в консоль и в файл каждый символ и его частоту в процентах
						out << it.first << '=' << float(it.second) / kol * 100 << "%" << endl;
					}
				}
				cout << "Частотная таблица записана в файл table.txt" << endl;
				system("pause");
				break;
			}
			case 4: //Если введено 4, то получаем две частотные таблицы двух файлов для сравнения. Делается все абсолютно то же самое, что и в пункте 3, только для 2 файлов
			{
				system("cls");
				char s[20], f[20];
				int kols = 0, kolf = 0;
				cout << "Введите название первого файла: ";
				cin >> s;
				cout << "Введите название второго файла: ";
				cin >> f;
				ifstream in(s, ios::in);
				ifstream fin(f, ios::in);
				ofstream out("2table.txt", ios::out);
				if (!in || !fin) {
					cerr << "Не правильное имя файла!\n";
					system("pause");
					break;
				}
				else
				{
					std::map<char, int> smap;
					std::map<char, int> fmap;
					while (getline(in, a))
					{
						for (int i = 0; i < (a.length()); i++) {
							smap[a[i]]++;
							kols++;
						}
					}
					while (getline(fin, a))
					{
						for (int i = 0; i < (a.length()); i++) {
							fmap[a[i]]++;
							kolf++;
						}
					}
					std::vector< std::pair< char, int > > svec(smap.begin(), smap.end());
					std::sort(svec.begin(), svec.end(), pred);
					std::vector< std::pair< char, int > > fvec(fmap.begin(), fmap.end());
					std::sort(fvec.begin(), fvec.end(), pred);
					cout << "Первый файл" << endl;
					out << "Первый файл" << endl;
					for (auto it : svec)
					{
						cout << it.first << '=' << float(it.second) / kols * 100 << "%" << endl;
						out << it.first << '=' << float(it.second) / kols * 100 << "%" << endl;
					}
					cout << "Второй файл" << endl;
					out << "Второй файл" << endl;
					for (auto it : fvec)
					{
						cout << it.first << '=' << float(it.second) / kolf * 100 << "%" << endl;
						out << it.first << '=' << float(it.second) / kolf * 100 << "%" << endl;
					}
				}
				cout << "Результат записан в файл 2table.txt" << endl;
				system("pause");
				break;
			}
			case 5: //Если введено 5, то производится расшифровка текста из входного файла по частотной таблице
			{
				system("cls");
				char s[20];
				int kol = 0;
				cout << "Введите название файла, текст из которого будет расшифрован: ";
				cin >> s;
				ifstream in(s, ios::in);
				ofstream out("decryptbychast.txt", ios::out); //Вводим название файла, создаем файловые потоки
				if (!in) { //Ошибка, если нет такого файла
					cerr << "Указаного файла не существует!\n";
					system("pause");
					break;
				}
				else //иначе
				{
					char mass[33] = { ' ','о','а','е','и','н','л','с','т','р','в','к','д','у','м',',','п','ь','я','г','б','ы','з','ч','.','й','ж','х','ш','-','ю','Г' };
					//Инициализируем вручную предполагаемую частотную таблицу для русского алфавита
					std::map<char, int> map; //Объявляем контейнер map для хранения каждого символа и его частоты
					while (getline(in, a)) //Как и раньше, проходим по всему шифртексту и считаем частоту каждого символа в тексте
					{
						for (int i = 0; i < (a.length()); i++) {
							map[a[i]]++;
							kol++;	
						}	
					}
					std::vector< std::pair< char, int > > svec(map.begin(), map.end());
					std::sort(svec.begin(), svec.end(), pred); //Так же переносим контейнер в вектор и сортируем его. 
					//В итоге мы получаем отсортированную таблицу от самой частой буквы в текста до наименее частой.
					//По сути получилсоь соответствие, первый элемент вектора - это первый элемент массива mass
					in.close(); //Закрываем исходный файл
					ifstream fin(s, ios::in); //Вновь открываем исходный файл и снова читаем его с начала
					while (getline(fin, a)) //Берем каждую строчку исходного файла
					{
						for (int i = 0; i < (a.length()); i++) { //Берем каждый символ строки 
							int index = 0; //переменная для индекса
							for (auto it : svec) //Цикл по вектору
							{
								if (it.first == a[i]) break; //Находим порядковый номер текущей буквы в векторе. После нахождения выходим из цикла
								index++;
							} 
							//Получили порядковый номер символа в векторе. Теперь вместо данного символа надо подставить символ из массива mass с тем же индексом
							if (index < 33) a[i] = mass[index];  //Всего в mass введено 33 символа. Заменяем символ только в том случае, если символ входит в 33 самых частых символа
						}
						out << a << endl; //Полученную строку выводим в файл
					}
				}
				out.close(); //Закрываем выходной файл
				cout << "Расшифрованный текст помещен в файл decryptbychast.txt" << endl;
				system("pause");
				break;
			}
			case 6: //При нажатии 6 производится расшифровка биграммами
			{
				system("cls"); //Очистка консоли
				char s[20];
				cout << "Введите название файла, текст из которого будет расшифрован: ";
				cin >> s; //Ввод названия файла
				ifstream in(s, ios::in);
				ofstream out("decryptbybigramm.txt", ios::out); //Вводим название файла, создаем файловые потоки
				char prev = 0; //Переменная для предыдущего символа. Изначально пустой
				int digram[256][256]; //Двумерный массив для хранения количества встреч пары символов
				for (int i = 0; i < 256; i++)
					for (int j = 0; j < 256; j++)
						digram[i][j] = 0; //Изначально обнуляем весь этот массив
				if (!in) { //Ошибка, если нет такого файла
					cerr << "Указаного файла не существует!\n";
					system("pause");
					break;
				}
				else //иначе
				{
					char mass[10] = { 'т','а','н','н','л','п','к','с','в','н'};
					char secmass[10] = { 'о','л','а','е','а','о','а','т','о','о' }; //Объявление массивов с самыми частными биграммами. Одна биграмма - это пара первых символов из двух массивов, т.е это: то, ал, на...
					while (getline(in, a)) //цикл, пока считываются строки
					{
						for (int i = 0; i < (a.length()); i++)  //Цикл по строке
						{
							char curr = a[i]; //Запоминаем текущий символ
							if ('а' <= prev && 'я' >= prev && 'а' <= curr && 'я' >= curr) //Если текущий и предыдущие символы лежат между а..я 
								digram[prev - 'а'][curr - 'а']++; //То прибавляем единицу в том месте двумерного массива, где ячейка находится на пересечении предыдущего и текущего символов
							prev = curr; //Текущий символ делаем предыдущим
						}
					}
					in.close(); //Закрываем файл 
					std::map <string, int> map; //Создаем контейнер пар
					for (int i = 0; i < 256; i++)
						for (int j = 0; j < 256; j++) //Идем по двумерному массиву. Переносим в контейнер все биграммы и их посчитанную частотность
							if (digram[i][j] != 0) //Если частота не ноль, то переносим
							{
								char ch[3]; //Создается символьный массив
								ch[0] = char(i) + 'а';  //Кладется первая буква биграммы
								ch[1] = char(j) + 'а'; //вторая буква биграммы
								ch[2] = '\0'; //конец символа
								string temp = string(ch); //символьнйы массив переводится в строку
								map[temp] = digram[i][j]; //строка и ее частота кладется в контейнер
							}
					cout << "Частота биграмм в данном тексте: " << endl;
					for (auto it : map) //В цикле печатается биграмма и ее частота
						cout << it.first << '\t' << it.second << endl;
					std::map <int, string> maptwo; //создаем новый контейнер, где ключом будет уже частота. Таким образом отсортируем биграммы по частоте
					for (auto it : map) //Цикл по всему исходному контейнер
						maptwo[it.second] = it.first; //Переносим в новый контейнер
					ifstream fin(s, ios::in); //Вновь открываем исходный файл и снова читаем его с начала
					while (getline(fin, a)) //Берем каждую строчку исходного файла
					{
						prev = 0; //обнуляем предыдущий символ
						for (int i = 0; i < (a.length()); i++) { //Берем каждый символ строки 
							char curr = a[i]; //rkfltv tuj rfr ntreobq
							if ('а' <= prev && 'я' >= prev && 'а' <= curr && 'я' >= curr) //если биграмма состоит из букв а..я
							{
								char ch[3]; 
								ch[0] = prev;
								ch[1] = curr;
								ch[2] = '\0';
								string temp = string(ch); //составляем биграммную строку
								auto it = maptwo.end(); //ставим итератор на конец контейнер (там находится самая частая биграмма)
								it--; //Итератор ставился на ячейку после последнего элемента контейнера. Возвращаем на последний элемент
								for (int index = 0; index < 10; index++) //Смотрим первые 10 биграмм из контейнера
								{
									if (index == 10) break; //если 10 прошли уже, то выходим из цикла
									if (it->second == temp) //если значение ключа в контейнера совпадает с биграммой, то меняем ее
									{
										a[i - 1] = mass[index]; //меняем предыдущий символ на первый символ биграммы
										a[i] = secmass[index]; //текущий символ на второй
									}
									it--; //с конца перемещаемся по итератору к началу
								}
							}
							prev = curr; //делаем текущий символ предыдущим
						}
						out << a << endl; //Полученную строку выводим в файл
					}

				}
				out.close(); //Закрываем выходной файл
				cout << "Расшифрованный текст помещен в файл decryptbybigramm.txt" << endl;
				system("pause");
				break;
			}
			}
		}
	return 0;
}

