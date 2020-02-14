#include "Echantillon.h"

Echantillon::Echantillon()
{
	Source = NULL;
}

Echantillon::Echantillon(char* file,int col)
{
	GetFileContent1D(file,col);
}

void Echantillon::setSource(DataSource* ptData)
{
	Source = ptData;
}

DataSource* Echantillon::getSource()
{
	return Source;
}

void Echantillon::GetFileContent1D(char* file, int col)
{
	ListeTriee<float> liste;
	ifstream fb(file,ios::in);
	if(fb == NULL)
		throw BaseException("le nom du fichier n'est pas bon");
	
	char Tampon[800];
	char Nom[80];
	char Sujet[80];
	
	// prise du nom et du sujet
	fb.getline(Tampon, 800);
	strcpy(Nom, Tampon);
	
	
	fb.getline(Tampon, 800);
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

	char mode = token[0];
	// token = type de la colonne ! -- YEAY
	getFileData1D(fb, liste, col);
	
	Liste<Data1D>* listeData = new Liste<Data1D>(transfereListe(liste));
	
	// definir le mode donc demarrer l'echantillon
	
	if(mode == 'C')
	{
		Source =new DataSourceSerieContinue(Nom,Sujet,0,listeData);
	}
	else
	if(mode == 'D')
	{
		Source = new DataSourceSerieDiscrete(Nom, Sujet,0,listeData);
	}
}

Liste<Data1D> Echantillon::transfereListe(ListeTriee<float>& liste)
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

void Echantillon::getFileData1D(ifstream& stream,ListeTriee<float>& liste, int col)
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
