#include"PointPool.h"
#include "IOFile.h"

//Point class
Point::Point(int rank, double x, double y, double z)
	:_rank(rank),
	_x(x),
	_y(y),
	_z(z),
	_isValid(true)
{
}

const int Point::PointRank() const
{
	return _rank;
}

const double Point::PointX() const
{
	return _x;
}

const double Point::PointY() const
{
	return _y;
}

const double Point::PointZ() const
{
	return _z;
}

const bool Point::IsValid() const
{
	return _isValid;
}

void Point::SetValid(bool flag) 
{
	_isValid = flag;
}

ofstream& operator<<(ofstream& out, const Point& pt)
{
	out << pt._rank << "  " << pt._x << "  " << pt._y << "  " << pt._z << std::endl;
	return out;
}

ostream& operator<<(ostream& out, const Point& pt)
{
	out << pt._rank << "  " << pt._x << "  " << pt._y << "  " << pt._z << std::endl;
	return out;
}

//Point Group Calss
PointGroup::PointGroup()
	:_num(0)
{
	_points.reserve(SIZE);
}

PointGroup::~PointGroup()
{
	for (auto& item : _points)
		delete item;
}

void PointGroup::AppendPointByValue(Point* point)
{
	if (_points.size() == 0)
	{
		_points.push_back(point);
		_num = point->PointX();
		return;
	}

	auto iter = _points.begin();
	for(; iter != _points.end(); iter++)
	{
		if (point->PointY() < (*iter)->PointY())
		{
			iter = _points.insert(iter, point);
			break;
		}
	}
	if (iter == _points.end()) _points.push_back(point);
}

const double PointGroup::MyNum() const
{
	return _num;
}

const vector<Point*>& PointGroup::GetPoints() const
{
	return _points;
}

//Point Pool Class
PointPool* PointPool::_mpInstance = nullptr;

PointPool::PointPool()
{
	_pointgroups.reserve(SIZE);
}

PointPool::~PointPool()
{
	delete _mpInstance;
	for (auto& item : _pointgroups)
		delete item;
}

PointPool* PointPool::GetInstance()
{
	if (_mpInstance == nullptr)
	{
		_mpInstance = new PointPool();
	}
	return _mpInstance;
}

void PointPool::AppendPointInPool(Point* point)
{
	//only find the right group here
	//its group's job to append it in group
	if (_pointgroups.size() == 0)
	{
		PointGroup* pNewGroup = new PointGroup();
		_pointgroups.push_back(pNewGroup);
		pNewGroup->AppendPointByValue(point);
		return;
	}

	for (auto iter = _pointgroups.begin(); iter != _pointgroups.end(); iter++)
	{
		if ((*iter)->MyNum() == point->PointX())
		{
			(*iter)->AppendPointByValue(point);
			return;
		}
		else if (point->PointX() < (*iter)->MyNum())
		{
			PointGroup* pNewGroup = new PointGroup();
			_pointgroups.insert(iter, pNewGroup);
			pNewGroup->AppendPointByValue(point);
			return;
		}
	}

	PointGroup* pNewGroup = new PointGroup();
	_pointgroups.push_back(pNewGroup);
	pNewGroup->AppendPointByValue(point);
}

const vector<PointGroup*>& PointPool::GetData() const
{
	return _pointgroups;
}

void PointPool::ConfirmData()
{
	//in same y judge the validity
	for (auto& pPointGroup : _pointgroups)
	{
		Point* pLastPoint = nullptr;
		double zMax = 0;
		double zMin = 0;
		bool isFirst = true;
		for (auto& pPoint : pPointGroup->GetPoints())
		{
			if (pLastPoint == nullptr)
			{
				pLastPoint = pPoint;
				continue;
			}
			if (pLastPoint->PointY() == pPoint->PointY() && isFirst)
			{
				(pLastPoint->PointZ() > pPoint->PointZ()) ? zMax = pLastPoint->PointZ(), zMin = pPoint->PointZ() : zMax = pPoint->PointZ(), zMin = pLastPoint->PointZ();
				pLastPoint = pPoint;
				isFirst = false;
				continue;
			}
			else
			{
				if (pLastPoint->PointY() == pPoint->PointY() && !isFirst)
				{
					if (zMin > pPoint->PointZ())
					{
						zMin = pPoint->PointZ();
						pLastPoint = pPoint;
						continue;
					}
					if (zMax < pPoint->PointZ())
					{
						zMax = pPoint->PointZ();
						pLastPoint = pPoint;
						continue;
					}
					pPoint->SetValid(false);
					continue;
				}
				else
					isFirst = true;
			}
		}
	}
}