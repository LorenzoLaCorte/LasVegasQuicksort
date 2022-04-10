#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>

using namespace std;

// variabili globali:
int dim, n_run;	
int count = 0;

// crea una sequenza di N numeri
vector<int> create_seq(int size)
{
	vector<int> seq(size);

	for(int i=0; i<size; i++)
	{
		seq[i] = rand() % size;
	}
	
	return seq;
}

// calcola l'espettazione
double calc_esp(vector<int> &num_c)
{
	double E_x = 0;

	for(int i=0; i<n_run; i++)
	{
		E_x += num_c[i];
	}
	
	E_x = E_x / n_run;

	return E_x;
}

// calcola la varianza
double calc_var(vector<int> &num_c, double E_x)
{
	double Var_x = 0;

	for(int i=0; i<n_run; i++)
	{
		Var_x += (num_c[i] - E_x)*(num_c[i] - E_x);
	}

	Var_x = Var_x / n_run;

	Var_x = sqrt(Var_x);

	return Var_x;
}

// stampa un vettore
void print_seq(vector<int> &seq)
{
	cout << "-- Stampo il vettore --" << endl;

	for(int i=0; i<seq.size(); i++)
	{
		cout << "Posizione " << i << ": " << seq[i] << endl;
	}

	cout << endl << endl;
}

// funzione ausiliaria al quicksort, necessaria a scambiare due elementi
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

// partizione il vettore rispetto al pivot scelto casualmente
int partition(vector<int> &seq, int min, int max)
{
	int pos_pivot = min+rand()%(max-min+1);
	
	swap(seq[pos_pivot], seq[min]);

	int i = min+1;
	
	for (int j=min+1; j<=max; ++j)
	{
		count++;
		if(seq[j] < seq[min])
		{
			swap(seq[i], seq[j]);
			++i;
		}
	}

	swap(seq[min], seq[i-1]);
	return i-1;


}
 
// chiama partition e si richiama ricorsivamente sulle due sequenze ordinate rispetto al pivot
void LVQuickSort(vector<int> &seq, int min, int max)
{
	if(min < max)
	{
		// chiama partition e fatti restituire la pos. del pivot
		int pos_piv = partition(seq, min, max);
 
		// richiama sulle due partizioni
        	LVQuickSort(seq, min, pos_piv - 1);
        	LVQuickSort(seq, pos_piv + 1, max);
	}
}

int main()
{
	srand(time(NULL));
	cout << "Las Vegas Quicksort -- Lorenzo La Corte" << endl << endl;

	// con I/O
/*
	cout << "Inserisci il numero di run (predefinito 10^5): ";
	cin >> n_run;
	cout << endl;

	cout << "Inserisci la dimensione della sequenza (predefinito 10^4): ";
	cin >> dim;
	cout << endl;
*/

	// con valori predefiniti
	n_run = 100000;
	dim = 10000;

	// costruisco un vettore per il numero di confronti
	vector<int> num_c(n_run);

	for(int i=0; i<n_run; i++)
	{
		// Costruisco una sequenza S di numeri con |S| = 104
		vector<int> S = create_seq(dim);


		// chiamo LVQuickSort 
		// e conto il numero Nj di confronti effettuati 
		// in ogni singolo run j per ordinare la sequenza S. 
		LVQuickSort(S, 0, dim-1);

		num_c[i] = count;
		count = 0;
	}

	// Calcolo il valore medio del numero di confronti 
	double E_x = calc_esp(num_c);

	cout << "Il valore atteso del numero dei confronti è: " << E_x << endl << endl;

	// Calcolo la varianza del numero di confronti 
	double Var_x = calc_var(num_c, E_x);

	cout << "La varianza del numero dei confronti è: " << Var_x << endl << endl;

	// riempo il file di output dei confronti
	ofstream confronti;
	confronti.open ("confronti.dat");

	for(int i=0; i<n_run; i++)
	{
		confronti << num_c[i] << endl;
	}

	confronti.close();

	// riempo il file di output dell'espettazione
	ofstream espettazione;
	espettazione.open ("espettazione.dat");

	espettazione << E_x << endl;

	espettazione.close();

	// stima empiricamente la probabilita con la quale LVQuickSort 
	// effettua il doppio e il quintuplo del valor medio dei confronti.
	int c_doub = 0;
	int c_quint = 0;

	for(int i=0; i<n_run; i++)
	{
		if(num_c[i] >= E_x * 2)
			c_doub++;

		if(num_c[i] >= E_x * 5)
			c_quint++;
	}

	cout << "Stima empirica del numero di volte in cui LVQuickSort effettua: " << endl;
	
	cout << "il doppio del valor medio dei confronti: " << c_doub << endl;

	cout << "il quintuplo del valor medio dei confronti: " << c_quint << endl;
	
	return 0;
}