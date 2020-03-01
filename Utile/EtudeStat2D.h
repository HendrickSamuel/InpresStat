#ifndef ETUDESTAT2D_H
#define ETUDESTAT2D_H

#include "Liste.h"
#include "Echantillon.h"
#include "Iterateur.h"
#include "BaseException.h"
#include <math.h>

class EtudeStat2D
{
	private:
	Echantillon* E;
	float MoyenneVal1, MoyenneVal2;
	float CoeffA, CoeffB;
	float CoeffCorelation;
	
	// calculs;
	public:
	EtudeStat2D(char*, int,int);
	// setters
	
	float CalculCorr();
	float CalculCorrA();
	float CalculCorrB();
	float CalculMoy(int);
	
	void setMoy1(float);
	void setMoy2(float);
	void setCoeffA(float);
	void setCoeffB(float);
	void setCorrel(float);
	
	float getMoy1();
	float getMoy2();
	float getCoeffA();
	float getCoeffB();
	float getCorrel();
	
	void AfficheRapport();
	void Previsions();	
	
	
};

#endif
