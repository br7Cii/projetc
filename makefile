# Compilation de l'exécutable
programme: main.o algo1.o algo2.o algo3.o fonction_allocation.o
	gcc -o programme main.o algo1.o algo2.o algo3.o fonction_allocation.o

# Compilation des fichiers objets
main.o: main.c fonction_allocation.h algo1.h algo2.h algo3.h
	gcc -c main.c

algo1.o: algo1.c algo1.h fonction_allocation.h fonction_commun.h
	gcc -c algo1.c

algo2.o: algo2.c algo2.h fonction_allocation.h
	gcc -c algo2.c

algo3.o: algo3.c algo3.h fonction_allocation.h fonction_commun.h
	gcc -c algo3.c

fonction_allocation.o: fonction_allocation.c fonction_allocation.h
	gcc -c fonction_allocation.c

# Nettoyage
clean:
	rm -f programme main.o algo1.o algo2.o algo3.o fonction_allocation.o
