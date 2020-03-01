#include "DataSourceSerieDiscrete.h"

DataSourceSerieDiscrete::DataSourceSerieDiscrete(const char* Nom, const char* Sujet, int eff, Liste<Data1D>* pl): DataSource(Nom,Sujet, eff)
{
	cout << "test"<<endl;
	L = pl;
	cout << "constructeur" << endl;
	setType(DISCRETE);
	CalculEffTotal();
}

void DataSourceSerieDiscrete::Rapport()
{
	cout << "DataSourceSerieDiscrete" << endl;
	cout << "Nom: " << getNom() << endl;
	cout << "Sujet: " << getSujet() << endl;
	L->Affiche();
	//cout << "valeurs:" << L->Affiche() << endl; 
}

void DataSourceSerieDiscrete::CalculEffTotal()
{
	Iterateur<Data1D> it(*L);
	int compteur = 0;
	while(!it.end())
	{
		compteur += it.getpCur()->valeur.getEff();
		it++;
	}	
	setEffTotal(compteur);
}

Liste<Data1D>* DataSourceSerieDiscrete	::getL()
{
	return L;
}
