#include <Windows.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"
#include "siirto.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;


Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}


void Kayttoliittyma::piirraLauta() {

	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			if (j == 0 && i == 7) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 8;
			}
			if (j == 0 && i == 6) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 7;
			}
			if (j == 0 && i == 5) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 6;
			}
			if (j == 0 && i == 4) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 5;
			}
			if (j == 0 && i == 3) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 4;
			}
			if (j == 0 && i == 2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 3;
			}
			if (j == 0 && i == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 2;
			}
			if (j == 0 && i == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
					BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				wcout << 1;
			}
			if (i % 2 != 0) {
				if (j % 2 == 0)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
						BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN |
						BACKGROUND_RED);
			}
			else {
				if (j % 2 != 0)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
						BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN |
						BACKGROUND_RED);
			}

			const int out_fileno = _fileno(stdout);

			assert(_isatty(out_fileno));
			_setmode(out_fileno, _O_WTEXT);

			if (_asema->_lauta[j][i] != NULL/* && _asema->_lauta[j][i]->getUnicode() != L"\u265F"*/)
				wcout << " " << _asema->_lauta[j][i]->getUnicode() << " ";
			/*else if (_asema->_lauta[j][i] != NULL && _asema->_lauta[j][i]->getUnicode() == L"\u265F") // Jostain syystä joillain konsoleilla seitsemäs rivi saa tupla välilyönnit, jos tämä tapahtuu, poista nämä ja ylemmät kommentoinnit
				wcout << " " << _asema->_lauta[j][i]->getUnicode();*/
			else
				wcout << "   ";

		}
		wcout << "\n";
	}
	wcout << "  " << "a " << " b " << " c " << " d " << " e " << " f " << " g " << " h \n";
}


/*
	Aliohjelma tarkistaa että käyttäjän antama syöte siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myös nappulan kirjaimen (K/D/L/R/T), tarkistaa että kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	int siirtoKoodi[6];
	char i[6];
	bool jarkevaSiirto;
	Ruutu alkuruutu;
	Ruutu loppuruutu;

	wcout << "\nAnna siirto:";
	cin >> i;

	if(i[0] == 'o')		// Jos tornitus, ei aseteta mitään oikeita koordinaatteja, annetaan
	{					// vain koodi joka otetaan toisessapäässä vastaan ja luetaan tornituksena
		if (i[3] == '-' && i[4] == 'o')
		{
			alkuruutu.setSarake(1);		//Kuningattaren tornitus: 1111
			alkuruutu.setRivi(1);
			loppuruutu.setSarake(1);
			loppuruutu.setRivi(1);
		}
		else 
		{
			alkuruutu.setSarake(0);		//Kuninkaan tornitus koodi: 0000
			alkuruutu.setRivi(0);
			loppuruutu.setSarake(0); 
			loppuruutu.setRivi(0);
		}
	}
	else {
		siirtoKoodi[0] = int(i[0]) - 97;
		siirtoKoodi[1] = i[1] - 49;
		siirtoKoodi[2] = int(i[2]) - 97;
		siirtoKoodi[3] = i[3] - 49;

		alkuruutu.setSarake(siirtoKoodi[0]);
		alkuruutu.setRivi(siirtoKoodi[1]);

		loppuruutu.setSarake(siirtoKoodi[2]);
		loppuruutu.setRivi(siirtoKoodi[3]);
	}
	Siirto* siirto = new Siirto(alkuruutu, loppuruutu);
	return *siirto;
}

int Kayttoliittyma::kysyVastustajanVari()
{
	int vari;

	wcout << "\nKumpaa väriä haluat pelata (0 = Valkoinen    1 = Musta)\n";
	wcin >> vari;
	return vari;
}
