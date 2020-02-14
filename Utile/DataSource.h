#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#define CONTINUE 2
#define DISCRETE 1


class DataSource {

	protected: 
		char* Nom;
		char* Sujet;
		int EffTotal;
		int Type;
	public:
		DataSource();
		DataSource(const char*, const char*, int);
		virtual ~DataSource();
		
		/* -- GETTERS --*/
		const char* getNom() const;
		const char* getSujet() const;
		int getEffTotal() const;
		int getType() const;
		
		/* -- SETTERS --*/
		
		void setNom(const char*);
		void setSujet(const char*);
		void setEffTotal(int);
		void setType(int);
		
		//virtual void Rapport() = 0;
};

#endif
