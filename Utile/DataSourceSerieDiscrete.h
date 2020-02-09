#ifndef DATASOURCESERIEDISCRETE_H
#define DATASOURCESERIEDISCRETE_H

#include "Liste.h"
#include "Data1D.h"
#include "DataSource.h"

class DataSourceSerieDiscrete: public DataSource
{
	private:
		Liste<Data1D>* L;
	public:
		DataSourceSerieDiscrete(const char*, const char*, int, int, Liste<Data1D>*);
		void Rapport();
};

#endif
