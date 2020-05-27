#include <windows.h>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*FUNKCJA POMOCNICZA DO quick_sort
Funkcja ma na celu zmusic quick_sort do uzywania elementu środkowego jako pivot, zamiast elementu ostatniego.
Poprawia to wydajność w niektórych przypadkach*/
long int pivot_ze_srodka(long int tab[],long int pierwszy_elem, long int ostatni_elem)
{
    long int mid = pierwszy_elem+(ostatni_elem-pierwszy_elem)/2;
    long int wartosc_pivota = tab[mid];
    swap(tab[mid],tab[ostatni_elem]);
    return wartosc_pivota;
}

/*********************************QUICKSORT****************************************************/
long int znajdz_klucz_QS( long int tab[], long int pierwszy_elem, long int ostatni_elem )
{
    long int pivot = pivot_ze_srodka(tab,pierwszy_elem,ostatni_elem);
    long int temp = 0;
	long int klucz = pierwszy_elem-1;
	long int licznik = pierwszy_elem;

	while ( licznik < ostatni_elem )
    {
        if(tab[licznik] < pivot)
        {
            klucz++;
            if(klucz != licznik)
            {
              swap(tab[klucz],tab[licznik]);
            }
        }
        licznik++;
    }
    klucz++;
    if(klucz != ostatni_elem)
        {
           swap(tab[klucz],tab[ostatni_elem]);
        }
return klucz;


}
void quick_sort (long int tab[],long int pierwszy_elem, long int ostatni_elem)
{
    if (pierwszy_elem >= ostatni_elem)
        {
           return;
        }
    long int klucz = znajdz_klucz_QS(tab,pierwszy_elem,ostatni_elem);

      if ( klucz - pierwszy_elem < ostatni_elem - klucz )
        {
            quick_sort(tab,pierwszy_elem,klucz-1);
            quick_sort(tab,klucz+1,ostatni_elem);
        }
        else
        {
            quick_sort(tab,klucz+1,ostatni_elem);
            quick_sort(tab,pierwszy_elem,klucz-1);
        }
}

/*********************************SHELLSORT****************************************************/
void shell_sort(long int tab[], long int rozm)
{
  long int i, j, przerwa, temp;

  przerwa = rozm/2;

  while(przerwa > 0) {

    i = przerwa;

    while(i < rozm)
    {
      temp = tab[i];


        for(j = i; (j >= przerwa) && (tab[j - przerwa] > temp); )
            {
                tab[j] = tab[j - przerwa];
                j = j - przerwa;
            }

      tab[j] = temp;
      i++;
    }
    przerwa = przerwa / 2;
  }
}
/*******************************************************************************************/

/*********************************MERGESORT****************************************************/
void merge ( long int tab[],long int pierwszy_elem, long int ostatni_elem, long int srodek)
{

    long int PP = srodek-pierwszy_elem+1;
    long int LP = ostatni_elem-srodek;
    long int *tempP = new long int[PP];   // TABLICE PRZECHOWUJACE LEWA I PRAWA POLOWE CIAGU LICZB
    long int *tempL = new long int[LP];  //


    for(long int i = 0; i < PP; i++)       //
    {                                     //
        tempP[i] = tab[pierwszy_elem+i]; //
    }                                    // WYPELNIANIE TABLIC POLOWAMI DANEGO CIAGU LICZB
    for(long int j = 0; j < LP; j++)    //
    {                                  //
        tempL[j] = tab[srodek + j+1];
    }

    long int it_PP = 0;
    long int it_LP = 0;
    long int it_pocz=pierwszy_elem;


 // GLOWNY ALGORYTM SORTUJACY I ŁĄCZACY DWIE POLOWY
    while (it_PP < PP && it_LP < LP )
    {
        if(tempP[it_PP] <= tempL[it_LP])
            {
             tab[it_pocz] = tempP[it_PP];
             it_PP++;
            }
            else
                {
                 tab[it_pocz] = tempL[it_LP];
                 it_LP++;
                }

            it_pocz++;
    }

    // SORTOWANIE I ŁACZENIE ELEMENTÓW KTÓRE POMIELIŚMY
    while (it_PP < PP )
    {
        tab[it_pocz] = tempP[it_PP];
       it_PP++;
       it_pocz++;
    }
    while (it_LP < LP)
    {
        tab[it_pocz] = tempL[it_LP];
        it_LP++;
        it_pocz++;
    }
    // USUWANIE TABLIC
    delete tempL;
    delete tempP;
}
void mergesort(long int tab[],long int pierwszy_elem, long int ostatni_elem)
{
    if (pierwszy_elem < ostatni_elem )  // WYKONYWANIE DOPOKI NIE DOSZLISMY DO OSTATNIEGO ELEMENTU
    {
       long int  srodek = pierwszy_elem + (ostatni_elem - pierwszy_elem)/2;  // WYBIERANIE ELEMENTU SRODKOWEGO
        mergesort(tab,pierwszy_elem,srodek);   //  REKURENCYJNE WYKONYWANIE ALGORYTMU NA OBU POŁOWACH
        mergesort(tab,srodek+1,ostatni_elem); //
        merge(tab,pierwszy_elem,ostatni_elem,srodek); // ŁĄCZENIE ELEMENTÓW W POSORTOWANY CIĄG
    }
}
/*********************************************************************************************/

