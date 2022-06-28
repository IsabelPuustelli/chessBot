#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"
#include "kayttoliittyma.h"
#include <string>

using namespace std;

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);

bool mustaDTLiikkunut = false;
bool mustaKTLiikkunut = false;
bool mustaKuningasLiikkunut = false;
bool valkeaDTLiikkunut = false;
bool valkeaKTLiikkunut = false;
bool valkeaKuningasLiikkunut = false;

int koneenVari;
int laskuri = 0;

Asema::Asema()
{

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			_lauta[i][j] = NULL;

	_lauta[0][0] = vt;
	_lauta[1][0] = vr;
	_lauta[2][0] = vl;
	_lauta[3][0] = vd;
	_lauta[4][0] = vk;
	_lauta[5][0] = vl;
	_lauta[6][0] = vr;
	_lauta[7][0] = vt;

	_lauta[0][1] = vs;
	_lauta[1][1] = vs;
	_lauta[2][1] = vs;
	_lauta[3][1] = vs;
	_lauta[4][1] = vs;
	_lauta[5][1] = vs;
	_lauta[6][1] = vs;
	_lauta[7][1] = vs;

	_lauta[0][7] = mt;
	_lauta[1][7] = mr;
	_lauta[2][7] = ml;
	_lauta[3][7] = md;
	_lauta[4][7] = mk;
	_lauta[5][7] = ml;
	_lauta[6][7] = mr;
	_lauta[7][7] = mt;

	_lauta[0][6] = ms;
	_lauta[1][6] = ms;
	_lauta[2][6] = ms;
	_lauta[3][6] = ms;
	_lauta[4][6] = ms;
	_lauta[5][6] = ms;
	_lauta[6][6] = ms;
	_lauta[7][6] = ms;
	
}

void Asema::paivitaAsema(Siirto *siirto)
{
	Ruutu alkuruutu = siirto->getAlkuruutu();
	Ruutu loppuruutu = siirto->getLoppuruutu();
	char korotus;



	if ((alkuruutu.getRivi() == 0 && alkuruutu.getSarake() == 0) && (loppuruutu.getSarake() == 0 && 
		(loppuruutu.getRivi() == 0)))  
	{
		if (_siirtovuoro == 0)
		{
			_lauta[6][0] = vk;				//Valkoisen kuningas tornitus
			_lauta[5][0] = vt;
			_lauta[4][0] = NULL;
			_lauta[7][0] = NULL;
		}
		else {
			_lauta[6][7] = mk;				//Mustan kuningas tornitus
			_lauta[5][7] = mt;
			_lauta[4][7] = NULL;
			_lauta[7][7] = NULL;
		}
	}
	else if ((alkuruutu.getRivi() == 1 && alkuruutu.getSarake() == 1) && (loppuruutu.getSarake() == 1 &&
		(loppuruutu.getRivi() == 1))) {

		if (_siirtovuoro == 1) {
			_lauta[2][7] = mk;				//Mustan kuningatar tornitus 
			_lauta[3][7] = mt;
			_lauta[4][7] = NULL;
			_lauta[0][7] = NULL;
		}
		else {
			_lauta[2][0] = vk;				//Valkoisen kuningatar tornitus 
			_lauta[3][0] = vt;
			_lauta[4][0] = NULL;
			_lauta[0][0] = NULL;
		}
	}
	else {

		switch (_lauta[alkuruutu.getSarake()][alkuruutu.getRivi()]->getKoodi())
		{
		case 0: _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = vt;
			if (alkuruutu.getSarake() == 0) { valkeaDTLiikkunut = true; }
			else { valkeaKTLiikkunut = true; } break;
		case 1: _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = vr; break;
		case 2: _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = vl; break;
		case 3: _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = vd; break;
		case 4: _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = vk; valkeaKuningasLiikkunut = true; break;
		case 5: if (loppuruutu.getRivi() == 7) {
			cout << "Anna korotus nappula: ";
			cin >> korotus;
			switch (korotus) {
			case 'd': _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = vd; break;
			case 't': _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = vt; break;
			case 'r': _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = vr; break;
			case 'l': _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = vl; break;
			}
		}else _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = vs; break;
		case 6: _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = mt;
			if (alkuruutu.getSarake() == 0) { mustaDTLiikkunut = true; }
			else { mustaKTLiikkunut = true; } break;
		case 7: _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = mr; break;
		case 8: _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = ml; break;
		case 9: _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = md; break;
		case 10: _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = mk; mustaKuningasLiikkunut = true; break;
		case 11: if (loppuruutu.getRivi() == 0) {
			cout << "Anna korotus nappula: ";
			cin >> korotus;
			switch (korotus) {
			case 'd': _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = md; break;
			case 't': _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = mt; break;
			case 'r': _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = mr; break;
			case 'l': _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = ml; break;
			}
		}else _lauta[loppuruutu.getSarake()][loppuruutu.getRivi()] = ms; break;
		}
		_lauta[alkuruutu.getSarake()][alkuruutu.getRivi()] = NULL;
	}
}



