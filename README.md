# LasVegasQuicksort
Introducing random numbers to optimize algorithms

Il programma realizzato ordina un vettore di 10^4 elementi attraverso un algoritmo QuickSort di tipo Las Vegas;

Vengono poi stimati valori atteso e varianza del numero di confronti effuettuati basandosi su 10^5 run.

Viene quindi riempito il file "confronti.dat" e creati i due istogrammi (uno classico e uno normalizzato).

Il programma stima inoltre empiricamente il numero di volte in cui LVQuickSort effettua il doppio e il quintuplo del valor medio dei confronti;
Questa operazione molto probabilmente ritornerà 0 per questo numero di run.


Per far girare il programma e creare gli istogrammi basta lanciare il makefile.
