#include "Echantillon.h"

Echantillon::Echantillon()
{
	Source = NULL;
}

Echantillon::Echantillon(char* file,int col)
{
	GetFileContent1D(file,col);
}

Echantillon::Echantillon(char* file, int col1, int col2)
{
	GetFileContent2D(file,col1,col2);
}

void Echantillon::setSource(DataSource* ptData)
{
	Source = ptData;
}

DataSource* Echantillon::getSource()
{
	return Source;
}

void Echantillon::GetFileContent2D(char* file, int col1, int col2)
{
	ifstream fb(file,ios::in);
	if(fb == NULL)
		throw BaseException("le fichier n'a pas pu etre ouvert");
		
	Liste<Data2D>* l = new Liste<Data2D>;
	char Tampon[800];
	char Nom[80];
	char Sujet1[80], Sujet2[80];
	char Type1,Type2;
	int tmp;
	char* token;
	if(col1 > col2)
	{
		tmp = col2;
		col2 = col1;
		col1 = tmp;
	}
	
	
	fb.getline(Nom,80);
	
	fb.getline(Tampon, 800);
	token = strtok(Tampon,":");
	for(int i = 1; i < col2; i++)
	{	
		if(i == col1)
			strcpy(Sujet1,token);
		token = strtok(NULL, ":");
		if(token == NULL)
			throw BaseException("la colonne selectionnee est soit incomplete soit inexistante");
	}
	strcpy(Sujet2,token);
	
	fb.getline(Tampon, 800);
	token = strtok(Tampon,":");
	for(int i = 1; i < col2; i++)
	{	
		if(i == col1)
			Type1 = token[0];
		token = strtok(NULL, ":");
		if(token == NULL)
			throw BaseException("la colonne selectionnee est soit incomplete soit inexistante");
	}
	Type2 = token[0];
	
	
	getFileData2D(fb,l,col1,col2);
	int type1, type2;
	if(Type1 == 'C')
		type1 = CONTINUE;
	else
		type1 = DISCRETE;
		
	if(Type2 == 'C')
		type2 = CONTINUE;
	else
		type2 = DISCRETE;
		
	Source = new DataSourceSerie2D(Nom,Sujet1,type1,Sujet2,type2,l);
}

void Echantillon::GetFileContent1D(char* file, int col)
{
	ListeTriee<float> liste;
	ifstream fb(file,ios::in);
	if(fb == NULL)
		throw BaseException("le fichier n'a pas pu etre ouvert");
	
	char Tampon[800];
	char Nom[80];
	char Sujet[80];
	char* token;
	// prise du nom et du sujet
	fb.getline(Nom, 80);
	
	
	fb.getline(Tampon, 800);
	token = strtok(Tampon,":");
	for(int i = 1; i < col; i++)
	{	
		token = strtok(NULL, ":");
		if(token == NULL)
			throw BaseException("la colonne selectionnee est soit incomplete soit inexistante");
	}
	
	strcpy(Sujet, token);	
	
	// definir si discret ou continu
	fb.getline(Tampon, 800);
	
	// selectionner la colonne necessaire
	
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

void Echantillon::getFileData2D(ifstream& file, Liste<Data2D>* liste,int col1,int col2)
{
	char Tampon[800];
	while(file.getline(Tampon,800))
	{
		Data2D data;
		char* token;
		token = strtok(Tampon,":");
		for(int i = 1; i < col2; i++ && token != NULL)
		{
			if(i == col1)
			{
				data.setVal1(atof(token));
			}
			token = strtok(NULL, ":");
		}
		if(token != NULL)
		{
			data.setVal2(atof(token));
			liste->insere(data);
		}
		else
			throw BaseException("probleme de ficher");
	}
}
