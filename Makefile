output: main carte.o jeu_cartes.o
	./main

main : main.cpp carte.o jeu_cartes.o
	g++ -o main carte.o jeu_cartes.o main.cpp

jeu_cartes.o : jeu_cartes.cpp jeu_cartes.h carte.h
	g++ -c jeu_cartes.cpp

carte.o : carte.cpp carte.h
	g++ -c carte.cpp