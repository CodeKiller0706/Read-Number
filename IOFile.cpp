#include<fstream>
#include<iostream>
#include "IOFile.h"
#include "PointPool.h"

using std::ifstream;
using std::ofstream;
using std::ostream;

IOFile::IOFile(const char* delimiter, string filePos)
	:_delimiter(delimiter)
	,_filePos(filePos)
{
	_data.reserve(SIZE);
}

IOFile::~IOFile()
{

}

const vector<string>& IOFile::Data()
{
	return _data;
}

void IOFile::ReadFile()
{
	ifstream inFile(_filePos);
	if (!inFile)
	{
		std::cout << "can not open file!" << std::endl;
		return;
	}
	string lineString;
	while (getline(inFile, lineString))
	{
		char* nextLine = nullptr;
		char* singleStrings = const_cast<char*>(lineString.c_str());
		char* sinString = strtok_s(singleStrings, _delimiter, &nextLine);
		while (sinString != nullptr)
		{
			_data.push_back(sinString);
			sinString = strtok_s(nullptr, _delimiter, &nextLine);
			if (_data.size() % VALIDNUM == 0)
			{
				break;
			}
		}
	}
}

void IOFile::SaveDataInNumber()
{
	for (int i = 1; i < _data.size(); i = i + VALIDNUM)
	{
		int rank = atoi(_data[i].c_str());
		double x = atof(_data[i + 1].c_str());
		double y = atof(_data[i + 2].c_str());
		double z = atof(_data[i + 3].c_str());
		Point* point = new Point(rank, x, y, z);
		PointPool* pointpool = PointPool::GetInstance();
		pointpool->AppendPointInPool(point);
	}
}

void IOFile::OutPutData()
{
	ofstream outFile("D:\\Summer\\node_out.txt");
	if (!outFile)
	{
		std::cout << "can not create file!" << std::endl;
		return;
	}

	PointPool* pPointPool = PointPool::GetInstance();
	pPointPool->ConfirmData();
	vector<PointGroup*> pGroupData = pPointPool->GetData();
	for (auto& group : pGroupData)
	{
		for (auto& point : group->GetPoints())
		{
			if (point->IsValid())
				outFile << *point << std::endl;
		}
	}
}