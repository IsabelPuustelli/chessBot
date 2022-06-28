//#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;


Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();

	for (int i = lahtoruutuX + 1; i < 8; i++) {							// Vaakarivi ruudusta eteenpäin
		if (asema->_lauta[i][lahtoruutuY] == NULL)
			lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY)));		// Jos ruutu on tyhjä, lisää listaan
		else if (asema->_lauta[i][lahtoruutuY] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[i][lahtoruutuY]->getVari();	// Jos ruutu on täynnä, tarkistetaan vielä onko nappula syötävä
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari)
				break;															// Jos oma nappula, break.
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari)
				lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY))); break;	// Jos vastustajan, lisää listaan ja break.
		}
	}

	for (int i = lahtoruutuX - 1; i >= 0; i--) {						// Vaakarivi ruudusta taaksepäin
		if (asema->_lauta[i][lahtoruutuY] == NULL)
			lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY)));		// Jos ruutu on tyhjä, lisää listaan
		else if (asema->_lauta[i][lahtoruutuY] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[i][lahtoruutuY]->getVari();	// Jos ruutu on täynnä, tarkistetaan vielä onko nappula syötävä
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari)
				break;															// Jos oma nappula, break.
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari)
				lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY))); break;	// Jos vastustajan, lisää listaan ja break.
		}
	}

	for (int i = lahtoruutuY + 1; i < 8; i++) {						// Sarake ruudusta ylöspäin
		if (asema->_lauta[lahtoruutuX][i] == NULL)
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));		// Jos ruutu on tyhjä, lisää listaan
		else if (asema->_lauta[lahtoruutuX][i] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX][i]->getVari();	// Jos ruutu on täynnä, tarkistetaan vielä onko nappula syötävä
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari)
				break;															// Jos oma nappula, break.
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari)
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i))); break;	// Jos vastustajan, lisää listaan ja break.
		}
	}

	for (int i = lahtoruutuY - 1; i >= 0; i--) {						// Sarake ruudusta alaspäin
		if (asema->_lauta[lahtoruutuX][i] == NULL)
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));		// Jos ruutu on tyhjä, lisää listaan
		else if (asema->_lauta[lahtoruutuX][i] != NULL) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX][i]->getVari();	// Jos ruutu on täynnä, tarkistetaan vielä onko nappula syötävä
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari)
				break;															// Jos oma nappula, break.
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari)
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i))); break;	// Jos vastustajan, lisää listaan ja break.
		}
	}
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;
	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();

	int x[] = { 2, 2, -2, -2, 1, -1, 1, -1 };
	int y[] = { 1, -1, 1, -1, 2, 2, -2, -2 };

	for (int i = 0; i < 8; i++) // Kyllä, if lause ei toimi syntaxilla if (0 < lahtoruutuY + y[i] < 8), joten sen pitää olla kuvottavan pitkä
	{
		if (0 < lahtoruutuY + y[i] && lahtoruutuY + y[i] < 8 && 0 < lahtoruutuX + x[i] && lahtoruutuX + x[i] < 8) // Jos ollaan pöydällä
		{
			if (asema->_lauta[lahtoruutuX + x[i]][lahtoruutuY + y[i]] == NULL) {	// Ja ruutu on tyhjä
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + x[i], lahtoruutuY + y[i])));
			}
			else {		// Jos ruutu ei oo tyhjä
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + x[i]][lahtoruutuY + y[i]]->getVari();	// Katotaan tuloruudun nappulan väri
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari)		// Onko se erivärinen
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + x[i], lahtoruutuY + y[i])));
			}
		}
	}
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;
	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();

	int i = 1;		// Tarkistus koilliseen
	while (asema->_lauta[lahtoruutuX + i][lahtoruutuY + i] == NULL && lahtoruutuX + i < 8 && lahtoruutuY + i < 8
		&& 0 <= lahtoruutuX + i && 0 <= lahtoruutuY + i)
	{
		lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + i, lahtoruutuY + i)));
		i++;
	}
	if (asema->_lauta[lahtoruutuX + i][lahtoruutuY + i] != NULL && lahtoruutuX + i < 8 && lahtoruutuY + i < 8
		&& 0 <= lahtoruutuX + i && 0 <= lahtoruutuY + i)
	{
		tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + i][lahtoruutuY + i]->getVari();
		if(lahtoruudunNappulanVari != tuloruudunNappulanVari)
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + i, lahtoruutuY + i)));
	}

	i = 1;		// Tarkistus kaakkoon
	while (asema->_lauta[lahtoruutuX + i][lahtoruutuY - i] == NULL && lahtoruutuX + i < 8 && lahtoruutuY - i < 8
		&& 0 <= lahtoruutuX + i && 0 <= lahtoruutuY - i)
	{
		lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + i, lahtoruutuY - i)));
		i++;
	}
	if (asema->_lauta[lahtoruutuX + i][lahtoruutuY - i] != NULL && lahtoruutuX + i < 8 && lahtoruutuY - i < 8
		&& 0 <= lahtoruutuX + i && 0 <= lahtoruutuY - i)
	{
		tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + i][lahtoruutuY - i]->getVari();
		if (lahtoruudunNappulanVari != tuloruudunNappulanVari)
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + i, lahtoruutuY - i)));
	}

	i = 1;		// Tarkistus lounas
	while (asema->_lauta[lahtoruutuX - i][lahtoruutuY - i] == NULL && lahtoruutuX - i < 8 && lahtoruutuY - i < 8
		&& 0 <= lahtoruutuX - i && 0 <= lahtoruutuY - i)
	{
		lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - i, lahtoruutuY - i)));
		i++;
	}
	if (asema->_lauta[lahtoruutuX - i][lahtoruutuY - i] != NULL && lahtoruutuX - i < 8 && lahtoruutuY - i < 8
		&& 0 <= lahtoruutuX - i && 0 <= lahtoruutuY - i)
	{
		tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - i][lahtoruutuY - i]->getVari();
		if (lahtoruudunNappulanVari != tuloruudunNappulanVari)
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - i, lahtoruutuY - i)));
	}

	i = 1;		// Tarkistus luoteeseen
	while (asema->_lauta[lahtoruutuX - i][lahtoruutuY + i] == NULL && lahtoruutuX - i < 8 && lahtoruutuY + i < 8
		&& 0 <= lahtoruutuX - i && 0 <= lahtoruutuY + i)
	{
		lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - i, lahtoruutuY + i)));
		i++;
	}
	if (asema->_lauta[lahtoruutuX - i][lahtoruutuY + i] != NULL && lahtoruutuX - i < 8 && lahtoruutuY + i < 8
		&& 0 <= lahtoruutuX - i && 0 <= lahtoruutuY + i)
	{
		tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - i][lahtoruutuY + i]->getVari();
		if (lahtoruudunNappulanVari != tuloruudunNappulanVari)
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - i, lahtoruutuY + i)));
	}
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	this->Lahetti::annaSiirrot(lista, ruutu, asema, vari);
	this->Torni::annaSiirrot(lista, ruutu, asema, vari);
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;
	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();

	int x[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int y[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	 
	for (int i = 0; i < 8; i++)
	{
		if (lahtoruutuX + x[i] < 8 && lahtoruutuX + x[i] >= 0 && lahtoruutuY + y[i] < 8 && lahtoruutuY + y[i] >= 0)
		{
			if (asema->_lauta[lahtoruutuX + x[i]][lahtoruutuY + y[i]] != NULL) {
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + x[i]][lahtoruutuY + y[i]]->getVari();
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari)
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + x[i], lahtoruutuY + y[i])));
			}
			if (asema->_lauta[lahtoruutuX + x[i]][lahtoruutuY + y[i]] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + x[i], lahtoruutuY + y[i])));
			}
		}
	}
	if (asema->getSiirtovuoro() == 0) {
		if ((asema->getOnkoValkeaKuningasLiikkunut() == false && asema->getOnkoValkeaKTliikkunut() == false)
			&& (asema->_lauta[6][0] == NULL && asema->_lauta[5][0] == NULL)) {
			lista.push_back(Siirto(Ruutu(0, 0), Ruutu(0, 0)));
		}
		if ((asema->getOnkoValkeaKuningasLiikkunut() == false && asema->getOnkoValkeaDTliikkunut() == false)
			&& (asema->_lauta[1][0] == NULL && asema->_lauta[2][0] == NULL && asema->_lauta[3][0] == NULL)) {
			lista.push_back(Siirto(Ruutu(1, 1), Ruutu(1, 1)));
		}
	}
	else if (asema->getSiirtovuoro() == 1) {
		if ((asema->getOnkoMustaKuningasLiikkunut() == false && asema->getOnkoMustaKTliikkunut() == false)
			&& (asema->_lauta[6][7] == NULL && asema->_lauta[5][7] == NULL)) {
			lista.push_back(Siirto(Ruutu(0, 0), Ruutu(0, 0)));
		}
		if ((asema->getOnkoMustaKuningasLiikkunut() == false && asema->getOnkoMustaDTliikkunut() == false)
			&& (asema->_lauta[1][7] == NULL && asema->_lauta[2][7] == NULL && asema->_lauta[3][7] == NULL)) {
			lista.push_back(Siirto(Ruutu(1, 1), Ruutu(1, 1)));
		}
	}
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();
	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;
	lahtoruudunNappulanVari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();

	// valkea sotilas rivillä 2 on mahdollisuus tupla-askeleeseen
	if (lahtoruutuY == 1 && lahtoruudunNappulanVari == 0) {
		for (int i = lahtoruutuY + 1; i < lahtoruutuY + 3; i++){
			if (asema->_lauta[lahtoruutuX][i] == NULL)		// Tyhjä ruutu lisätään listaan
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
			else
				break;
		}
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1] != NULL && lahtoruutuX + 1 < 8){
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari)		// Jos viistossa edessä oleva nappula on vastustajan
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)));
		}
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1] != NULL && lahtoruutuX - 1 >= 0) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari)		// Jos viistossa edessä oleva nappula on vastustajan
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 1)));
		}
	}
 

	// musta sotilas rivillä 7 on mahdollisuus tupla-askeleeseen
	if (lahtoruutuY == 6 && lahtoruudunNappulanVari == 1) {
		for (int i = lahtoruutuY - 1; i > lahtoruutuY - 3; i--) {
			if (asema->_lauta[lahtoruutuX][i] == NULL)		// Tyhjä ruutu lisätään listaan
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
			else
				break;
		}
		if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1] != NULL && lahtoruutuX + 1 < 8) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari)	// Jos viistossa edessä oleva nappula on vastustajan
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)));
		}
		if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1] != NULL && lahtoruutuX - 1 >= 0) {
			tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari)		// Jos viistossa edessä oleva nappula on vastustajan
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)));
		}
	}

	// perusruudut valkeille
	if ((lahtoruutuY == 2 || lahtoruutuY == 3 || lahtoruutuY == 4 || lahtoruutuY == 5 || lahtoruutuY == 6) && lahtoruudunNappulanVari == 0) {
		if (asema->_lauta[lahtoruutuX][lahtoruutuY + 1] == NULL) {		// Siirtymä eteenpäin
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)));
		}
		// viistoon syönti
		if (lahtoruutuX + 1 < 8) {	// Tarkistetaan onko syötävä ruutu laudan sisällä
			if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1] != NULL) {
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY + 1]->getVari();
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari){		// Jos viistossa edessä oleva nappula on vastustajan
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)));
				}
			}
		}
		if (lahtoruutuX - 1 >= 0) {	// Tarkistetaan onko syötävä ruutu laudan sisällä
			if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1] != NULL) {
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY + 1]->getVari();
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {		// Jos viistossa edessä oleva nappula on vastustajan
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 1)));
				}
			}
		}
	}
	// perusruudut mustille
	if ((lahtoruutuY == 1 || lahtoruutuY == 2 || lahtoruutuY == 3 || lahtoruutuY == 4 || lahtoruutuY == 5 || lahtoruutuY == 6) && lahtoruudunNappulanVari == 1) {
		if (asema->_lauta[lahtoruutuX][lahtoruutuY - 1] == NULL) {		// Siirtymä eteenpäin
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)));
		}
		// viistoon syönti
		if (lahtoruutuX + 1 < 8) {	// Tarkistetaan että ollaan vielä laudan sisällä
			if (asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1] != NULL) {
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX + 1][lahtoruutuY - 1]->getVari();
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {		// Jos viistossa edessä oleva nappula on vastustajan
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)));
				}
			}
		}
		if (lahtoruutuX - 1 >= 0) {	// Tarkistetaan että ollaan vielä laudan sisällä
			if (asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1] != NULL) {
				tuloruudunNappulanVari = asema->_lauta[lahtoruutuX - 1][lahtoruutuY - 1]->getVari();
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {		// Jos viistossa edessä oleva nappula on vastustajan
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)));
				}
			}
		}
	}
}

/*
void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}*/