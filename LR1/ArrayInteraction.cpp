#include "ArrayInteraction.h"

ArrayInteraction::ArrayInteraction(int cnt)
{
	cntNumbers = cnt;
	cntSubsets = pow(2, cntNumbers);
}

void ArrayInteraction::genVec()
{
	for (int i = 0; i < cntNumbers; i++)
	{
		variety.push_back(i + 1);
	}
}

vector<int> ArrayInteraction::getVec()
{
	return variety;
}

int ArrayInteraction::getRank(vector<int> subset)
{
	int rank = 0;

	for (int i = 1; i <= cntNumbers; i++)
	{
		if (find(subset.begin(), subset.end(), i) != subset.end())
		{
			rank += pow(2, cntNumbers - i);
		}
	}

	return rank;
}

vector<int> ArrayInteraction::getUnrank(int rank)
{
	vector<int> subset;

	for (int i = cntNumbers; i >= 1; i--)
	{
		if (rank % 2 == 1)
		{
			subset.push_back(i);
		}

		rank /= 2;
	}

	sort(subset.begin(), subset.end());

	return subset;
}

vector<int> ArrayInteraction::successor(vector<int> prevSubset)
{
	vector<int> temp;

	if (getRank(prevSubset) < cntSubsets - 1)
	{
		temp = getUnrank(getRank(prevSubset) + 1);
	}
	else if (getRank(prevSubset) == cntSubsets - 1)
	{
		temp.clear();
	}

	return temp;
}

void ArrayInteraction::printSubsets()
{
	for (int i = 0; i < cntSubsets; i++)
	{
		vector<int> temp = getUnrank(i);
		//sort(temp.begin(), temp.end());
		cout << i << " подмножество: ";
		if (temp.empty())
		{
			cout << "<пустое>";
		}
		else
		{
			for (int i = 0; i < temp.size(); i++)
			{
				cout << temp[i] << " ";
			}
		}
		cout << endl;
	}
}

void ArrayInteraction::printVec()
{
	cout << "Заданное множество: ";
	for (int i = 0; i < variety.size(); i++)
	{
		cout << variety[i] << " ";
	}
	cout << endl;
}

void ArrayInteraction::printQuit()
{
	cout << endl << endl << "Backspace - возврат в меню";

	int answ = _getch();
	bool press = false;

	while (!press)
	{
		if (answ == 8)
		{
			press = true;
			break;
		}
		else
		{
			answ = _getch();
		}
	}

	system("cls");
}

vector<int> ArrayInteraction::grayCodeSuccessorUnrec(vector<int> subset)
{
	vector<int> tempCnt = { cntNumbers };
	vector<int> combiVec;

	if (subset.size() % 2 == 0)
	{
		for (auto& element : subset) 
		{
			if (find(tempCnt.begin(), tempCnt.end(), element) == tempCnt.end()) 
			{
				combiVec.push_back(element);
			}
		}

		for (auto& element : tempCnt) 
		{
			if (find(subset.begin(), subset.end(), element) == subset.end())
			{
				combiVec.push_back(element);
			}
		}

		return combiVec;
	}
	else
	{	
		int j = cntNumbers;

		while (j > 0 && (find(subset.begin(), subset.end(), j) == subset.end()))
		{
			j--;
		}

		if (j == 1)
		{
			combiVec.clear();
			return combiVec;
		}

		vector<int> tempJ = { j - 1 };

		for (auto& element : subset)
		{
			if (find(tempJ.begin(), tempJ.end(), element) == tempJ.end())
			{
				combiVec.push_back(element);
			}
		}

		for (auto& element : tempJ)
		{
			if (find(subset.begin(), subset.end(), element) == subset.end())
			{
				combiVec.push_back(element);
			}
		}

		return combiVec;
	}
}

void ArrayInteraction::UnrecGrayCode(vector<int> subset)
{
	if (grayCodeSuccessorUnrec(subset).empty())
	{
		return;
	}

	vector<int> temp = grayCodeSuccessorUnrec(subset);
	sort(temp.begin(), temp.end());

	cout << "Подмножество: ";
	for (auto& el : temp)
	{
		cout << el << " ";
	}

	cout << endl << "Его ранг - " << getRank(temp) << endl << endl;

	UnrecGrayCode(temp);
}

vector<vector<int>> ArrayInteraction::grayCodeSuccessorRec(int step)
{
	if (step == 1)
	{
		return { {0},
				 {1} };
	}

	vector<vector<int>> prevCode = grayCodeSuccessorRec(step - 1);

	vector<vector<int>> result;
	for (int i = 0; i < prevCode.size(); i++)
	{
		vector<int> temp;
		temp.push_back(0);
		for (auto el : prevCode[i])
		{
			temp.push_back(el);
		}
		result.push_back(temp);
	}
	for (int i = prevCode.size() - 1; i >= 0; i--)
	{
		vector<int> temp;
		temp.push_back(1);
		for (auto el : prevCode[i])
		{
			temp.push_back(el);
		}
		result.push_back(temp);
	}

	return result;
}

void ArrayInteraction::transGrayCodeRec(vector<vector<int>>& result)
{
	for (auto& row : result)
	{
		for (int i = 0; i < row.size(); i++)
		{
			if (row[i] == 1)
			{
				row[i] = variety[i];
			}
		}
		row.erase(remove(row.begin(), row.end(), 0), row.end());
	}
}