// TestIO.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream modelFile;
	modelFile.open("Test.txt");
	char output[1000000];
	if (modelFile.is_open())
	{
		while (!modelFile.eof())
		{
			modelFile >> output;
			cout << output;
		}
	}
	system("pause");


	return 0;
}
