#include "EtudeStat1D.h"

/* ------------------ CONSTRUCTEURS -------------------*/

EtudeStat1D::EtudeStat1D(char* file, int col)
{
	E = NULL;
	E = new Echantillon(file,col);
	
//	DataSourceSerieContinue* pointeurCData = dynamic_cast<DataSourceSerieContinue*>(E->getSource());
//	if(pointeurCData)
//	{
//		cout << "CECI EST UNE CONTINUE" << endl;
//	}

//	DataSourceSerieDiscrete* pointeurDData = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource());
//	if(pointeurDData)
//	{
//		cout << "CECI EST UNE DISCRETE" << endl;
//		pointeurDData->Rapport();
//	}
	demarreCalcul();
	AfficheRapport();
}

/* ------------------- PRIVE ----------------------*/
		/*-------- SETTERS ---------*/
void EtudeStat1D::setMoyenne(float val)
{
	Moyenne = val;
}

void EtudeStat1D::setMediane(float val)
{
	Mediane = val;
}

void EtudeStat1D::setMode(float val1, float val2, float val3)
{
	Mode[0] = val1;
	Mode[1] = val2;
	Mode[2] = val3;
}
		/*--------  CALCULS ---------*/
float EtudeStat1D::CalculMoyenne()
{
	Liste<Data1D>*L;
	DataSourceSerieContinue* pointeurCData = dynamic_cast<DataSourceSerieContinue*>(E->getSource());
	if(pointeurCData)
	{
		L = pointeurCData->getListe();
	}

	DataSourceSerieDiscrete* pointeurDData = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource());
	if(pointeurDData)
	{
		L = pointeurDData->getListe();
	}
	
	Iterateur<Data1D> it(*L);
	float moy = 0;
	while(!it.end())
	{
		moy += (it.getpCur()->valeur.getVal() * it.getpCur()->valeur.getEff());
		it++;
	}
	moy /= E->getSource()->getEffTotal();
	
	return moy;
}

float EtudeStat1D::CalculMediane()
{
	Liste<Data1D>*L;
	DataSource* ds = E->getSource();
	DataSourceSerieContinue* pointeurCData = dynamic_cast<DataSourceSerieContinue*>(ds);
	if(pointeurCData)
	{
		L = pointeurCData->getListe();
	}

	DataSourceSerieDiscrete* pointeurDData = dynamic_cast<DataSourceSerieDiscrete*>(ds);
	if(pointeurDData)
	{
		L = pointeurDData->getListe();
	}

	// if mode 
	if(ds->getType() == CONTINUE)
	{
		cout << "calculMediane continue" << endl;
	}
	else
	if(ds->getType() == DISCRETE)
	{
		cout << "calculMediane discrete" << endl;
	}
}

/* ------------------- PUBLIC ----------------------*/

void EtudeStat1D::demarreCalcul()
{
	setMoyenne(CalculMoyenne());
	setMediane(CalculMediane());
}
		
float EtudeStat1D::getMoyenne() const
{
	return Moyenne;
}

const float* EtudeStat1D::getMode() const
{
	return Mode;
}

float EtudeStat1D::getMediane() const
{
	return Mediane;
}

float EtudeStat1D::getEcartType() const
{
	return EcartType;
}

float EtudeStat1D::getEtendue() const
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
	DataSourceSerieContinue* pointeurCData = dynamic_cast<DataSourceSerieContinue*>(E->getSource());
	if(pointeurCData)
	{
		pointeurCData->getListe()->Affiche();
	}

	DataSourceSerieDiscrete* pointeurDData = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource());
	if(pointeurDData)
	{
		pointeurDData->getListe()->Affiche();
	}
	//
	
	cout << "---------" << endl;
	cout << "Effectif total : " << E->getSource()->getEffTotal() << endl;
	cout << "Moyenne : " << getMoyenne() <<endl;/*
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
