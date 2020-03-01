#ifndef DATA1D_H
#define DATA1D_H

#include <iostream>
using namespace std;


class Data1D {

	private:
		float Val;
		int Eff;
	public: 
		Data1D(float, int);
		Data1D();
		
		float getVal() const;
		int getEff() const;
		
		void setVal(float);
		void setEff(int);
		
		friend ostream& operator<<(ostream&,const Data1D&);
		
};

#endif

