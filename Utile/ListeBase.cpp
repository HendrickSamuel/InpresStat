#include "ListeBase.h"

template <class T> ListeBase<T>::ListeBase(){
	pTete = NULL;
}
	
template <class T> ListeBase<T>::ListeBase(const ListeBase& old){
	pTete = NULL;
	Cellule<T> *pDeplOld = old.getpTete();
	Cellule<T> *pDepld = this->getpTete();
	Cellule<T> *pPrec = NULL;
	

	while(pDeplOld != NULL)
	{
		pDepld = new Cellule<T>;
		pDepld -> valeur = pDeplOld -> valeur;
		pDepld -> suivant = NULL;
		if(this->estVide())
			pTete = pDepld;
		else
			{
				pPrec -> suivant = pDepld;
			}
		
		pPrec = pDepld;			
		pDeplOld = pDeplOld->suivant;
	}
		
}

template <class T> ListeBase<T>::~ListeBase(){
	Cellule<T> *pSupp;
	while(pTete != NULL)
	{
		pSupp = pTete;
		pTete = pTete->suivant;
		delete pSupp;
	}
}

template <class T> const ListeBase<T>& ListeBase<T>::operator=(const ListeBase& old){
	
	if(!this->estVide())
	{	
		Cellule<T> *pSupp;
		while(pTete != NULL)
		{
			pSupp = pTete;
			pTete = pTete->suivant;
			delete pSupp;
		}
		pTete = NULL;
	}
	
	Cellule<T> *pDeplOld;
	Cellule<T> *pDepld;
	Cellule<T> *pPrec = NULL;
	
	pDeplOld = old.pTete;
	pDepld = pTete;
	while(pDeplOld != NULL)
	{
		pDepld = new Cellule<T>;
		pDepld -> valeur = pDeplOld -> valeur;
		pDepld -> suivant = NULL;
		if(this->estVide())
			pTete = pDepld;
		else
			{
				pPrec -> suivant = pDepld;
			}
		
		pPrec = pDepld;			
		pDeplOld = pDeplOld->suivant;
	}	
	
	return *this;
}

template <class T> Cellule<T>* ListeBase<T>::getpTete() const
{
	return pTete;
}

template <class T> Cellule<T>* ListeBase<T>::getpQueu() const
{
	Cellule<T> *pDepl = getpTete();
	if(pDepl != NULL)
	{
		while(pDepl->suivant != NULL)
		{
			pDepl = pDepl->suivant;
		}
	}
	return pDepl;
}

//template <class T> Cellule<T>* ListeBase<T>::getElem(int case) const
//{
//	compteur = 0;
//	Cellule<T> *pDepl = getpTete();
//	while(pDepl!= NULL && compteur < case)
//	{
//		pDepl = pDepl->suivant;
//	}
//	return pDepl;
//}

template <class T> void ListeBase<T>::setpTete(Cellule<T>* point)
{
	pTete = point;
}	

template <class T> bool ListeBase<T>::estVide() const{
	if(getpTete() == NULL)
		return true;
	else
		return false;
}

template <class T> int ListeBase<T>::getNombreElements() const{
	int compteur = 0;
	Cellule<T> *pPointeur;
	pPointeur = getpTete();
	while(pPointeur != NULL)
	{
		pPointeur = pPointeur->suivant;
		compteur++;
	}
	return compteur;
}

template <class T> void ListeBase<T>::Affiche() const{
	Cellule<T> *pSupp;
	pSupp = getpTete();
	while(pSupp != NULL)
	{
		cout <<" "<< pSupp->valeur;
		pSupp = pSupp ->suivant;
	}
	cout << endl;
}

template class ListeBase<int>;
template class ListeBase<float>;
#include "Data1D.h"
template class ListeBase<Data1D>;
