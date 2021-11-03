#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"PointPool.h"
#include"IOFile.h"

using namespace std;

int ReadAndSaveData(int systemstatus)
{
	IOFile inFile;
	inFile.ReadFile();
	inFile.SaveDataInNumber();

	PointPool* pointpool = PointPool::GetInstance();
	pointpool->ConfirmData();

	inFile.OutPutData();

	return systemstatus;
}

int main()
{
	int systemstatus = 1;
	ReadAndSaveData(systemstatus);
	
	return systemstatus;
}

