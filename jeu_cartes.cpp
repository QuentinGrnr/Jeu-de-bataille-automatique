#include "jeu_cartes.h"
#include "carte.h"
#include <iostream>
using namespace std;

jeu_cartes::jeu_cartes() {
    this->tete = nullptr;
    this->nb_cartes = 0;
}

void jeu_cartes::remplirjeu() {
    carte *tmp;
    this -> tete = new carte();
    tmp =  this->tete;
    for (int i = 0; i < 4 ; i++){
        for (int j = 2 ; j < 15 ; j++) {
            tmp->suivant = new carte(i, j);
            tmp = tmp->suivant;
            this->nb_cartes++;
            cout << tmp->valeur << " " << tmp->forme << endl;
        }
    }
}

jeu_cartes::~jeu_cartes() {
    carte * temp;

    while (tete != nullptr){
        temp = tete;
        tete = tete -> suivant;
        delete temp;
    }
}

void jeu_cartes::afficherjeu() {
    carte *tmp;
    tmp = this->tete;
    for (int i = 0; i < this->nb_cartes; i++){
        tmp = tmp->suivant;
        switch (tmp->valeur) {
            case 11:
                cout << "Valet ";
                break;
            case 12:
                cout << "Dame ";
                break;
            case 13:
                cout << "Roi ";
                break;
            case 14:
                cout << "As ";
                break;
            default:
                cout << tmp->valeur;
                break;

        }
        switch (tmp->forme){
            case 0:
                cout << " de Trefle" << endl;
                break;
            case 1:
                cout << " de Carreau" << endl;
                break;
            case 2:
                cout << " de Coeur" << endl;
                break;
            case 3:
                cout << " de Pique" << endl;
                break;
            default:
                break;
            }
        }
    }

void jeu_cartes::melangerjeu(jeu_cartes jeu_vide) {
    
}






