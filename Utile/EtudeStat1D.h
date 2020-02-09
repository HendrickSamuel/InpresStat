#ifndef ETUDESTAT1D_H
#define ETUDESTAT1D_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <QApplication>
#include "Echantillon.h"

#include "Liste.h"
#include "Data1D.h"
#include "ListeTriee.h"
#include "Iterateur.h"
#include "DataSourceSerieDiscrete.h"
#include "DataSourceSerieContinue.h"
//extern QApplication* a;

using namespace std;

class EtudeStat1D {
	private:
		Echantillon* E;
		float Moyenne;
		float EcartType;
		float Mediane;
		float Mode[3];
		
		void getFileContent(ifstream&,ListeTriee<float>&,int);	
		Liste<Data1D> transfereListe(ListeTriee<float>&);	
		DataSource* methodeContinue(const char*, const char*,int,int,Liste<Data1D>*);
		
	public:
		EtudeStat1D(char* , int);
		
		void StartFichier(char* ,int);
		
		float getMoyenne();
		float getMode();
		float getMediane();
		
		float getEcartType();
		float getEtendue();
		
		void AfficheRapport();
};

#endif