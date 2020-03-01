#ifndef ECHANTILLON_H
#define ECHANTILLON_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <QApplication>
#include "Echantillon.h"

#include "Liste.h"
#include "Data1D.h"
#include "Data2D.h"
#include "ListeTriee.h"
#include "Iterateur.h"
#include "DataSource.h"
#include "DataSourceSerieDiscrete.h"
#include "DataSourceSerieContinue.h"
#include "DataSourceSerie2D.h"

using namespace std;
class Echantillon
{
	private:
		DataSource* Source;
	public:
		Echantillon(char*,int);
		Echantillon(char*, int, int);
		void setSource(DataSource*);
		DataSource* getSource();		
		void GetFileContent2D(char*,int,int);
		void GetFileContent1D(char*,int);
		Liste<Data1D> transfereListe(ListeTriee<float>&);
		void getFileData1D(ifstream&,ListeTriee<float>& ,int);
		void getFileData2D(ifstream&, Liste<Data2D>* ,int,int);
		Echantillon();
};
	
#endif
