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

void DataSourceSerieContinue::getIntervale()
{
	cout << "Encodez votre valeur de début: " ;
	cin >> Debut;
	cout << "Encodez votre intervalle: ";
	cin >> Intervalle; 
	applicIntervale();
}

void DataSourceSerieContinue::applicIntervale()
{
	cout << "---------------------------" << endl;
	Iterateur<Data1D> it(*L);
	while(!it.end())
	{
		if(it.getpCur()->valeur.getVal() < Debut || it.getpCur()->valeur.getVal() > Debut + Intervalle)
		// verifier si remove plus petit que une certaine valeur
		it.remove();
		it++;	
	}		
}
