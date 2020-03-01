#include "EtudeStat2D.h"

EtudeStat2D::EtudeStat2D(char* fichier, int col1, int col2)
{
	E = new Echantillon(fichier, col1, col2); 
	
	CalculMoy(1);
	CalculMoy(2);
	CalculCorr();
	CalculCorrA();
	CalculCorrB();
	
	AfficheRapport();
} 


float EtudeStat2D::CalculCorr()
{
	DataSourceSerie2D* pt = dynamic_cast<DataSourceSerie2D*>(E->getSource());
	if(!pt)
		throw BaseException("une erreur lors du calcul de correlation s'est produite");
		
	Iterateur<Data2D> it(*(pt->getL()));
	float sommexi = 0;
	float sommeyi = 0;
	float sommexiyi = 0;
	float xicarre = 0;
	float yicarre = 0;
	
	while(!it.end())
	{
		sommexi += ((Data2D)it).getVal1();
		sommeyi += ((Data2D)it).getVal2();
		sommexiyi += ((Data2D)it).getVal1() * ((Data2D)it).getVal2();
		xicarre += ((Data2D)it).getVal1() * ((Data2D)it).getVal1();
		yicarre += ((Data2D)it).getVal2() * ((Data2D)it).getVal2();
		it++;
	}
	
	float corr = sommexiyi - (sommexi) * (sommeyi) / pt->getEffTotal();
	float div = sqrt( (xicarre - (sommexi*sommexi) / pt->getEffTotal() )*( yicarre - (sommeyi * sommeyi)/ pt->getEffTotal()));
	float res = corr / div;
	setCorrel(res);
	return res;
}

float EtudeStat2D::CalculCorrA()
{
	DataSourceSerie2D* pt = dynamic_cast<DataSourceSerie2D*>(E->getSource());
	if(!pt)
		throw BaseException("une erreur lors du calcul de correlation s'est produite");
		
	Iterateur<Data2D> it(*(pt->getL()));
	float sommexi = 0;
	float sommeyi = 0;
	float sommexiyi = 0;
	float xicarre = 0;
	
	while(!it.end())
	{
		sommexi += ((Data2D)it).getVal1();
		sommeyi += ((Data2D)it).getVal2();
		sommexiyi += ((Data2D)it).getVal1() * ((Data2D)it).getVal2();
		xicarre += ((Data2D)it).getVal1() * ((Data2D)it).getVal1();
		it++;
	}
	
	float corr = sommexiyi - (sommexi) * (sommeyi) / pt->getEffTotal();
	float div = xicarre - (sommexi * sommexi)/ pt->getEffTotal();
	float res = corr / div;
	setCoeffA(res);
	return res;	
}

float EtudeStat2D::CalculCorrB()
{
	float res = CalculMoy(2) - CalculCorrA() * CalculMoy(1);
	setCoeffB(res);
	return res;
}

float EtudeStat2D::CalculMoy(int col)
{
	if(col != 1 && col != 2)
		throw BaseException("mauvais choix de param sur le calcul de moyenne");
		
	DataSourceSerie2D* pt = dynamic_cast<DataSourceSerie2D*>(E->getSource());
	if(!pt)
		throw BaseException("une erreur lors du calcul de correlation s'est produite");
		
	Iterateur<Data2D> it(*(pt->getL()));
	float moy1 = 0;
	float moy2 = 0;
	
	if(col == 1)
	{
		while(!it.end())
		{
			moy1 += ((Data2D)it).getVal1();
			it++;
		}
		float res = moy1 / pt->getEffTotal(); 
		setMoy1(res);
		return res;
	}
	else
	{
		while(!it.end())
		{
			moy2 += ((Data2D)it).getVal2();
			it++;
		}
		float res = moy2 / pt->getEffTotal();
		setMoy2(res);
		return res;	
	}
}

void EtudeStat2D::setMoy1(float val)
{
	MoyenneVal1 = val;
}
void EtudeStat2D::setMoy2(float val)
{
	MoyenneVal2 = val;
}
void EtudeStat2D::setCoeffA(float val)
{
	CoeffA = val;
}
void EtudeStat2D::setCoeffB(float val)
{
	CoeffB = val;
}
void EtudeStat2D::setCorrel(float val)
{
	CoeffCorelation = val;
}

float EtudeStat2D::getMoy1()
{
	return MoyenneVal1;
}
float EtudeStat2D::getMoy2()
{
	return MoyenneVal2;
}
float EtudeStat2D::getCoeffA()
{
	return CoeffA;
}
float EtudeStat2D::getCoeffB()
{
	return CoeffB;
}
float EtudeStat2D::getCorrel()
{
	return CoeffCorelation;
}


void EtudeStat2D::AfficheRapport()
{
	cout << "\n Etude statistique: " << endl << "------------------" << endl;
	DataSourceSerie2D* pt = dynamic_cast<DataSourceSerie2D*>(E->getSource());
	if(pt)
	{
		pt->Affiche();
	}	
	
	cout << "\n Moyenne Val1 : " << getMoy1() << endl;
	cout << "Moyenne Val2 : " << getMoy2() << endl;
	
	cout << "\n Corrélation :" << getCorrel()<< endl;
	cout << "\n\tCoefficient a : " << getCoeffA() << endl;
	cout << "\tCoefficient b : " << getCoeffB() << endl;
	
//		cout << "test: " << getCoeffA()*70 + getCoeffB() << endl;
//	cout << "test2: "<< (1.62885 - getCoeffB()) / getCoeffA() << endl;
	
	Previsions();
	
}

void EtudeStat2D::Previsions()
{
	DataSourceSerie2D* pt = dynamic_cast<DataSourceSerie2D*>(E->getSource());
	if(!pt)
		throw BaseException("une erreur de type s'est produite");
	bool isDone = false;	
	int choix = 0;
	float val = 0;
	
	while(!isDone)
	{
		cout << "\t\t1 : Prévision pour : " << pt->getSujet() << endl;
		cout << "\t\t2 : Prévision pour : " << pt->getSujet2() << endl;
		cout << "\t\t3 : Sortie" << endl;
		cout << "\tVotre choix: ";
		cin >> choix;
		
		switch (choix)
		{
			case 1: 
				cout << endl<<"Entrez la valeur pour " << pt->getSujet() << " : ";
				cin >> val;
				cout << "\tla valeur prévue: " << getCoeffA()*val + getCoeffB() << endl << endl;
				break;
				
			case 2:
				cout << endl <<"Entre la valeur pour " << pt->getSujet2() << " : ";
				cin >> val;
				cout << "\tla valeur prévue: " <<(val - getCoeffB()) / getCoeffA() << endl << endl;
				break;
			case 3:
				isDone = true;
				break;
			default:
				cout << "-- Mauvais choix " << endl << endl;
				isDone = true;
		}
		
	}
	
}
