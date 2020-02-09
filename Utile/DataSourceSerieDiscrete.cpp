#include "DataSourceSerieDiscrete.h"

DataSourceSerieDiscrete::DataSourceSerieDiscrete(const char* Nom, const char* Sujet, int eff, int type, Liste<Data1D>* pl): DataSource(Nom,Sujet, eff, type)
{
	cout << "test"<<endl;
	L = pl;
	cout << "constructeur" << endl;
}

void DataSourceSerieDiscrete::Rapport()
{
	cout << "DataSourceSerieDiscrete" << endl;
	cout << "Nom: " << getNom() << endl;
	cout << "Sujet: " << getSujet() << endl;
	L->Affiche();
	//cout << "valeurs:" << L->Affiche() << endl; 
}