int Asema::getSiirtovuoro() 
{
	return _siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro) 
{
	_siirtovuoro = vuoro;
}


bool Asema::getOnkoValkeaKuningasLiikkunut() 
{
	return valkeaKuningasLiikkunut;
}


bool Asema::getOnkoMustaKuningasLiikkunut() 
{
	return mustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut() 
{
	return valkeaDTLiikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut() 
{
	return valkeaKTLiikkunut;
}


bool Asema::getOnkoMustaDTliikkunut() 
{
	return mustaDTLiikkunut;
}


bool Asema::getOnkoMustaKTliikkunut() 
{
	return mustaKTLiikkunut;
}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
L‰hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv‰ ett‰ kunigas g1 tai b1/c1
Loppupeliss‰ vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est‰m‰ss‰ vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki‰ linjoja daami, torni ja l‰hetti
*/
double Asema::evaluoi() 
{
	//kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta
	
	//1. Nappuloiden arvo
	
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
	// 4. Arvosta linjoja

	double tulos = 0;
	
	tulos = tulos + laskeNappuloidenArvo(0);

	tulos = tulos + nappuloitaKeskella(0);

	for (int i = 0; i < 8; i++) {
		if (_lauta[i][7] != NULL) {
			if (_lauta[i][7]->getKoodi() == 10)
				tulos = tulos - 10;
		}
	}
	for (int i = 0; i < 8; i++) {
		if (_lauta[i][0] != NULL) {
			if (_lauta[i][0]->getKoodi() == 4)
				tulos = tulos + 10;
		}
	}

	return tulos;
}


double Asema::laskeNappuloidenArvo(int vari) 
{
	double tulos = 0;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (_lauta[x][y] != NULL)
			{
				int koodi = _lauta[x][y]->getKoodi();

				switch (koodi) {

				case 0: tulos = tulos + 5.63; break;
				case 1: tulos = tulos + 3.05; break;
				case 2: tulos = tulos + 3.33; break;
				case 3: tulos = tulos + 9.5; break;
				case 4: tulos = tulos + 100; break;
				case 5:	tulos = tulos + 1; break;
				case 6:	tulos = tulos - 5.63; break;
				case 7:	tulos = tulos - 3.05; break;
				case 8:	tulos = tulos - 3.33; break;
				case 9:	tulos = tulos - 9.5; break;
				case 10: tulos = tulos - 100; break;
				case 11: tulos = tulos - 1; break;
				}
			}
		}
	}
	return tulos;
}


bool Asema::onkoAvausTaiKeskipeli(int vari) 
{
	// Jos upseereita 3 tai v‰hemm‰n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j‰ljell‰
	
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
	bool avaus = false;

	if (kierros < 10)
		avaus = true;
	else
		avaus = false;
	return avaus;
}


