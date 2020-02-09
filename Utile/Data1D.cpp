#include "Data1D.h"

Data1D::Data1D(float val, int eff)
{
	setVal(val);
	setEff(eff);
}

Data1D::Data1D()
{
	setVal(0);
	setEff(0);
}

float Data1D::getVal() const
{
	return Val;
}

int Data1D::getEff() const
{
	return Eff;
}

void Data1D::setVal(float val)
{
	Val = val;
}

void Data1D::setEff(int eff)
{
	Eff = eff;
}

ostream& operator<<(ostream& s,const Data1D& d)
{
	s << d.getVal() << " " << d.getEff() << endl;
	return s;
}
