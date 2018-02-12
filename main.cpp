#include "Macierz.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
while(true)
{
	Macierz *macierz;
	string nazwa;
	int wierzcholki, waga;

	cout << endl << "          Podaj nazwe pliku do wczytania grafu: ";
	cin >> nazwa;
	nazwa = nazwa + ".txt";
	ifstream plik(nazwa);
	if (!plik)
	{
		cout << endl << "          Nie mozna otworzyc pliku" << endl;
		goto etykieta;

	}

	else
	{

		{
			plik >> wierzcholki;
			if (!plik || wierzcholki <= 1)
			{
				cout << endl << "          Cos nie tak!" << endl << "          Liczba wierzcholkow nie jest prawidlowa." << endl;

				goto etykieta;
			}

			else
			{
				macierz = new Macierz(wierzcholki);


				for (int i = 0; i < wierzcholki; i++)
				{
					for (int j = 0; j < wierzcholki; j++)
					{

						plik >> waga;
						if (waga < -1)
						{
							cout << endl << "          Cos nie tak! Zle podane krawedzie!" << endl;
							goto etykieta;
							break;
						}
						else
						{
							macierz->a[i][j] = waga;
						}
					}
				}
				plik.close();
			}
		}
	}

	cout << endl << "          Wczytano graf." << endl;


	macierz->wyswietlMacierz();
	macierz->DynamiczneTSP();

}
}