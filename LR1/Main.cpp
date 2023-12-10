#include "ArrayInteraction.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_BACKSPACE 8

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleTitle(L"Множества");
	ConsoleCursorVisible(false, 100);

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

	int cntEl;
	cout << "Введите количество элементов множества" << endl;
	cin >> cntEl;

	ArrayInteraction test(cntEl);
	test.genVec();

	int active_menu = 0;
	int keyInput;
	bool exitProg = false;

	system("cls");

	while (!exitProg)
	{
		int x = 20, y = 12;
		GoToXY(x, y);

		vector<string> menu =
		{
			"				Вывод множества на экран",
			"			Вычисление ранга заданного подмножества",
			"		Генерация и вывод на экран подмножества по заданному рангу",
			"			Генерация и вывод на экран всех подмножеств",
			"	Генерация и вывод на экран следующего подмножества по заданному подмножеству",
			"		Генерация всех подмножеств в порядке минимального изменения",
			"Генерация всех подмножеств в порядке минимального изменения (рекурсивный алгоритм)",
			"					Выход"
		};

		for (int i = 0; i < menu.size(); i++)
		{
			if (i == active_menu)
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			GoToXY(x, y++);
			cout << menu[i] << endl;
		}

		keyInput = _getch();
		switch (keyInput)
		{
		case KEY_ESC:
			exit(0);

		case KEY_UP:
		{
			if (active_menu > 0)
			{
				active_menu--;
			}
		}
		break;

		case KEY_DOWN:
		{
			if (active_menu < menu.size() - 1)
			{
				active_menu++;
			}
		}
		break;

		case KEY_ENTER:
		{
			switch (active_menu)
			{
			case 0:
			{
				system("cls");

				test.printVec();

				test.printQuit();
			}
			break;

			case 1:
			{
				system("cls");

				int add_num;
				vector<int> subsetInput;

				cout << "Введите элементы подмножества через пробел, после ввода последнего элемента введите точку" << endl;
				while (cin >> add_num)
				{
					subsetInput.push_back(add_num);
				}
				cin.clear();
				cin.ignore(255, '\n');

				cout << "Ранг подмножества - " << test.getRank(subsetInput);

				test.printQuit();

			}
			break;

			case 2:
			{
				system("cls");

				int rankInput;
				cout << "Введите ранг" << endl;
				cin >> rankInput;

				vector<int> vecUnranked = test.getUnrank(rankInput);

				cout << endl << "Подмножество с рангом " << rankInput << ": ";
				for (int i = 0; i < vecUnranked.size(); i++)
				{
					cout << vecUnranked[i] << " ";
				}

				test.printQuit();
			}
			break;

			case 3:
			{
				system("cls");

				test.printSubsets();

				test.printQuit();
			}
			break;

			case 4:
			{
				system("cls");

				int add_num;
				vector<int> subsetInput;

				cout << "Введите элементы подмножества через пробел, после ввода последнего элемента введите точку" << endl;
				while (cin >> add_num)
				{
					subsetInput.push_back(add_num);
				}
				cin.clear();
				cin.ignore(255, '\n');

				vector<int> result = test.successor(subsetInput);

				cout << "Ранг подмножества - " << test.getRank(subsetInput) << endl << endl;

				if (!result.empty())
				{
					cout << "Следующее подмножество: ";
					for (int i = 0; i < result.size(); i++)
					{
						cout << result[i] << " ";
					}
					cout << endl << "Ранг подмножества - " << test.getRank(result);
				}
				else
				{
					cout << "Вы ввели наивысшее по рангу подмножество" << endl;
				}

				test.printQuit();
			}
			break;

			case 5:
			{
				system("cls");

				vector<int> temp = {};

				cout << "Подмножество: <пустое>";

				for (auto& el : temp)
				{
					cout << el << " ";
				}

				cout << endl << "Его ранг - " << test.getRank(temp) << endl << endl;

				test.UnrecGrayCode(temp);

				test.printQuit();
			}
			break;

			case 6:
			{
				system("cls");

				vector<vector <int>> temp = test.grayCodeSuccessorRec(cntEl);
				test.transGrayCodeRec(temp);

				for (auto el : temp)
				{
					if (el.empty())
					{
						cout << "Подмножество: <пустое>";
						cout << endl << "Его ранг - " << test.getRank(el) << endl << endl;
					}
					else
					{
						cout << "Подмножество: ";
						for (auto num : el)
						{
							cout << num << " ";
						}
						cout << endl << "Его ранг - " << test.getRank(el) << endl << endl;
					}
				}

				test.printQuit();
			}
			break;

			case 7:
			{
				exit(0);
			}
			break;

			}
		}
		break;

		}

	}

}