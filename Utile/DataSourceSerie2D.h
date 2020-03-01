#ifndef DATASOURCESERIE2D_H
#define DATASOURCESERIE2D_H

#include "DataSource.h"
#include "Liste.h"
#include "Data2D.h"
#include "Iterateur.h"
#include <iostream>

using namespace std;
class DataSourceSerie2D:public DataSource
{
	private:
		Liste<Data2D>* L;
		char* Sujet2;
		int Type2;	
	public:
		void setSujet2(const char*);
		void setType2(int);
		DataSourceSerie2D(const char*, const char*, int,const char*,int, Liste<Data2D>*);
		
		const char* getSujet2(void);
		int getType2(void);
		Liste<Data2D>* getL(void);
		void Affiche(void);
	
};

#endif
