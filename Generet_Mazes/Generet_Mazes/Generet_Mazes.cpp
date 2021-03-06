// Generet_Mazes.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

#define sizes  11

struct Coord
{
	int i;
	int j;
	Coord(int i, int j)
	{
		this->i = i;
		this->j = j;
	}
	bool operator == (const Coord &with)
	{
		if (this->i == with.i && this->j == with.j)
		{
			return true;
		}
		else { return false; }
	}
};
//Сравниваем новые координаты с предыдущими
bool Compare(Coord who, std::vector<Coord> with)
{
	bool flag = false;
	for (size_t f = 0; f < with.size(); f++)
	{
		if (who==with[f])
		{
			flag = true;
			break;
		}
	}
	return flag;
}
//Выводим содержимое массива на экран
void Print_Massiv(std::string mas[sizes][sizes])
{
	for (int i = 0; i < sizes; i++)
	{
		for (int j = 0; j < sizes; j++)
		{
			std::cout << mas[i][j] << "   ";
		}
		std::cout << std::endl << std::endl;
	}
}
//Заполняем массив координатами и *
void Fill_Maze(std::string mas[sizes][sizes])
{
	for (int i = 1; i < sizes; i++)
	{
		mas[0][i] = (char)(97 - 1 + i);
		mas[i][0] = (char)(49 - 1 + i);
	}
	for (int i = 1; i < sizes; i++)
	{
		for (int j = 1; j < sizes; j++)
		{
			mas[i][j] = "*";
		}
	}
	mas[10][0] = "10";
}
//Добавляем Дополнительные пути, кроме правильного
void Rand_Stown(std::string mas[sizes][sizes], std::vector<Coord> with)
{
	int k = 0;
	while (k < 6)
	{
		int rand_i = (rand() % 10 + 1);
		int rand_j = (rand() % 10 + 1);
		for (size_t t = 0; t < with.size(); t++)
		{
			if (with[t].j == rand_j)
			{
				if (with[t].i < rand_i)
				{
					while (with[t].i != rand_i)
					{
						mas[rand_i][rand_j] = " ";
						mas[rand_j][rand_i] = " ";
						rand_i--;
					}
				}
				else if (with[t].i > rand_i)
				{
					while (with[t].i != rand_i)
					{
						mas[rand_i][rand_j] = " ";
						mas[rand_j][rand_i] = " ";
						rand_i++;
					}

				}
				break;
			}
		}
		k++;
	}
}
//Создание пути от входа к выходу
bool Сreature_TrueWay(const int in, const int out, int &i, int &j, std::vector<Coord> &way)
{
	int i_1 = i;
	int j_1 = j;
	int step = (rand() % 3);

	if (step == 0) { j = j + 1; }
	else if (out < i && j == 10) { i = i - 1; }
	else if (out > i && j == 10) { i = i + 1; }
	else if (step == 1) { i = i + 1; }
	else if (step == 2) { i = i - 1; }

	Coord i_j(i, j);
	bool flag = (((i == 0) || (i == 11)) || ((j == 0) || (j == 11)) || Compare(i_j, way));

	if (flag) { i = i_1; j = j_1; }
	else { way.push_back(i_j); }
	return flag;
}
//Заполнение массива дополнительными элементами
void Treatment_Maze(std::string mas[sizes][sizes], std::vector<Coord> &way, const int in, const int out)
{
	way.pop_back();
	Rand_Stown(mas, way);
	std::cout << " '!' - обозначает вход и выход лабиринта, а '*'- стены лабинта" << std::endl;
	// Прорисовываем правильный путь
	for (size_t t = 0; t < way.size(); t++) mas[way[t].i][way[t].j] = ">";

	mas[in][1] = "!";
	mas[out][10] = "!";

	Print_Massiv(mas);
	std::cout << "Путь до выхода:" << std::endl;
	//выводим координаты пути от входа до выхода
	for (size_t t = 0; t < way.size(); t++)
	{
		std::cout << way[t].i << ',' << (char)(97 - 1 + way[t].j) << "  ";
	}
	std::cout << std::endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	int nomber = 10;
	int count=0;
	while (true)
	{
		if (count < 10000)
		{
			std::cout << "1 - Создать новый лабиринт" << std::endl;
			std::cout << "0 - Выйти из программы" << std::endl;
			std::cin >> nomber;
		}
		system("cls");
		count = 0;
		if (nomber == 1)
		{
			//Создаем переменные и массив куда будет все записано
			std::string Maze[sizes][sizes] = {};
			std::vector <Coord> True_Way;
			int in_maze = (rand() % 10 + 1);
			int out_maze = (rand() % 10 + 1);
			int i = in_maze;
			int j = 1;
			bool end = true;
			Fill_Maze(Maze);
			while (end)
			{
				end = !(i == out_maze && j == 10);
				bool flag = true;
				while (flag)
				{
					flag = Сreature_TrueWay(in_maze, out_maze, i, j, True_Way);
					count++;
					if (count > 10000) { break; }
				}
				if (count > 10000) { break; }
				else { Maze[i][j] = " "; }
			}
		    if (count < 10000)
			{
				Treatment_Maze(Maze, True_Way, in_maze, out_maze);
			}
		}
		else if (nomber == 0){break;}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
