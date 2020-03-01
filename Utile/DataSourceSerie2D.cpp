#include "DataSourceSerie2D.h"

DataSourceSerie2D::DataSourceSerie2D(const char* nom, const char* sujet1, int type1,const char* sujet2,int type2, Liste<Data2D>* liste):DataSource(nom,sujet1,type1)
{
	setSujet2(sujet2);
	L = liste;
	setType2(type2);
	setEffTotal(liste->getNombreElements());	
}

void DataSourceSerie2D::setSujet2(const char* chaineget)
{
	if(Sujet2)
	{
		delete Sujet2;
	}
	if(chaineget)
	{
		Sujet2 = new char[strlen(chaineget)+1];
		strcpy(Sujet2,chaineget);
	}
	else
	{
	 Sujet2 = NULL;
	}
}

void DataSourceSerie2D::setType2(int type)
{
	Type2 = type;
}

const char* DataSourceSerie2D::getSujet2()
{
	return Sujet2;
}

int DataSourceSerie2D::getType2()
{
	return Type2;
}

Liste<Data2D>* DataSourceSerie2D::getL()
{
	return L;
}

void DataSourceSerie2D::Affiche()
{
	cout <<"Titre : "<< getNom() << endl;
	cout <<"Sujet de l'etude: "<< getSujet() << " -- " << getSujet2() << endl;
	cout <<"Eff Total: " << getEffTotal() << endl;
	cout <<"type1: " <<getType() << " type2: " << getType2() << endl << endl;
	cout <<"Valeurs: " << endl;
	getL()->Affiche();
	
	
}


