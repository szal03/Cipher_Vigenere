#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

int odszyfrowanie(string text, string second_text, string key)
{
	ifstream d;
	ofstream e;
	d.open("tutaj_bedzie_zaszyfrowany tekst.txt");
	e.open("tutaj_bedzie_odszyfrowany_tekst");
	int k = 0;
	string line;
	string s;
	//getline(cin, s);
	//cout << "wprowadz zaszyfrowany tekst: ";
	getline(d, text);
	cout << "wprowadz klucz: ";
	cin >> key;
	//cout<<"ile kolumn?";


	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '\x84')
		{
			second_text[i] = 32;
		}
		else
		{
			second_text[i] = (((text[i] - 122) - (key[k] - 97)) % 26) + 122;
			k++;
			if (k == key.length())
			{
				k = 0;
			}
		}
	}
	cout << endl << "odszyfrowany tekst: \n\n";

	for (int i = 0; i < text.length(); i++) 
	{
		cout << second_text[i];
		e << second_text[i]; // odszyfrowany juz tekst
	}

	cout << endl << endl;
	d.close();
	e.close();

	return 0;
}

void przeliczanie(unsigned int kolumna[26], string second_text, unsigned int ile_kolumn, int ktora_kolumna) 
{
	int pozycja = 0; //pozycja kolumny
	int indeks_litery; //ascii 
	//int a;
	for (int i = 0; i < second_text.length(); i++)
	{
		if (pozycja == ktora_kolumna)
		{
			indeks_litery = (int)second_text[i] - 97;
			kolumna[indeks_litery]++;
		}
		pozycja++;
		if (pozycja >= ile_kolumn)
		{
			pozycja = 0;
		}
	}
}

void zamiana(unsigned int kolumna[26]) //przesuwanie wartosci // musi byc 26
{
	int przesuniecie = kolumna[0]; //o ile 
	for (int j = 0; j < 26; j++)
	{
		if (j <= 24)
		{
			kolumna[j] = kolumna[j + 1];
		}
		else
		{
			kolumna[25] = przesuniecie;
		}
	}
}

int szyfrowanie(string text, string second_text, string key)  //second_text - tekst wychdz�cy
{
	//
	unsigned int kolumna1[26];
	unsigned int kolumna2[26];
	unsigned int indeks_klucza;
	unsigned int ile_kolumn; // tutaj zmieniaj d�ugo�� klucza - na ile kolumn podzieli�
								 //dlugosc_klucza = key.size();
	double wspolczynnik = 0;
	string klucz;
	int N = 0;
	int N1 = 0;
	//klucz = key;
	string s; //lancuch slow
	int m = 0;
	//int dlugosc_klucza; //dlugosc klucza
	//plik - otwieranie, wpisywanie itd
	ifstream c;
	ofstream d;
	string line;
	c.open("tekst_Vigenere2.txt");
	d.open("tutaj_bedzie_zaszyfrowany tekst.txt");

	//	getline(cin, s);
	//	cout << "wpisz tekst: ";
	//getline(cin, text);

	getline(c, text);
	cout << text << "\n\n";
	cout << "wprowadz klucz: ";
	cin >> key;
	cout << "podaj ilosc kolumn: "; // ilosc kolumn=dlugosc klucza // pamietaj o 0 !!!
	cin >> ile_kolumn;


	for (int i = 0; i < text.length(); i++) //tablica ascii
	{
		if (text[i] == 32)
		{
			second_text[i] = '\x84';
		}
		else
		{
			second_text[i] = (((text[i] - 97) + (key[m] - 97)) % 26) + 97;
			m++;
			if (m == key.length())
			{
				m = 0;
			}
		}
	}

	cout << endl << "zaszyfrowany tekst: \n";
	for (int i = 0; i < text.length(); i++)
	{
		cout << second_text[i];
		d << second_text[i];
	}
	cout << endl << endl;

	for (int i = 0; i < 26; i++)
	{
		kolumna1[i] = 0;
		kolumna2[i] = 0;
	}

	//zad 2 ##
	przeliczanie(kolumna1, second_text, ile_kolumn, 0);


	for (int i = 0; i < 26; i++)
	{
		N += kolumna1[i];
		wspolczynnik += kolumna1[i] * (kolumna1[i] - 1);
	}
	cout << "\n";
	cout << " Indeks zgodnosci dla zadanego podzialu na kolumny : " << wspolczynnik / (N*(N - 1)) << endl; // wzorek z zadania
	cout << "\n";

	//zad3 ###
	for (int i = 0; i < 26; i++)
	{
		kolumna1[i] = 0;
	}
	

	for (int e = 0; e < ile_kolumn; e++)
	{
		przeliczanie(kolumna1, second_text, ile_kolumn, e);

		for (int j = 0; j < ile_kolumn; j++)
		{
			if (j > e)
			{
				przeliczanie(kolumna2, second_text, ile_kolumn, j);
				N = 0;
				N1 = 0;
				wspolczynnik = 0;
				for (int k = 0; k < 26; k++)
				{
					N += kolumna1[k];
					N1 += kolumna2[k];
					wspolczynnik += (kolumna1[k] * kolumna2[k]);
				}
				cout << "\n";
				//odp zad3
				cout << " wspolczynnik miedzy kolumna: " << e + 1 << " a kolumna " << j + 1 << " = " << wspolczynnik / (N*N1) << "\n";

				for (int k = 0; k < 26; k++)
				{
					kolumna2[k] = 0;
				}
			}
		}
		for (int j = 0; j < 26; j++)
		{
			kolumna1[j] = 0;
		}
	}

	c.close();
	d.close();

	return 0;
}

int main() 
{
	
	string text; // tekst wejscia
	string second_text; // tekst wyj�cia 
	string key; // klucz/haslo
	//string tekst;
	string line;
	string b,c;
	ifstream a;
	//
	unsigned int kolumna1[26];
	unsigned int kolumna2[26];
	unsigned int indeks_klucza;
	//dlugosc_klucza = key.size();
	double wspolczynnik = 0;
	string klucz;
	int N = 0; // z zadania
	int N1 = 0; //z zadania
	//
	//klucz = key;
	//
	a.open("tekst_Vigenere2.txt");
	
	while (getline(a, line))
	{
		//cout << line;
	second_text = line;
	}
	

	//cout << "\n\n";
	cout << "1 - zaszyfruj tekst" << endl;
	cout << "2 - odszyfruj tekst" << endl;


	int odp;
	cin >> odp;


	switch (odp)
	{
	case 1:
		szyfrowanie(text, second_text, key);
		break;
	case 2:
		odszyfrowanie(text, second_text, key);
		break;
	default:
		cout << "zly wybor" << endl << endl;
		break;
	}

	a.close();
	system("pause");
	//return 0;
}
