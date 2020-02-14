#ifndef DATASOURCESERIECONTINUE_H
#define DATASOURCESERIECONTINUE_H

#include "Liste.h"
#include "Iterateur.h"
#include "Data1D.h"
#include "DataSource.h"

class DataSourceSerieContinue: public DataSource
{
	private:
		Liste<Data1D>* L;
		float Debut;
		float Intervalle;
	public:
		DataSourceSerieContinue(const char*, const char*, int, Liste<Data1D>*);
		DataSourceSerieContinue(DataSourceSerieContinue&);
		void applicIntervale();
		void Rapport();
		void getIntervale();
		void CalculEffTotal();
		Liste<Data1D>* getListe();
};

#endif