/*********************************FUNKCJE POMOCNICZE*************************************************/
/*wyp_full_los - tworzenie dowolnie dużej tablicy nieposortowanych liczb*/
/*posortowana_odwrotnie - tworzenie tablicy liczb posortowanych w odwrotnej kolejności*/
/*wypelniona_procent - tworzenie tablicy liczb, która już częściowo jest posortowana*/
void wyp_full_los(long int tab[], long int rozm)
{
    srand(time(NULL));
    for (long int i = 0; i<rozm; i++)
        {
        tab[i]=rand() % 1000000+ 1;
        }
}
void posortowana_odwrotnie(long int tab[], long int rozm)
{
    wyp_full_los(tab,rozm);
    sort(tab, tab + rozm);
    reverse(tab, tab + rozm);
}
void wypelniona_procent(long int tab[], long int rozm, long int procent)
{
    int do_tego_miejsca = procent/100.0*rozm;

        for (int i = 0; i < do_tego_miejsca; i++)
        {
            tab[i] = i;
        }

    srand(time(NULL));
    for (int j = do_tego_miejsca; j < rozm; j++)
    {
        tab[j] = rand() % 1000000 + 1;
    }
}
void odwracanie(long int tab[], long int rozmiar)
{
    sort(tab, tab + rozmiar);
    reverse(tab, tab+rozmiar);
}
/***********************************************************************************************/

 int main()
{
    ofstream dane;
    long int procent = 99.7;
    long int rozmiar = 50;
    long int *tab = new long int [rozmiar];


    for (int i = 0; i < 1; i++)
        {
        ///////////////////////////////// ////////////////
        //wyp_full_los(tab,rozmiar);                   //
       // wypelniona_procent(tab,rozmiar,procent);    // OPCJE SORTOWANIA
        posortowana_odwrotnie(tab,rozmiar);          //
      ////////////////////////////////////////////////

        high_resolution_clock::time_point t1 = high_resolution_clock::now();  //POMIAR CZASU
        ////////////////////////////////
        //shell_sort(tab,rozmiar);       //
         // QS(tab,0,rozmiar-1);    // WYBOR ALGORYTMU SORTOWANIA
        mergesort(tab,0,rozmiar-1);//
        ////////////////////////////

        cout << '\a'; // SYGNAL INFORMUJACY O WYKONANYM SORTOWANIU
        high_resolution_clock::time_point t2 = high_resolution_clock::now(); // POMIAR CZASU
        auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        dane.open ("example.csv",ios::app);
        dane << duration <<";"<< "\n";    // ZAPISYWANIE CZASU SORTOWANIA DO PLIKU CSV
        dane.close();


        }
cout<<"Ciekawa muzyka";
return 0;
}

