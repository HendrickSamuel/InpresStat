#ifndef DATA2D_H
#define DATA2D_H

#include <iostream>
using namespace std;


class Data2D {

	private:
		float Val1;
		float Val2;
	public: 
		Data2D(float, float);
		Data2D();
		
		float getVal1() const;
		float getVal2() const;
		
		void setVal1(float);
		void setVal2(float);
		
		friend ostream& operator<<(ostream&,const Data2D&);
		
};

#endif
