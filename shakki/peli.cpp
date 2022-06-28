#include "peli.h"
#include "kayttoliittyma.h"

using namespace std;

int _ihmisenVari;

Peli::Peli(int ihmisenVari)
{
	_ihmisenVari = ihmisenVari;
}


int Peli::getKoneenVari(){
	
	int koneenVari = 1 - _ihmisenVari;
	return koneenVari;
}
