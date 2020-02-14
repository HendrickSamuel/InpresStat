#ifndef DATASOURCESERIEDISCRETE_H
#define DATASOURCESERIEDISCRETE_H

#include "Liste.h"
#include "Data1D.h"
#include "DataSource.h"
#include "Iterateur.h"

class DataSourceSerieDiscrete: public DataSource
{
	private:
		Liste<Data1D>* L;
	public:
		DataSourceSerieDiscrete(const char*, const char*, int, Liste<Data1D>*);
		void Rapport();
		void CalculEffTotal();
		Liste<Data1D>* getListe();
};

#endif
