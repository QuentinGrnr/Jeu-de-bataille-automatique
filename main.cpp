#include "jeu_cartes.h"
#include "carte.h"
#include <iostream>
using namespace std;

int main() {
    jeu_cartes jeu;
    jeu.jouer(4);
    jeu_cartes* playerstab = jeu.distribuer(5);
    return 0;
}
