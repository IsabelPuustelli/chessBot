#include <iostream>
#include <list>
#include <assert.h>
#include <stdio.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "Siirto.h"
#include "asema.h"

using namespace std; 

int main()
{

	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Asema asema; 
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	std::list<Siirto> lista;
	std::list<Siirto>::iterator it;
	system("cls");
	int koneenVari = peli.getKoneenVari();
	asema.koneenVari = koneenVari;
	asema.setSiirtovuoro(0);
 
	while (lopetus != 0) {
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		wcout << "\n";

		asema.annaLaillisetSiirrot(lista);

		if (lista.size() == 0) {			// Tarkasta onko peli loppu?
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}
		Siirto siirto; 
		if (asema.getSiirtovuoro() == koneenVari) {
			//asema.laskuri = 0;
			MinMaxPaluu paluu;
			if (koneenVari == 0) {
				paluu = asema.maxi(4);
			}
			else {
				paluu = asema.mini(4);
			}
			siirto = paluu._parasSiirto; 
		}
		else {
			bool laillinenSiirto = false;
			while (!laillinenSiirto)
			{
				siirto = Kayttoliittyma::getInstance()->
					annaVastustajanSiirto();
				for (it = lista.begin(); it != lista.end(); ++it) {
					Ruutu alkuruutu = it->getAlkuruutu();
					Ruutu loppuruutu = it->getLoppuruutu();
					Ruutu siirtoAlku = siirto.getAlkuruutu();
					Ruutu siirtoLoppu = siirto.getLoppuruutu();
					if (alkuruutu.getRivi() == siirtoAlku.getRivi() && alkuruutu.getSarake() == siirtoAlku.getSarake()
						&& loppuruutu.getRivi() == siirtoLoppu.getRivi() && loppuruutu.getSarake() == siirtoLoppu.getSarake())
						laillinenSiirto = true;
				}
				if (!laillinenSiirto)
					wcout << "Laiton siirto!";
			}
		}
		asema.paivitaAsema(&siirto);
		asema.kierros++;

		if (asema.getSiirtovuoro() == 1)
			asema.setSiirtovuoro(0);
		else
			asema.setSiirtovuoro(1);
	}
	return 0;
}
