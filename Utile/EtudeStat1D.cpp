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

void EtudeStat1D::setEcart(float val)
{
	EcartType = val;
}
		/*--------  CALCULS ---------*/
float EtudeStat1D::CalculMoyenne()
{
	Liste<Data1D>*L;
	DataSourceSerieContinue* pointeurCData = dynamic_cast<DataSourceSerieContinue*>(E->getSource());
	if(pointeurCData)
	{
		L = pointeurCData->getL();
		Iterateur<Data1D> it(*L);
		float moy = 0;
		while(!it.end())
		{
			moy += ((it.getpCur()->valeur.getVal()+ (pointeurCData->getIntervalle()/2)) * it.getpCur()->valeur.getEff());
			it++;
		}
		moy /= E->getSource()->getEffTotal();
	
		return moy;
	}

	DataSourceSerieDiscrete* pointeurDData = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource());
	if(pointeurDData)
	{
		L = pointeurDData->getL();
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
	

}

float EtudeStat1D::CalculMediane()
{
	Liste<Data1D>*L;
	DataSource* ds = E->getSource();
	int compteur = 0;
	int limite = ds->getEffTotal()/2;
	Data1D nieme, nieme2;
	float effinf = 0, effinf2 = 0;
	float mediane = 0;
	bool estPair = true;
	bool niemeSet = false, nieme2Set = false;
	bool isDone = false;
	
	if(ds->getEffTotal()%2 != 0)
	{
		estPair = false;
		limite ++;			
	}
		
	
	DataSourceSerieContinue* pointeurCData = dynamic_cast<DataSourceSerieContinue*>(ds);
	if(pointeurCData)
	{
		L = pointeurCData->getL();
	}

	DataSourceSerieDiscrete* pointeurDData = dynamic_cast<DataSourceSerieDiscrete*>(ds);
	if(pointeurDData)
	{
		L = pointeurDData->getL();
	}
	
	Iterateur<Data1D> it(*L);
	while(!it.end() && !isDone)
	{
		compteur += it.getpCur()->valeur.getEff();
		if(!niemeSet)
		{
			if(compteur >= limite)
			{
				nieme.setVal( ((Data1D)it).getVal() );
				nieme.setEff( ((Data1D)it).getEff() );
				niemeSet = true;
			}
			else
				effinf+= it.getpCur()->valeur.getEff();

		}
			
		if(!nieme2Set)
		{
			if(compteur >= limite+1)
			{
				nieme2.setVal( ((Data1D)it).getVal() );
				nieme2.setEff( ((Data1D)it).getEff() );
				nieme2Set = true;
			}
			else
				effinf2+= it.getpCur()->valeur.getEff();
		}	
		
		it++;
		
		if(nieme2Set && niemeSet)
			isDone = true;
	}
	/* -- j'ai nieme et nieme+1 si besoin -- */

	// if mode 
	if(ds->getType() == CONTINUE)
	{
//		if(pointeurCData == NULL)
//			throw BaseException()
		cout << "calculMediane continue" << endl;
		if(!estPair)
		{
			cout << "mediane inpair" << endl;
			cout << "n " << nieme << endl;

			float pos = limite - effinf;
			cout << "lim " << limite << " effinf " << effinf << endl;
			cout << " pos " << pos <<endl;
			mediane = nieme.getVal() + ( pointeurCData->getIntervalle() / nieme.getEff()  ) * pos;
			return mediane;
			// borne inf + etendue/effectif * (pos dans l'intervalle)
		}
		else
		{
			cout << "mediane pair" << endl;
			cout << "n " << nieme << " n+1 " << nieme2 << endl;
			float pos1 = limite - effinf;
			float vtemp1 = nieme.getVal() + ( pointeurCData->getIntervalle() / nieme.getEff()  ) * pos1;
			
			float pos2 = limite - effinf2;
			float vtemp2 = nieme.getVal() + ( pointeurCData->getIntervalle() / nieme.getEff()  ) * pos2;
			
			mediane = (vtemp1 + vtemp2) / 2;
			return mediane;
			
		}
	}

	if(ds->getType() == DISCRETE)
	{
		cout << "calculMediane discrete" << endl;
		if(estPair)
		{
			cout << "mediane pair" << endl;
			mediane = (nieme.getVal() + nieme2.getVal()) / 2;
			return mediane;
		}
		else
		{
			mediane = nieme.getVal();
			return mediane;
		}
	}
	
	
	
	return mediane;
}

