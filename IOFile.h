#ifndef _IO_FILE_
#define _IO_FILE_

#define SIZE 10000
#define VALIDNUM 5

/*
const SIZE = 10000;
const VALIDNUM = 5;
*/

#include<vector>
#include<string>

using std::vector;
using std::string;

class IOFile
{
public:
	IOFile(const char* delimiter = " " ,string filePos = "D:\\Summer\\node.txt");
	~IOFile();

	const vector<string>& Data();

	//save data interface
	void ReadFile();         //only read five num in one line
	void SaveDataInNumber();

	//output interface
	void OutPutData();

private:
	string _filePos;
	const char* _delimiter;
	string _lineString;
	vector<string> _data;
};

#endif // !IO_FILE_

