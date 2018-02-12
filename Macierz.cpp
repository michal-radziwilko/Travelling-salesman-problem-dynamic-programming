#include "Macierz.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <Windows.h>


using namespace std;

long long int Macierz::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

Macierz::Macierz(int wierzcholki_)
{
	wierzcholki = wierzcholki_;
	dwaDoWierzcholki = (int)pow(2, wierzcholki);
	a = new int *[wierzcholki];


	for (int i = 0; i < wierzcholki; i++)
		a[i] = new int[wierzcholki];

	for (int i = 0; i < wierzcholki; i++)
	{
		for (int j = 0; j < wierzcholki; j++)
			a[i][j] = -1;	
	}
}


Macierz::~Macierz()
{
	for (int i = 0; i < wierzcholki; i++)
		delete[] a[i];
	
	delete[] a;
}

void Macierz::losowaMacierz()
{
	srand(time(NULL));


	for (int i = 0; i < wierzcholki; i++)
	{
		for (int j = 0; j < wierzcholki; j++)
		{
			if(i==j) a[i][j] = -1;

			else a[i][j] = ((rand() % 20) + 1);
		}
	}
}


void Macierz::wpiszMacierz()
{

	for (int i = 0; i < wierzcholki; i++)
	{
		for (int j = 0; j < wierzcholki; j++)
		{
			cin >> a[i][j];
		}
	}
}


void Macierz::wyswietlMacierz()
{
	cout << endl << endl << "Graf w postaci macierzy: " << endl << endl;

	for (int i = 0; i < wierzcholki; i++)
	{
		for (int j = 0; j < wierzcholki; j++)
				cout << setw(4) << a[i][j];

		cout << endl << endl;
	}

	cout << endl << endl;
}

void Macierz::DynamiczneTSP()
{
	int czas = 0;

	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	start = read_QPC();

	dwaDoWierzcholki = (int)pow(2, wierzcholki);
	g = new int *[wierzcholki];
	p = new int *[wierzcholki];


	for (int i = 0; i < wierzcholki; i++)
	{
		g[i] = new int[dwaDoWierzcholki];
		p[i] = new int[dwaDoWierzcholki];
	}

	for (int i = 0; i < wierzcholki; i++)
	{
		for (int k = 0; k < dwaDoWierzcholki; k++)
		{
			g[i][k] = -1;
			p[i][k] = -1;

		}
		g[i][0] = a[i][0];
	}

	int wynik = MinDroga(0, dwaDoWierzcholki - 2);

	elapsed = read_QPC() - start;
	czas = (1000000.0 * elapsed) / frequency;

	cout << endl << "Najkrotsza trasa wynosi: " << wynik << endl;
	cout << endl << "Droga: "<< "0";

	start = read_QPC();

	trasa(0, dwaDoWierzcholki - 2);
	
	elapsed = read_QPC() - start;
	czas = czas + (1000000.0 * elapsed) / frequency;

	cout << " -> 0" << endl << endl;
	cout << endl << "Czas[us]: " << czas << endl;


}

int Macierz::MinDroga(int start, int zbior)
{
	int zmaskowane, maska, wynik = -1, funkcja;// Wynik przechowuje minimum.

	if (g[start][zbior] != -1)	// Jesli ju� raz wywo�ywali�my funkcj� MinDroga o danych parametrach
		return g[start][zbior];	// to jej wynik b�dzie zapisany na odpowiedniej pozycji w tablicy g, wi�c go zwracamy zamiast wywo�ywa� funkcj� jeszcze raz. 

	else {
		for (int i = 0; i < wierzcholki; i++)
		{   // n_potega-1 to zbi�r wszystkich wierzcho�k�w poza wierzcho�kiem zerowym.
			maska = (dwaDoWierzcholki - 1) - ((int)pow(2, i));	// Usuwamy wierzcho�ek i-ty ze zbioru wierzcho�k�w.
			zmaskowane = zbior&maska;	// Generujemy nowy zbi�r wierzcho�k�w.
			if (zmaskowane != zbior)	// Gdy wygenerowany zbi�r b�dzie r�ny od zbioru pocz�tkowego (w niekt�rych przypadkach maskowania wygenerowany zostanie ten sam zbi�r (np. 12&14 = 12).
			{
				funkcja = a[start][i] + MinDroga(i, zmaskowane);//	Wz�r funkcji g�ownej algorytmu. Oznacza d�ugo�� minimalnej drogi zaczynaj�cej si� od wierzcho�ka i-tego,
															// przechodz�cej przez wszystkie wierzcho�ki w zbiorze "zmaskowane", oraz ko�cz�cej si� na wierzcho�ku zerowym.
				if (funkcja < wynik || wynik == -1) // Szukanie minimum.
				{
					wynik = funkcja;
					p[start][zbior] = i;	// Numer wierzcho�ka, dla kt�rego zosta�o zwr�cone minimum jest przechowywany w tablicy "rodzic�w".
				}
			}
		}

		g[start][zbior] = wynik; // Wynik przechowywany w tablicy d�ugo�ci minimalnych dr�g.

		return wynik;	// Zwracamy d�ugo�� minimalnej drogi.
	}
}

void Macierz::trasa(int start, int zbior)
{
	if (p[start][zbior] == -1) // Je�li minimalna droga nie jest okre�lona to ko�czymy funkcj�.
		return;
	int i = p[start][zbior];	// Wierzcho�ek od kt�rego zaczyna sie minimalna droga, przechowywany jest w tablicy "rodzic�w".
	int maska = (dwaDoWierzcholki - 1) - ((int)pow(2, i));	// Usuwamy wierzcho�ek i-ty ze zbioru wierzcho�k�w.
	int zmaskowane = zbior&maska;	// Generujemy nowy zbi�r wierzcho�k�w, ze wszystkich wierzcho�k�w w zbiorze z wykluczeniem wierzcho�ka i-tego.

	cout << " -> " << i;	// Wypisujemy wierzcho�ek i odczytujemy kolejny wierzcho�ek minimalnej drogi.
	trasa(i, zmaskowane);
}
