#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <Windows.h>
#include <conio.h>

using namespace std;

class ArrayInteraction
{
	int cntSubsets;
	int cntNumbers;

	vector<int> variety;

public:

	ArrayInteraction(int cnt);

	void genVec();
	vector<int> getVec();

	int getRank(vector<int> subset);
	vector<int> getUnrank(int rank);
	vector<int> successor(vector<int> prevSubset);

	void printSubsets();
	void printVec();
	void printQuit();

	vector<int> grayCodeSuccessorUnrec(vector<int> subset);
	void UnrecGrayCode(vector<int> subset); 

	vector<vector<int>> grayCodeSuccessorRec(int step);
	void transGrayCodeRec(vector<vector<int>>& result);
};