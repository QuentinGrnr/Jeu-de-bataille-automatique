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
    void melangerjeu();
    ~jeu_cartes();
};


#endif
