#ifndef TP4S2POO_JEU_CARTES_H
#define TP4S2POO_JEU_CARTES_H
#include "carte.h"

class jeu_cartes {
    carte *tete;
    carte *queue;
    int nb_cartes;
public:
    jeu_cartes();
    void remplirjeu();
    void afficherjeu();
    void melangerjeu(jeu_cartes jeu_vide);
    ~jeu_cartes();
};


#endif
