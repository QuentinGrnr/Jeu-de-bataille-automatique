#include "jeu_cartes.h"
#include "carte.h"
#include <iostream>
using namespace std;

jeu_cartes::jeu_cartes() {
    this->head = nullptr;
    this->tail = nullptr;
    this->nb_cartes = 0;
    cout << "Creation du jeu de cartes" << endl;
}

void jeu_cartes::remplirjeu() {
    carte *tmp;
    this -> head = new carte(0,2);
    this->nb_cartes++;
    tmp =  this->head;
    for (int i = 0; i < 4 ; i++){
        for (int j = 2 ; j < 15 ; j++) {
            if (i != 0 || j != 2){
                tmp->suivant = new carte(i, j);
                tmp = tmp->suivant;
                this->nb_cartes++;
            }
        }
    }
    this->tail = tmp;
    delete tmp;
    cout << "Le jeu de cartes a ete rempli" << endl;
}

jeu_cartes::~jeu_cartes() {
    this->viderjeu();
}

void jeu_cartes::afficherjeu() {
    carte *tmp;
    tmp = this->head;
    for (int i = 0; i < this->nb_cartes; i++){
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
        tmp = tmp->suivant;
    }
    delete tmp;
}

void jeu_cartes::addhead(carte *c) {
    carte *tmp = new carte (c->forme, c->valeur);
    if (this->head == nullptr){
        this->head = tmp;
        this->nb_cartes++;
        return;
    }
    tmp->suivant = this->head;
    this->head = tmp;
    this->nb_cartes++;
    delete tmp;
}

void jeu_cartes::addtail(carte *c) {
    carte *tmp = new carte (c->forme, c->valeur);
    if (this->tail == nullptr){
        this->tail = tmp;
        this->nb_cartes++;
        return;
    }
    this->tail->suivant = tmp;
    this->tail = tmp;
    this->nb_cartes++;
    delete tmp;
}

void jeu_cartes::viderjeu() {
    carte *tmp1 = this->head;
    carte *tmp2;
    while (tmp1 != nullptr) {
        tmp2 = tmp1->suivant;
        if (tmp2 != nullptr){
            delete tmp1;
            tmp1 = tmp2;
        } else {
            break;
        }
    }
    head = nullptr;
    tail = nullptr;
    nb_cartes = 0;
}

void jeu_cartes::melangerjeu() {
    jeu_cartes jeu_vide;
    carte *tmp= this->head;
    while (this->nb_cartes != 0){
        if (this->nb_cartes % 2 == 0){
            jeu_vide.addtail(tmp);
        } else {
            jeu_vide.addhead(tmp);
        }
        tmp = tmp->suivant;
        this->nb_cartes--;
    }
}

//défois ça crash défois non ==> a régler


