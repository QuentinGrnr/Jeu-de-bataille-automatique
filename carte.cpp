#include "carte.h"

carte::carte(int forme, int valeur, carte *suivant) {
    this->valeur = valeur;
    this->forme = forme;
    this->suivant = suivant;
}

carte::carte() {
    this->valeur = 0;
    this->forme = 0;
    this->suivant = nullptr;
}

carte::carte(int forme, int valeur) {
    this->valeur = valeur;
    this->forme = forme;
    this->suivant = nullptr;
}
