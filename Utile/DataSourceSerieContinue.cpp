#include "DataSourceSerieContinue.h"

DataSourceSerieContinue::DataSourceSerieContinue(const char* nom, const char* sujet, int eff, Liste<Data1D>* pl): DataSource(nom,sujet, eff)
{
	L = pl;
	getIntervale();
	CalculEffTotal();
	setType(CONTINUE);
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
	// afficher min et max.
	CalculEffTotal();
	cout << "Min: " << L->getpTete()->valeur.getVal();
	cout << " Max: " << L->getpQueu()->valeur.getVal() << endl;
	cout << "Eff Total: " << getEffTotal() << endl;
	
	cout << "Encodez votre valeur de début: " ;
	cin >> Debut;
	cout << "Encodez votre intervalle: ";
	cin >> Intervalle; 
	applicIntervale();
}

void DataSourceSerieContinue::applicIntervale()
{
	Iterateur<Data1D> it(*L);
	Liste<Data1D>* NL = new Liste<Data1D>();
	int compteur = 0;
	int borneInf = Debut;	
	while(!it.end())
	{
		if(it.getpCur()->valeur.getVal() < Debut)
		{
			it.remove();
		}
		else
		{
			if(it.getpCur()->valeur.getVal() < borneInf + Intervalle)
			{
				compteur+= it.getpCur()->valeur.getEff();
				it++;
			}
			else
			{
				Data1D data(borneInf,compteur);
				NL->insere(data);
				compteur = 0;
				borneInf = borneInf+ Intervalle;
			}
		}
	
	}
	Data1D data(borneInf,compteur);
	NL->insere(data);
	free(L);
	L = NL;		
}

void DataSourceSerieContinue::CalculEffTotal()
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

Liste<Data1D>* DataSourceSerieContinue::getListe()
{
	return L;
}
