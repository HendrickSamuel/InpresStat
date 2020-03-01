#include "Liste.h"

template <class T> Liste<T>::Liste() : ListeBase<T>::ListeBase(){

}

template <class T> Liste<T>::Liste(const Liste& old): Liste<T>::ListeBase(old){
}

template <class T>Liste<T>::~Liste(){

}

template <class T> void Liste<T>::insere(const T & val){
	//Liste<T>::Affiche();
	Cellule<T> *pt = NULL;
	pt = new Cellule<T>;
	
	pt->valeur = val;
	pt->suivant = NULL;
	
	
	if(this->estVide())
	{
		this->setpTete(pt);
	}
	else
	{	
		Cellule<T> *pdepl;
		pdepl = this->getpTete();
		while(pdepl->suivant != NULL)
		{
			pdepl = pdepl->suivant;
		}	
		pdepl -> suivant = pt;
	}
	
}

template class Liste<int>;
template class Liste<float>;
#include "Data1D.h"
template class Liste<Data1D>;
#include "Data2D.h"
template class Liste<Data2D>;
