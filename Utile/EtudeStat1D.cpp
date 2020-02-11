#include "EtudeStat1D.h"

EtudeStat1D::EtudeStat1D(char* file, int col)
{
	E = NULL;
	E = new Echantillon();
	StartFichier(file, col);
	
	DataSourceSerieContinue* pointeurCData = dynamic_cast<DataSourceSerieContinue*>(E->Source);
	if(pointeurCData)
	{
		cout << "CECI EST UNE CONTINUE" << endl;
		pointeurCData->Rapport();
	}

	DataSourceSerieDiscrete* pointeurDData = dynamic_cast<DataSourceSerieDiscrete*>(E->Source);
	if(pointeurDData)
	{
		cout << "CECI EST UNE DISCRETE" << endl;
		pointeurDData->Rapport();
	}
}

void EtudeStat1D::StartFichier(char* file, int col)
{
	char Tampon[800];
	char Nom[80];
	char Sujet[80];
	
	ListeTriee<float> liste;
	ifstream fb(file,ios::in);
	
	// prise du nom et du sujet
	fb.getline(Tampon, 800);
	cout <<"Nom: " <<Tampon << endl;	
	strcpy(Nom, Tampon);
	
	fb.getline(Tampon, 800);
	cout <<"Sujet: " <<Tampon << endl;
	strcpy(Sujet, Tampon);	
	
	// definir si discret ou continu
	fb.getline(Tampon, 800);
	
	// selectionner la colonne necessaire
	char* token;
	token = strtok(Tampon,":");
	for(int i = 1; i < col; i++)
	{	
		token = strtok(NULL, ":");
		if(token == NULL)
			throw BaseException("la colonne selectionnee est soit incomplete soit inexistante");
	}
	cout<<"Mode:" << token << endl;
	char mode = token[0];
	// token = type de la colonne ! -- YEAY
	getFileContent(fb, liste, col);
	
	Liste<Data1D>* listeData = new Liste<Data1D>(transfereListe(liste));
	
	// definir le mode donc demarrer l'echantillon
	DataSource* pdata = NULL;
	
	if(mode == 'C')
	{
		cout << "MODE C" << endl;
		pdata =new DataSourceSerieContinue(Nom,Sujet,0,0,listeData);
	}
	else
	if(mode == 'D')
	{
		cout << "MODE D" << endl;
		pdata = new DataSourceSerieDiscrete(Nom, Sujet,0,0,listeData);
	}
	
	//pdata->Rapport();
	E->Source = pdata;
		
	
	 
	
		
		
	
}

void EtudeStat1D::getFileContent(ifstream& stream,ListeTriee<float>& liste, int col)
{
	char Tampon[800];
	while(stream.getline(Tampon, 800))
	{
		char* token;
		token = strtok(Tampon,":");
		for(int i = 1; i < col; i++)
			token = strtok(NULL, ":");
		if(token == NULL)
			throw BaseException("la colonne selectionnee est soit incomplete soit inexistante");
		else
		{
			float f = atof(token);
			//cout << "Data: " << f << endl;
			liste.insere(f);
		}
			
	}
}

Liste<Data1D> EtudeStat1D::transfereListe(ListeTriee<float>& liste)
{
		float val;
	int compteur;
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
	
	return listeData;
}

DataSource* EtudeStat1D::methodeContinue(const char* nom, const char* sujet, int eff, int autre, Liste<Data1D>* liste)
{
	DataSourceSerieContinue* datasource;
	datasource = new DataSourceSerieContinue(nom,sujet,0,0,liste);
	datasource->Rapport();
	cout <<"--" << endl;
	DataSource* pdata = dynamic_cast<DataSource*>(datasource);
	return pdata;
	
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
//	GraphStat1DDiscrete w(*this);
//	w.show();
//	a->exec();
//	cout << "test" << endl;
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
