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
	SetConsoleTitle(L"���������");
	ConsoleCursorVisible(false, 100);

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

	int cntEl;
	cout << "������� ���������� ��������� ���������" << endl;
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
			"				����� ��������� �� �����",
			"			���������� ����� ��������� ������������",
			"		��������� � ����� �� ����� ������������ �� ��������� �����",
			"			��������� � ����� �� ����� ���� �����������",
			"	��������� � ����� �� ����� ���������� ������������ �� ��������� ������������",
			"		��������� ���� ����������� � ������� ������������ ���������",
			"��������� ���� ����������� � ������� ������������ ��������� (����������� ��������)",
			"					�����"
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

				cout << "������� �������� ������������ ����� ������, ����� ����� ���������� �������� ������� �����" << endl;
				while (cin >> add_num)
				{
					subsetInput.push_back(add_num);
				}
				cin.clear();
				cin.ignore(255, '\n');

				cout << "���� ������������ - " << test.getRank(subsetInput);

				test.printQuit();

			}
			break;

			case 2:
			{
				system("cls");

				int rankInput;
				cout << "������� ����" << endl;
				cin >> rankInput;

				vector<int> vecUnranked = test.getUnrank(rankInput);

				cout << endl << "������������ � ������ " << rankInput << ": ";
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

				cout << "������� �������� ������������ ����� ������, ����� ����� ���������� �������� ������� �����" << endl;
				while (cin >> add_num)
				{
					subsetInput.push_back(add_num);
				}
				cin.clear();
				cin.ignore(255, '\n');

				vector<int> result = test.successor(subsetInput);

				cout << "���� ������������ - " << test.getRank(subsetInput) << endl << endl;

				if (!result.empty())
				{
					cout << "��������� ������������: ";
					for (int i = 0; i < result.size(); i++)
					{
						cout << result[i] << " ";
					}
					cout << endl << "���� ������������ - " << test.getRank(result);
				}
				else
				{
					cout << "�� ����� ��������� �� ����� ������������" << endl;
				}

				test.printQuit();
			}
			break;

			case 5:
			{
				system("cls");

				vector<int> temp = {};

				cout << "������������: <������>";

				for (auto& el : temp)
				{
					cout << el << " ";
				}

				cout << endl << "��� ���� - " << test.getRank(temp) << endl << endl;

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
						cout << "������������: <������>";
						cout << endl << "��� ���� - " << test.getRank(el) << endl << endl;
					}
					else
					{
						cout << "������������: ";
						for (auto num : el)
						{
							cout << num << " ";
						}
						cout << endl << "��� ���� - " << test.getRank(el) << endl << endl;
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