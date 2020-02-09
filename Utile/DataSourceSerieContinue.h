#ifndef DATASOURCESERIECONTINUE_H
#define DATASOURCESERIECONTINUE_H

#include "Liste.h"
#include "Data1D.h"
#include "DataSource.h"

class DataSourceSerieContinue: public DataSource
{
	private:
		Liste<Data1D>* L;
		float Debut;
		float intervalle;
	public:
		DataSourceSerieContinue(const char*, const char*, int, int, Liste<Data1D>*);
		DataSourceSerieContinue(DataSourceSerieContinue&);
		void Rapport();
};

#endif
