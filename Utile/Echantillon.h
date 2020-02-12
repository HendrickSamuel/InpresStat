#ifndef ECHANTILLON_H
#define ECHANTILLON_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <QApplication>
#include "Echantillon.h"

#include "Liste.h"
#include "Data1D.h"
#include "ListeTriee.h"
#include "Iterateur.h"
#include "DataSource.h"
#include "DataSourceSerieDiscrete.h"
#include "DataSourceSerieContinue.h"

using namespace std;
class Echantillon
{
	private:
		DataSource* Source;
	public:
		Echantillon(char*,int);
		void setSource(DataSource*);
		DataSource* getSource();		
		void GetFileContent1D(char*,int);
		Liste<Data1D> transfereListe(ListeTriee<float>&);
		void getFileData1D(ifstream&,ListeTriee<float>& ,int);
		Echantillon();
};
	
#endif
