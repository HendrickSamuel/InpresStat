#include "DataSourceSerieContinue.h"

DataSourceSerieContinue::DataSourceSerieContinue(const char* nom, const char* sujet, int eff, int type, Liste<Data1D>* pl): DataSource(nom,sujet, eff, type)
{
	cout << "test"<<endl;
	L = pl;
	cout << "constructeur" << endl;
}

DataSourceSerieContinue::DataSourceSerieContinue(DataSourceSerieContinue& old)
{
	L = old.L;
	setNom(old.getNom());
	setSujet(old.getSujet());
}

void DataSourceSerieContinue::Rapport()
{
	cout << "DataSourceSerieDiscrete" << endl;
	if(Nom)
		cout << "Nom: " << Nom << endl;
	if(Sujet)
		cout << "Sujet: " << Sujet << endl;
	L->Affiche();
	//cout << "valeurs:" << L->Affiche() << endl; 
}
