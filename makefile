all:
	g++ LV_QuickSort.cpp -o LV_QuickSort

	@echo "Avvio il programma, la sequenza verrà ordinata in qualche minuto."

	./LV_QuickSort

	@echo "Creo gli istogrammi."

	python3 istogramma.py

	@echo "Il programma è terminato con successo."

clean:
	rm -f Istogramma.png IstogrammaNormalizzato.png confronti.dat espettazione.dat LV_QuickSort