double Asema::nappuloitaKeskella(int vari) 
{
	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa
	
	//valkeille ydinkeskusta

	
	
	//valkeille laitakeskusta
	


	//mustille ydinkeskusta
	
	//mustille laitakeskusta
	double tulos = 0;
	float sotilas;
	float hevonen;

	if (onkoAvausTaiKeskipeli(0)) {
		sotilas = 0.5;
		hevonen = 0.3;
	}
	else {
		sotilas = 0.15;
		hevonen = 0.1;
	}

	if (_lauta[3][4] != NULL) {
		if (_lauta[3][4]->getVari() == 0)
			tulos = tulos + sotilas;
		else if (_lauta[3][4]->getVari() == 1)
			tulos = tulos - sotilas;
	}

	if (_lauta[4][4] != NULL) {
		if (_lauta[4][4]->getVari() == 0)
			tulos = tulos + sotilas;
		else if (_lauta[4][4]->getVari() == 1)
			tulos = tulos - sotilas;
	}

	if (_lauta[4][3] != NULL) {
		if (_lauta[4][3]->getVari() == 0)
			tulos = tulos + sotilas;
		else if (_lauta[4][3]->getVari() == 1)
			tulos = tulos - sotilas;
	}

	if (_lauta[3][3] != NULL) {
		if (_lauta[3][3]->getVari() == 0)
			tulos = tulos + sotilas;
		else if (_lauta[3][3]->getVari() == 1)
			tulos = tulos - sotilas;
	}
	for (int i = 0; i < 8; i++) {
		if (_lauta[2][i] != NULL) {
			if (_lauta[2][i]->getKoodi() == 1)
				tulos = tulos + hevonen;
			else if (_lauta[2][i]->getKoodi() == 7)
				tulos = tulos - hevonen;
		}
	}
	for (int i = 0; i < 8; i++) {
		if (_lauta[5][i] != NULL) {
			if (_lauta[5][i]->getKoodi() == 1)
				tulos = tulos + hevonen;
			else if (_lauta[5][i]->getKoodi() == 7)
				tulos = tulos - hevonen;
		}
	}
	return tulos;
}


double Asema::linjat(int vari) 
{
	return 0;
	
	//valkoiset
	
	//mustat
	
}

MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	
	// Rekursion kantatapaus 1: peli on loppu
	
	// Rekursion kantatapaus 2: katkaisusyvyydess‰
	
	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys) 
{
	MinMaxPaluu paluu;
	paluu._evaluointiArvo = -500;

	std::list<Siirto> lista;
	std::list<Siirto>::iterator it;

	if (syvyys == 0) { paluu._evaluointiArvo = evaluoi(); return paluu; }

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (_lauta[x][y] != NULL)
			{
				if (_lauta[x][y]->getVari() == 0)
				{
					int koodi = _lauta[x][y]->getKoodi();
					Ruutu* ruutu = new Ruutu(x, y);

					switch (koodi) {

					case 0: vt->annaSiirrot(lista, ruutu, this, 0); break;
					case 1: vr->annaSiirrot(lista, ruutu, this, 0); break;
					case 2: vl->annaSiirrot(lista, ruutu, this, 0); break;
					case 3: vd->annaSiirrot(lista, ruutu, this, 0); break;
					case 4: vk->annaSiirrot(lista, ruutu, this, 0); break;
					case 5: vs->annaSiirrot(lista, ruutu, this, 0); break;
					}
				}
			}
		}
	}

	for (it = lista.begin(); it != lista.end(); ++it)
	{
		int koodi = -1;

		if (it->getAlkuruutu().getRivi() == 0 && it->getAlkuruutu().getSarake() == 0 && it->getLoppuruutu().getRivi() == 0 && it->getLoppuruutu().getSarake() == 0) {
		}else if(it->getAlkuruutu().getRivi() == 1 && it->getAlkuruutu().getSarake() == 1 && it->getLoppuruutu().getRivi() == 1 && it->getLoppuruutu().getSarake() == 1){
		}else {

			if (this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] != NULL)
				koodi = this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()]->getKoodi();

			this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()]
				= this->_lauta[it->getAlkuruutu().getSarake()][it->getAlkuruutu().getRivi()];
			this->_lauta[it->getAlkuruutu().getSarake()][it->getAlkuruutu().getRivi()] = NULL;

			MinMaxPaluu temp = mini(syvyys - 1);
			if (temp._evaluointiArvo >= paluu._evaluointiArvo) {
				paluu._evaluointiArvo = temp._evaluointiArvo;
				paluu._parasSiirto = Siirto(it->getAlkuruutu(), it->getLoppuruutu());
			}
			this->_lauta[it->getAlkuruutu().getSarake()][it->getAlkuruutu().getRivi()]
				= this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()];

			if (koodi == -1)
				this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = NULL;
			else
				switch (koodi) {
				case 6: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = mt; break;
				case 7: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = mr; break;
				case 8: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = ml; break;
				case 9: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = md; break;
				case 10: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = mk; break;
				case 11: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = ms; break;
			}
		}
	}
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys) 
{
	MinMaxPaluu paluu;
	paluu._evaluointiArvo = 500;

	std::list<Siirto> lista;
	std::list<Siirto>::iterator it;

	if (syvyys == 0) { paluu._evaluointiArvo = evaluoi(); return paluu; }

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (_lauta[x][y] != NULL)
			{
				if (_lauta[x][y]->getVari() == 1)
				{
					int koodi = _lauta[x][y]->getKoodi();
					Ruutu* ruutu = new Ruutu(x, y);

					switch (koodi) {

					case 6: mt->annaSiirrot(lista, ruutu, this, 1); break;
					case 7: mr->annaSiirrot(lista, ruutu, this, 1); break;
					case 8: ml->annaSiirrot(lista, ruutu, this, 1); break;
					case 9: md->annaSiirrot(lista, ruutu, this, 1); break;
					case 10: mk->annaSiirrot(lista, ruutu, this, 1); break;
					case 11: ms->annaSiirrot(lista, ruutu, this, 1); break;
					}
				}
			}
		}
	}
	/*
	laskuri++;
	if (laskuri >= 641)
		int mutsis = 54;
		*/
	for (it = lista.begin(); it != lista.end(); ++it)
	{
		if (it->getAlkuruutu().getRivi() == 0 && it->getAlkuruutu().getSarake() == 0 && it->getLoppuruutu().getRivi() == 0 && it->getLoppuruutu().getSarake() == 0) {
		}
		else if (it->getAlkuruutu().getRivi() == 1 && it->getAlkuruutu().getSarake() == 1 && it->getLoppuruutu().getRivi() == 1 && it->getLoppuruutu().getSarake() == 1) {
		}else {
			int koodi = -1;

			laskuri++;
			if (laskuri >= 70309)
				int mutsis = 54;

			if (this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] != NULL)
				koodi = this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()]->getKoodi();

			this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()]
				= this->_lauta[it->getAlkuruutu().getSarake()][it->getAlkuruutu().getRivi()];
			this->_lauta[it->getAlkuruutu().getSarake()][it->getAlkuruutu().getRivi()] = NULL;

			MinMaxPaluu temp = maxi(syvyys - 1);
			if (temp._evaluointiArvo <= paluu._evaluointiArvo) {
				paluu._evaluointiArvo = temp._evaluointiArvo;
				paluu._parasSiirto = Siirto(it->getAlkuruutu(), it->getLoppuruutu());
			}
			this->_lauta[it->getAlkuruutu().getSarake()][it->getAlkuruutu().getRivi()]
				= this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()];
			if (koodi == -1)
				this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = NULL;
			else
				switch (koodi) {
				case 0: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vt; break;
				case 1: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vr; break;
				case 2: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vl; break;
				case 3: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vd; break;
				case 4: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vk; break;
				case 5: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vs; break;
				}
		}
	}

	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* uhattu, int vastustajanVari)
{
	std::list<Siirto> lista;
	std::list<Siirto>::iterator it;
	bool uhkaus = false;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (_lauta[x][y] != NULL)
			{
				if (_lauta[x][y]->getVari() == vastustajanVari)
				{
					int koodi = _lauta[x][y]->getKoodi();
					Ruutu* ruutu = new Ruutu(x, y);

					switch (koodi) {

					case 0: vt->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					case 1: vr->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					case 2: vl->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					case 3: vd->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					case 4: vk->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					case 5: vs->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					case 6: mt->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					case 7: mr->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					case 8: ml->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					case 9: md->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					case 10: mk->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					case 11: ms->annaSiirrot(lista, ruutu, this, vastustajanVari); break;
					}
				}
			}
		}
	}

	for (it = lista.begin(); it != lista.end() && !uhkaus; ++it)
	{
		int loppuRivi = it->getLoppuruutu().getRivi();
		int loppuSarake = it->getLoppuruutu().getSarake();
		int uhattuRivi = uhattu->getRivi();
		int uhattuSarake = uhattu->getSarake();

		if (loppuRivi == uhattuRivi) {
			if (loppuSarake == uhattuSarake) {
				uhkaus = true;
			}
		}
	}
	if (uhkaus)
		return true;
	else
		return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari) 
{ 
	std::list<Siirto>::iterator it;

	for (it = lista.begin(); it != lista.end();) 
	{
		bool loytynyt = false;
		bool poista = false;
		int koodi = -1;
		
		if (this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] != NULL) 
			koodi = this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()]->getKoodi();

		this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()]
			= this->_lauta[it->getAlkuruutu().getSarake()][it->getAlkuruutu().getRivi()];
		this->_lauta[it->getAlkuruutu().getSarake()][it->getAlkuruutu().getRivi()] = NULL;

		Ruutu testiAlku = (it->getAlkuruutu());
		Ruutu testiLoppu = (it->getLoppuruutu());
		
		for (int x = 0; x < 8 && !loytynyt; x++)
		{
			for (int y = 0; y < 8 && !loytynyt; y++)
			{
				if (_lauta[x][y] != NULL)
				{
					if (it->getAlkuruutu().getRivi() == 0 && it->getAlkuruutu().getSarake() == 4 && it->getLoppuruutu().getRivi() == 0 && it->getLoppuruutu().getSarake() == 3 && x == 3 && y == 0) {
						int stop = 1;
					}

					Ruutu kakka(x, y);
					Ruutu* ruutu = &kakka;
					if (this->_lauta[x][y]->getKoodi() == vk->getKoodi() && this->_lauta[x][y]->getVari() == getSiirtovuoro()) {
						loytynyt = true;
						poista = (onkoRuutuUhattu(ruutu, 1));
					}
					if (this->_lauta[x][y]->getKoodi() == mk->getKoodi() && this->_lauta[x][y]->getVari() == getSiirtovuoro()) {
						loytynyt = true;
						poista = (onkoRuutuUhattu(ruutu, 0));
					}
				}
			}
		}
		this->_lauta[it->getAlkuruutu().getSarake()][it->getAlkuruutu().getRivi()]
			= this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()];

		if (koodi == -1)
			this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = NULL;
		else
			switch (koodi) {

			case 0: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vt; break;
			case 1: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vr; break;
			case 2: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vl; break;
			case 3: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vd; break;
			case 4: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vk; break;
			case 5: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = vs; break;
			case 6: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = mt; break;
			case 7: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = mr; break;
			case 8: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = ml; break;
			case 9: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = md; break;
			case 10: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = mk; break;
			case 11: this->_lauta[it->getLoppuruutu().getSarake()][it->getLoppuruutu().getRivi()] = ms; break;
			}
		if (poista == true)
			it = lista.erase(it++);
		else
			it++;
	}
}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {

	for (int x = 0; x < 8; x++) 
	{
		for (int y = 0; y < 8; y++) 
		{
			if (_lauta[x][y] != NULL)
			{
				if (_lauta[x][y]->getVari() == getSiirtovuoro())
				{
					int koodi = _lauta[x][y]->getKoodi();
					Ruutu* ruutu = new Ruutu(x, y);

					switch (koodi) {

					case 0: vt->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					case 1: vr->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					case 2: vl->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					case 3: vd->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					case 4: vk->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					case 5: vs->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					case 6: mt->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					case 7: mr->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					case 8: ml->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					case 9: md->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					case 10: mk->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					case 11: ms->annaSiirrot(lista, ruutu, this, getSiirtovuoro()); break;
					}
				}
			}
		}
	}
	huolehdiKuninkaanShakeista(lista, this->getSiirtovuoro());
}