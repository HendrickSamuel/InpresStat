#include "EtudeStat1D.h"

EtudeStat1D::EtudeStat1D(char* file, int col)
{
	E = NULL;
	E = new Echantillon(file,col);
	
	DataSourceSerieContinue* pointeurCData = dynamic_cast<DataSourceSerieContinue*>(E->getSource());
	if(pointeurCData)
	{
		cout << "CECI EST UNE CONTINUE" << endl;
		pointeurCData->Rapport();
		pointeurCData->getIntervale();
		pointeurCData->Rapport();
	}

	DataSourceSerieDiscrete* pointeurDData = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource());
	if(pointeurDData)
	{
		cout << "CECI EST UNE DISCRETE" << endl;
		pointeurDData->Rapport();
	}
	
	AfficheRapport();
}

		
float EtudeStat1D::getMoyenne()
{
	return Moyenne;
}

float EtudeStat1D::getMode()
{
	return Mode[0];
}

float EtudeStat1D::getMediane()
{
	return Mediane;
}

float EtudeStat1D::getEcartType()
{
	return EcartType;
}

float EtudeStat1D::getEtendue()
{
	return 0;
}

void EtudeStat1D::AfficheRapport()
{
	cout << "Nom : " << E->getSource()->getNom() << endl;
	cout << "Sujet de l'étude : " << E->getSource()->getSujet() << endl;
	cout << "type : " << E->getSource()->getType() << endl;
	cout << "Donnees :" <<endl;
	cout << "---------" << endl;
	// dynamic cast pour afficher la liste
	
	/*...
	Effectif total :
	Moyenne :
	Médiane :
	Mode :
	0 : 0 : 0
	Ecart type :
	Coefficient de variation : %
	Contrôle de qualité:
	valeur min
	:
	valeur Maximum :
	coefficient de variation :*/
}


/*
	// si mode = C continu // si mode = D discret
	
	while(fb.getline(Tampon, 800))
	{
		float f = atof(Tampon);
		//cout << "Data: " << f << endl;
		liste.insere(f);
	}
	//liste.Affiche();
	cout << "-----------------------------" << endl;	
	// allouer un echantillon
	
	Liste<Data1D> listeData;
	
	Iterateur<float> it(liste);
	
	val = it.getpCur()->valeur;
	compteur = 0;
	
	while(!it.end()){
		if(it.getpCur()->valeur != val)
		{
			Data1D data(val,compteur);
			listeData.insere(data);
			compteur = 0;
		}
		
		val = it.getpCur()->valeur;
		
		compteur++;
		it++;
	}
	
	Data1D data(val,compteur);
	listeData.insere(data);
			
	//listeData.Affiche();
	
	DataSourceSerieDiscrete etude(Nom, Sujet,10,1,&listeData);
	etude.Rapport();
*/
