#include "Data2D.h"

Data2D::Data2D(float val1, float val2)
{
	setVal1(val1);
	setVal2(val2);
}

Data2D::Data2D()
{
	setVal1(0);
	setVal2(0);
}

float Data2D::getVal1() const
{
	return Val1;
}

float Data2D::getVal2() const
{
	return Val2;
}

void Data2D::setVal1(float val)
{
	Val1 = val;
}

void Data2D::setVal2(float val)
{
	Val2 = val;
}
ostream& operator<<(ostream& s,const Data2D& d)
{
	s << d.getVal1() << " \t " << d.getVal2() << endl;
	return s;
}

bool Data2D::operator<(const Data2D& other)
{
	return (this->Val1 < other.Val1 && this->Val2 < other.Val2);
}
