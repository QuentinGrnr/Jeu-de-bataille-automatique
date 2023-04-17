#ifndef TP4S2POO_JEU_CARTES_H
#define TP4S2POO_JEU_CARTES_H
#include "carte.h"

class jeu_cartes {
    carte *head;
    carte *tail;
    int nb_cartes;
public:
    jeu_cartes();
    void remplirjeu();
    void afficherjeu();
    void addhead(carte *c);
    void addtail(carte *c);
    void viderjeu();
    void melangerjeu(int nb_melanges);
    void copy(jeu_cartes *j);
    jeu_cartes* distribuer(int nb_joueurs);
    void jouer(int nb_joueurs);
    void trierjeu();
    void swap(carte *a, carte *b);
    ~jeu_cartes();
};


#endif
