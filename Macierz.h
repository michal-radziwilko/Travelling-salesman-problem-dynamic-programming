#pragma once
class Macierz
{
public:
	int wierzcholki, dwaDoWierzcholki;
	Macierz(int wierzcholki_);
	~Macierz();
	void wyswietlMacierz();
	void losowaMacierz();
	int **a, **g, **p;
	void DynamiczneTSP();
	int MinDroga(int start, int set);
	void trasa(int start, int set);
	void wpiszMacierz();
	long long int read_QPC();
};

