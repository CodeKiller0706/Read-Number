#ifndef _POINT_FUN_
#define _POINT_FUN_

#include<vector>
#include<fstream>
#include<iostream>

using std::vector;
using std::ofstream;
using std::ostream;

class Point
{
public:
	Point(int rank, double x, double y, double z);

	const int PointRank() const;
	const double PointX() const;
	const double PointY() const;
	const double PointZ() const;
	const bool IsValid() const;
	void SetValid(bool flag);
	friend ofstream& operator<<(ofstream& out, const Point& pt);
	friend ostream& operator<<(ostream& out, const Point& pt);

private:
	int _rank;
	double _x;
	double _y;
	double _z;
	bool _isValid;
};

class PointGroup
{
public:
	PointGroup();
	~PointGroup();
	
	void AppendPointByValue(Point* point);
	const double MyNum() const;
	const vector<Point*>& GetPoints() const;

private:
	double _num;
	vector<Point*> _points;
};

class PointPool
{
public:
	static PointPool* GetInstance();
	void AppendPointInPool(Point* point);
	const vector<PointGroup*>& GetData() const;
	void ConfirmData();

private:
	PointPool();
	~PointPool();
	static PointPool* _mpInstance;
	vector<PointGroup*> _pointgroups;
};

#endif