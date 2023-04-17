#include "jeu_cartes.h"
#include "carte.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Bienvenu dans cette simulation de jeu de bataille" << endl;
    cout << "Combien de joueurs voulez-vous ?" << endl;
    int nb_joueurs;
    cin >> nb_joueurs;
    jeu_cartes jeu;
    jeu.jouer(nb_joueurs);
    return 0;
}
