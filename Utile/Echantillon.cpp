#include "Echantillon.h"

Echantillon::Echantillon()
{
	Source = NULL;
}

void Echantillon::setSource(DataSource* ptData)
{
	Source = ptData;
}
