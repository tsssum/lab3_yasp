// Использование созданного шаблонного класса необходимо показать на трех разных типах данных :
//− Числовой;
//− Строковый;
//− Пользовательская структура на выбор сдающего(минимум 3 поля).
//

//6. Реализовать шаблон класса множество Set<X>. Класс должен содержать методы:
//− Добавление элемента во множество;
//− Удаление элемента из множества;
//− Проверка существования элемента во множестве;
//− Операции объединения двух множеств;
//− Пересечение двух множеств;
//− Разности двух множеств;
//− Вывод множества в файл;
//− Печать множества на консоль;
//− Инициализация множества из файла.
import TIME;
import SET;
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <compare>
#include <regex>
#include <Windows.h>

std::string get_file();
bool condition(int x, int border);
void read_and_check(int& x, bool(*condition)(int, int), int border);
int menu(const char* message, bool(*condition)(int, int), int border);
int exit();
template<typename T>
void tasks(Set<T>& set, short option);
void string_tasks(short option) {};
void time_tasks(short option) {};
template<typename T>
T validation();
int valid_int();
std::string valid_string();
Time valid_time();
template<typename T>
void set_in(Set<T>& set, short option_inp);

int main()
{
    SetConsoleOutputCP(1251);
    Set<int> set_i;
    Set<std::string> set_s;
    Set<Time> set_t;
    bool flag{}; // флаг чтоб определить вводили ли мы уже значения в основное множество
    short option{}, tmp{}; //тмп чтобы тыщу раз не спрашивать как иниц и как вводить
    do
    {
        option = menu("\nЗадачи:\n1. Добавление элемента во множество.\n"
            "2. Удаление элемента из множества\n"
            "3. Проверка существования элемента во множестве\n"
            "4. Операции объединения двух множеств\n"
            "5. Пересечение двух множеств\n6. Разность двух множеств\n"
            "7. Вывод множества в файл\n8. Печать множества на консоль\n"
            "9. Завершение работы", condition, 10);

        if (option != 9)
        {
            short option2, option3;
            if (!tmp)
            {
                option2 = menu("Каким типом данных инициализировать?\n1. int\n2. std::string\n3. Time", condition, 4);
                option3 = menu("Как вводить значения?\n1. С консоли\n2. Из файла", condition, 3);
                tmp = option2;
            }
                switch (tmp)
                {
                case 1:
                {
                    if (!flag) { set_in(set_i, option3); flag = 1; }
                    tasks(set_i, option);
                    break;
                }
                case 2:
                {
                    if (!flag) { set_in(set_s, option3); flag = 1; }
                    tasks(set_s, option);
                    break;
                }
                case 3:
                {
                    if (!flag) { set_in(set_t, option3); flag = 1; }
                    tasks(set_t, option);
                    break;
                }
                }

        }
        option = exit();
    } while (option != 9);

    std::cin.get();
}


std::string get_file()
{
    std::cout << "Введите имя файла:\n>";
    std::string file_name;
    std::cin >> file_name;
    std::ifstream file(file_name);
    while (!file)
    {
        std::cout << "Файл не найден! Введите корректное название файла!\n-> ";
        std::cin.clear();
        std::string file_name;
        std::cin >> file_name;
        file.open(file_name);
    }
    return file_name;
}

bool condition(int x, int border)
{
    return x > 0 && x < border;
}

void read_and_check(int& x, bool(*condition)(int, int), int border)
{
    std::cout << "\n->";
    while (!(std::cin >> x && condition(x, border))) {
        std::cout << "Ошибка! Введите корректное значение:\n";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\n->";
    }
}

int menu(const char* message, bool(*condition)(int, int), int border)
{
    std::cout << message;
    int option{};
    read_and_check(option, condition, border);
    std::cout << "\n";
    return option;
}


int exit()
{
	std::cout << "Завершить работу? (Y/любая клавиша): ";
	char is_exit;
	short option_exit{};
	std::cin >> is_exit;
	if (is_exit == 'Y' || is_exit == 'y')
		option_exit = 9;
	return option_exit;
}

int valid_int()
{
    std::string input;
    int elem;
    bool flag{};

    do
    {
        std::cout << "Введите элемент: ";
        std::getline(std::cin, input);

        std::istringstream ss(input);
        if (ss >> elem)
        {
            if (ss.eof()) { flag = 1; }
        }

        if (!flag)
        {
            std::cout << "Некорректный ввод. Пожалуйста, повторите ввод.\n";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
        }
    } while (!flag);
    return elem;
}

std::string valid_string()
{
    std::string str;
    std::cout << "Введите элемент: ";
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::getline(std::cin, str);
    return str;
}

Time valid_time()
{
    std::string str;
    std::cout << "Введите время (часы, минуты, секунды, разделённые двоеточием): ";
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::getline(std::cin, str);
    std::regex time_regex(R"(\s*(\d+)\s*:\s*(\d+)\s*:\s*(\d+)\s*)");
    std::smatch matches;
    while (!std::regex_match(str, matches, time_regex))
    {
        std::cout << "Некорректный ввод. Пожалуйста, введите время без лишних символов.\n->";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::getline(std::cin, str);
    }
    Time time(str);
    return time;
}

template<typename T>
void tasks(Set<T>& set, short option)
{
    T elem;
    Set<T> other;

    if (option == 4 || option == 5 || option == 6)
    {
        short choice = menu("\nКак вводить значения нового множества?\n1. С консоли\n2. Из файла", condition, 3);
        set_in(other, choice);
    }

    switch (option)
    {
    case 1: //1. Добавление элемента во множество.
    {
       elem = validation<T>();
       set.add(elem);
        break;
    }
    case 2: //2. Удаление элемента из множества
    {
        elem = validation<T>();
        set.del(elem);
        break;
    }
    case 3: // Проверка существования элемента во множестве
    {
        elem = validation<T>();
        if (set.find(elem))
            std::cout << "Множество содержит элемент\n";
        else
            std::cout << "Множество НЕ содержит элемент\n";
        break;
    }
    case 4: // Операции объединения двух множеств
    {
        set.Union(other);
        break;
    }
    case 5: //Пересечение двух множеств
    {
        set.Intersection(other);
        break;
    }
    case 6: //Разность двух множеств
    {
        set.Difference(other);
        break;
    }
    case 7: //Вывод множества в файл
    {
        std::string file_name = get_file();
        set.print_to_file(file_name);
        break;
    }
    case 8: //Печать множества на консоль
    {
        std::cout << "Множество: ";
        set.print_to_console();
        std::cout << '\n';
        break;
    }
    }
}


template<typename T>
T validation()
{
    T elem;

    if constexpr (std::is_same<T, int>::value)
    {
        elem = valid_int();
    }

    else if constexpr (std::is_same<T, std::string>::value)
    {
        elem = valid_string();
    }
    else
    {
        elem = valid_time();
    }
    return elem;
}

template<typename T>
void set_in(Set<T>& set, short option_inp)
{
    if (option_inp ==1)
    {
        T elem;
        size_t n;
        std::cout << "Сколько элементов ввести?\n-> ";
        std::cin >> n;
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        for (size_t i{}; i < n; ++i)
        {
            elem = validation<T>();
            set.add(elem);
        }

    }
    else 
    {
        std::string file_name = get_file();
        Set<T> set_if(file_name);
        set = set_if;
    }
}
