# importo la libreria
import matplotlib.pyplot as plt

import numpy as np

# prendo il valore atteso
e = open('espettazione.dat', 'r')

e.seek(0)
esp = int(e.readline())

# prendo i confronti
f = open('confronti.dat', 'r')

# faccio solo un file con 50 bin
binCounts = [50]

# cicla da 1 a 50
for binCount in binCounts:
	vals = []
	f.seek(0)

	# riempo vals
	for line in f.readlines():
		vals.append(int(line))

	n, bins, patches = plt.hist(vals, bins=binCount)

	#guardo dove si trova il valore di espettazione
	# mi fermo quando l'espettazione è nel bin giusto
	# bins[0] limite sx del primo bin; bin[1] limite destro
	# per questo parto a contare da count=-1, poiché se ad esempio mi trovassi
	# nel primo bin entrerebbe nell'if una volta (perché è maggiore del limite sx di esso)
	# quindi dovrei alla fine count dovrebbe essere 0
	count = -1;
	for mayEsp in bins:
		if(esp > mayEsp):
			count = count + 1

	plt.gca().set(title='Istogramma LV_Quicksort', xlabel='Numero di Confronti', ylabel='Frequenza')
	patches[count].set_fc('y')	
	plt.savefig(f'Istogramma.png')
	plt.close()

	weights = np.ones_like(vals)/float(len(vals))
	n, bins, patches = plt.hist(vals, weights=weights, bins=binCount)
	plt.gca().set(title='Istogramma LV_Quicksort Normalizzato', xlabel='Numero di Confronti', ylabel='Frequenza')
	patches[count].set_fc('y')	
	plt.savefig(f'IstogrammaNormalizzato.png')
	plt.close()
