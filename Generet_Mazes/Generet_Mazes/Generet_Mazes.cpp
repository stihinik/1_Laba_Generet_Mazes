// Generet_Mazes.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>


#define sizes  11

using namespace std;

class Coord
{
public:
	int i;
	int j;
	Coord(int i, int j)
	{
		this->i = i;
		this->j = j;
	}
};
bool Srav(Coord who, vector<Coord> with)
{
	bool flag = false;
	for (size_t f = 0; f < with.size(); f++)
	{
		if ((who.i == with[f].i)&&(who.j == with[f].j))
		{
			flag = true;
			break;
		}
	}
	return flag;
}
void Print_Mas(string mas[sizes][sizes])
{
	for (int i = 0; i < sizes; i++)
	{
		for (int j = 0; j < sizes; j++)
		{
			cout << mas[i][j] << "   "; 
		}
		cout << endl << endl;
	}
}
void Fill_Maze(string mas[sizes][sizes])
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
void Round_Stown(string mas[sizes][sizes], vector<Coord> with)
{
	int k = 0;
	while (k < 10)
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
						rand_i--;
					}
				}
				else if (with[t].i > rand_i)
				{
					while (with[t].i != rand_i)
					{
						mas[rand_i][rand_j] = " ";
						rand_i++;
					}

				}
				break;
			}
		}
		mas[rand_i][rand_j] = " ";
		k++;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	int Nomer = 10;
	int count=0;
	while (1)
	{
		if (count < 10000)
		{
			cout << "1 - Создать новый лабиринт" << endl;
			cout << "0 - Выйти из программы" << endl;
			cin >> Nomer;
		}
		system("cls");
		count = 0;
		if (Nomer == 1)
		{
			string Maze[sizes][sizes] = {};
			vector <Coord> True_Puth;
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
					int i_1 = i;
					int j_1 = j;
					int step = (rand() % 3);
					if (step == 0) { j = j + 1; }
					else if (out_maze < i && j == 10) { i = i - 1; }
					else if (out_maze > i && j == 10) { i = i + 1; }
					else if (step == 1) { i = i + 1; }
					else if (step == 2) { i = i - 1; }
					Coord i_j(i, j);
					bool flag_2 = Srav(i_j, True_Puth);
					flag = (((i == 0) || (i == 11)) || ((j == 0) || (j == 11)) || flag_2);
					if (flag) {
						i = i_1; j = j_1;
					}
					else {
						True_Puth.push_back(i_j);
					}
					count++;
					if (count > 10000) { break; }
				}
				if (count > 10000) { break; }
				Maze[i][j] = " ";
			}
			
			if (count < 10000)
			{
				Round_Stown(Maze, True_Puth);
				Maze[in_maze][1] = "!";
				Maze[out_maze][10] = "!";

				Print_Mas(Maze);
				cout << "Путь до выхода:";
				cout << endl;
				for (size_t t = 0; t < True_Puth.size(); t++)
				{
					cout << True_Puth[t].i << ',' << (char)(97 - 1 + True_Puth[t].j) << "  ";
				}
				cout << endl;
			}
		}
		else if (Nomer == 0){break;}
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
