#ifndef ECHANTILLON_H
#define ECHANTILLON_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "DataSource.h"

class Echantillon
{
	public:
		DataSource* Source;
	public:
		void setSource(DataSource*);		
		Echantillon();
};
	
#endif