float EtudeStat1D::CalculEcart()
{
	float val = 0;
	float val2 = 0;

	float ecart = 0;
	DataSource* ds = E->getSource();
	Liste<Data1D> *L;
	DataSourceSerieContinue* pointeurCData = dynamic_cast<DataSourceSerieContinue*>(ds);
	if(pointeurCData)
	{
		L = pointeurCData->getL();
		Iterateur<Data1D> it(*L);
	
		while(!it.end())
		{
			val += it.getpCur()->valeur.getEff() * pow(it.getpCur()->valeur.getVal() + pointeurCData->getIntervalle()/2,2);
			val2 += it.getpCur()->valeur.getEff() * (it.getpCur()->valeur.getVal() + pointeurCData->getIntervalle()/2);
			it++;
		}
		val2 = pow(val2,2);
		val2 = val2/ds->getEffTotal();
		ecart = (val - val2)/ds->getEffTotal();
		ecart = sqrt(ecart);
	
		return ecart;
	}

	DataSourceSerieDiscrete* pointeurDData = dynamic_cast<DataSourceSerieDiscrete*>(ds);
	if(pointeurDData)
	{
		L = pointeurDData->getL();
		Iterateur<Data1D> it(*L);
	
		while(!it.end())
		{
			val += it.getpCur()->valeur.getEff() * pow(it.getpCur()->valeur.getVal(),2);
			val2 += it.getpCur()->valeur.getEff() * (it.getpCur()->valeur.getVal());
			it++;
		}
		val2 = pow(val2,2);
		val2 = val2/ds->getEffTotal();
		ecart = (val - val2)/ds->getEffTotal();
		ecart = sqrt(ecart);
		
		cout << "ecart: " << ecart << endl;		
		
		return ecart;
	
	}
	return 0;
	
}

float* EtudeStat1D::CalculMode()
{
	float *mod = new float[3];
	Liste<Data1D> *L;
	DataSource* ds = E->getSource();
	int val;
	int pos = 0;
	
	DataSourceSerieContinue* pointeurCData = dynamic_cast<DataSourceSerieContinue*>(ds);
	if(pointeurCData)
	{
		L = pointeurCData->getL();
	}

	DataSourceSerieDiscrete* pointeurDData = dynamic_cast<DataSourceSerieDiscrete*>(ds);
	if(pointeurDData)
	{
		L = pointeurDData->getL();
	}
	Iterateur<Data1D> it(*L);
	
	val = ((Data1D)it).getEff();
	
	while(!it.end())
	{
		if(((Data1D)it).getEff() > val)
		{
			val = ((Data1D)it).getEff();
			mod[0] = ((Data1D)it).getVal();
			mod[1] = 0;
			mod[2] = 0;
			pos = 1;
		}
		else
		if(((Data1D)it).getEff() == val)
		{
			if(pos <= 2)
			{
				mod[pos] = ((Data1D)it).getVal();
				pos ++;
			}
		}
		it++;
	}
	return mod;
}

float EtudeStat1D::CalculCoeffVar()
{
	float ecart = getEcartType();
	float moy = getMoyenne();
	return (ecart / moy)*100; // en % ? 
}

/* ------------------- PUBLIC ----------------------*/

void EtudeStat1D::demarreCalcul()
{
	setMoyenne(CalculMoyenne());
	setMediane(CalculMediane());
	setEcart(CalculEcart());
	float* mod = CalculMode();
	setMode(mod[0],mod[1],mod[2]);
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

Echantillon* EtudeStat1D::getE() const
{
	return E;
}

void EtudeStat1D::AfficheRapport()
{
	Liste<Data1D> *L;
	DataSourceSerieContinue* pointeurCData = dynamic_cast<DataSourceSerieContinue*>(E->getSource());
	if(pointeurCData)
	{
		L = pointeurCData->getL();
	}

	DataSourceSerieDiscrete* pointeurDData = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource());
	if(pointeurDData)
	{
		L = pointeurDData->getL();
	}
	
	cout << "Nom : " << E->getSource()->getNom() << endl;
	cout << "Sujet de l'étude : " << E->getSource()->getSujet() << endl;
	cout << "type : " << E->getSource()->getType() << endl;
	cout << "Donnees :" <<endl;
	cout << "---------" << endl;
	
	// dynamic cast pour afficher la liste
	L->Affiche();
	//
	
	cout << "---------" << endl;
	cout << "Effectif total : " << E->getSource()->getEffTotal() << endl;
	cout << "Moyenne : " << getMoyenne() <<endl;
	cout << "Médiane : " << getMediane() << endl; 
	cout << "Mode : " << endl;
	cout << Mode[0] <<":" << Mode[1] << ":" << Mode[2] << endl;
	cout << "Ecart type : " << getEcartType() << endl;
	cout << "Coefficient de variation : % " << CalculCoeffVar() << endl;
	
	cout << endl<<"Contrôle de qualité: " << endl;
	cout << "valeur min: " << L->getElement(0).getVal() << endl;
	cout << "valeur Maximum : " << L->getElement(L->getNombreElements()-1).getVal() << endl;
	cout << "Coefficient de variation : % " << CalculCoeffVar()/100 << endl;


	
	if(E->getSource()->getType() == DISCRETE)
	{
		GraphStat1DDiscrete w(*this);	
		w.show();
		a->exec();
			
	}
	else
	{
		GraphStat1DContinue w(*this);
		w.show();
		a->exec();
	}
}
