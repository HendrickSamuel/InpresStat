#include "EtudeStatDescriptive.h"

EtudeStatDescriptive::EtudeStatDescriptive(int argc,char* argv[])
{
	if (argc == 2)
	{
		EtudeStat1D E(argv[1],0);
	}
	else
	if (argc == 3)
		EtudeStat1D E(argv[1],atoi(argv[2]));
	else
	if (argc == 4)
		EtudeStat2D E(argv[1],atoi(argv[2]),atoi(argv[3]));
	else
	throw BaseException("mauvais parametres");
}

EtudeStatDescriptive::~EtudeStatDescriptive()
{
}
