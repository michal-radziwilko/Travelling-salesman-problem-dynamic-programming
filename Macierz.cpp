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

	if (g[start][zbior] != -1)	// Jesli ju¿ raz wywo³ywaliœmy funkcjê MinDroga o danych parametrach
		return g[start][zbior];	// to jej wynik bêdzie zapisany na odpowiedniej pozycji w tablicy g, wiêc go zwracamy zamiast wywo³ywaæ funkcjê jeszcze raz. 

	else {
		for (int i = 0; i < wierzcholki; i++)
		{   // n_potega-1 to zbiór wszystkich wierzcho³ków poza wierzcho³kiem zerowym.
			maska = (dwaDoWierzcholki - 1) - ((int)pow(2, i));	// Usuwamy wierzcho³ek i-ty ze zbioru wierzcho³ków.
			zmaskowane = zbior&maska;	// Generujemy nowy zbiór wierzcho³ków.
			if (zmaskowane != zbior)	// Gdy wygenerowany zbiór bêdzie ró¿ny od zbioru pocz¹tkowego (w niektórych przypadkach maskowania wygenerowany zostanie ten sam zbiór (np. 12&14 = 12).
			{
				funkcja = a[start][i] + MinDroga(i, zmaskowane);//	Wzór funkcji g³ownej algorytmu. Oznacza d³ugoœæ minimalnej drogi zaczynaj¹cej siê od wierzcho³ka i-tego,
															// przechodz¹cej przez wszystkie wierzcho³ki w zbiorze "zmaskowane", oraz koñcz¹cej siê na wierzcho³ku zerowym.
				if (funkcja < wynik || wynik == -1) // Szukanie minimum.
				{
					wynik = funkcja;
					p[start][zbior] = i;	// Numer wierzcho³ka, dla którego zosta³o zwrócone minimum jest przechowywany w tablicy "rodziców".
				}
			}
		}

		g[start][zbior] = wynik; // Wynik przechowywany w tablicy d³ugoœci minimalnych dróg.

		return wynik;	// Zwracamy d³ugoœæ minimalnej drogi.
	}
}

void Macierz::trasa(int start, int zbior)
{
	if (p[start][zbior] == -1) // Jeœli minimalna droga nie jest okreœlona to koñczymy funkcjê.
		return;
	int i = p[start][zbior];	// Wierzcho³ek od którego zaczyna sie minimalna droga, przechowywany jest w tablicy "rodziców".
	int maska = (dwaDoWierzcholki - 1) - ((int)pow(2, i));	// Usuwamy wierzcho³ek i-ty ze zbioru wierzcho³ków.
	int zmaskowane = zbior&maska;	// Generujemy nowy zbiór wierzcho³ków, ze wszystkich wierzcho³ków w zbiorze z wykluczeniem wierzcho³ka i-tego.

	cout << " -> " << i;	// Wypisujemy wierzcho³ek i odczytujemy kolejny wierzcho³ek minimalnej drogi.
	trasa(i, zmaskowane);
}
