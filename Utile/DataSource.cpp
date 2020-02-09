#include "DataSource.h"
#include <iostream>
using namespace std;

DataSource::DataSource()
{
	Nom = NULL;
	Sujet = NULL;
}

DataSource::DataSource(const char* nom, const char* _sujet, int eff, int type)
{
	Nom = NULL;
	Sujet = NULL;
	setNom(nom);
	setSujet(_sujet);
	
}

DataSource::~DataSource()
{
	if(Nom)
		delete Nom;
	if(Sujet)
		delete Sujet;
}

		/* -- GETTERS --*/
		
const char* DataSource::getNom() const
{
	return Nom;
}
		
const char* DataSource::getSujet() const
{
	return Sujet;
}

int DataSource::getEffTotal() const
{
	return EffTotal;
}

int DataSource::getType() const
{
	return Type;
}
		
		/* -- SETTERS --*/
		
void DataSource::setNom(const char* chaineget)
{
	if(Nom)
	{
		delete Nom;
	}
	if(chaineget)
	{
		Nom = new char[strlen(chaineget)+1];
		strcpy(Nom,chaineget);
	}
	else
	{
	 Nom = NULL;
	}
}

void DataSource::setSujet(const char* chaineget){
	if(Sujet)
	{
		delete Sujet;
	}
	if(chaineget)
	{
		Sujet = new char[strlen(chaineget)+1];
		strcpy(Sujet,chaineget);
	}
	else
	{
	 Sujet = NULL;
	}
}

void DataSource::setEffTotal(int eff)
{
	EffTotal = eff;
}

void DataSource::setType(int type)
{
	Type = type;
}

