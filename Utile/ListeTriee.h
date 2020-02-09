#ifndef LISTETRIEE_H
#define LISTETRIEE_H
#include "ListeBase.h"

using namespace std;

template <class T> class ListeTriee: public ListeBase<T>
{
	private :
		
		
	public :
		ListeTriee();
		ListeTriee(const ListeTriee&);
		~ListeTriee();

		void insere(const T& val);
		
		
};

#endif
