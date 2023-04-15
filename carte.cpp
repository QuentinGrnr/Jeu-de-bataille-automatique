#include "carte.h"

carte::carte(int forme, int valeur, carte *suivant) {
    this->valeur = valeur;
    this->forme = forme;
    this->suivant = suivant;
    this->gagnant = false;
}

carte::carte() {
    this->valeur = 0;
    this->forme = 0;
    this->suivant = nullptr;
    this->gagnant = false;
}

carte::carte(int forme, int valeur) {
    this->valeur = valeur;
    this->forme = forme;
    this->suivant = nullptr;
    this->gagnant = false;
}

carte::~carte() {
    this->suivant = nullptr;
}
