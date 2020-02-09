#include "ListeTriee.h"

template <class T> ListeTriee<T>::ListeTriee(): ListeBase<T>::ListeBase(){
	#ifdef DEV
	Trace("Constructeur par defaut ListeTriee");
	#endif
}

template <class T> ListeTriee<T>::ListeTriee(const ListeTriee& old): ListeBase<T>::ListeBase(old){

}

template <class T>ListeTriee<T>::~ListeTriee(){

}

template <class T> void ListeTriee<T>::insere(const T & val){
	Cellule<T> *pt = NULL;
	pt = new Cellule<T>;
	
	pt->valeur = val;
	
	
	if(this->estVide())
	{
		pt->suivant = NULL;
		this->setpTete(pt);
	}
	else
	{
		Cellule<T> *pdepl = this->getpTete();
		Cellule<T> *pprec = NULL; 
		while(pdepl != NULL && pdepl->valeur < val)
		{
			pprec = pdepl;
			pdepl = pdepl->suivant;
		}	
		if(pdepl == this->getpTete())
		{
			pt->suivant = this->getpTete();
			this->setpTete(pt);
		}
		else
		{	
			pt->suivant = pdepl;
			pprec->suivant = pt;
		}
	}
	
}

template class ListeTriee<int>;
template class ListeTriee<float>;

