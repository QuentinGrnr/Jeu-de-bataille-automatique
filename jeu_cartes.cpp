#include "jeu_cartes.h"
#include "carte.h"
#include <iostream>
using namespace std;

jeu_cartes::jeu_cartes() {
    this->head = nullptr;
    this->tail = nullptr;
    this->nb_cartes = 0;
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
    cout << "Le jeu de cartes a ete rempli" << endl << endl;
}

jeu_cartes::~jeu_cartes() {
    this->viderjeu();
}

void jeu_cartes::afficherjeu() {
    carte *tmp;
    tmp = this->head;
    if (tmp == nullptr){
        cout << "Le jeu de cartes est vide" << endl;
        return;
    }
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
    cout << endl;
}

void jeu_cartes::addhead(carte *c) {
    carte *tmp = new carte (c->forme, c->valeur);
    if (this->head == nullptr && this->tail == nullptr){
        this->head = tmp;
        this->tail = tmp;
        this->nb_cartes++;
        return;
    }
    tmp->suivant = this->head;
    this->head = tmp;
    this->nb_cartes++;
}

void jeu_cartes::addtail(carte *c) {
    carte *tmp = new carte (c->forme, c->valeur);
    if (this->tail == nullptr && this->head == nullptr){
        this->tail = tmp;
        this->head = tmp;
        this->nb_cartes++;
        return;
    }
    this->tail->suivant = tmp;
    this->tail = tmp;
    this->nb_cartes++;
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

void jeu_cartes::copy(jeu_cartes *j) {
    this->viderjeu();
    carte *tmp = j->head;
    while (tmp != nullptr){
        this->addtail(tmp);
        tmp = tmp->suivant;
    }
}

void jeu_cartes::melangerjeu() {
    jeu_cartes jeu_vide;
    carte *tmp;
    for (int i = 0; i < 23; i++){ // Melange 15 fois en utilisant la methode tail/head alternée
        tmp = this->head;
        int carte = this->nb_cartes;
        while (carte != 0){
            if (carte % 2 == 0){
                jeu_vide.addtail(tmp);
            } else {
                jeu_vide.addhead(tmp);
            }
            tmp = tmp->suivant;
            carte--;
        }
        this->copy(&jeu_vide);
        jeu_vide.viderjeu();
    }
    cout << "Le jeu de cartes a ete melange 15 fois" << endl << endl;
}

jeu_cartes* jeu_cartes::distribuer(int nb_joueurs) {
    jeu_cartes* playertab = new jeu_cartes[nb_joueurs];
    while (this->nb_cartes != 0){
        for (int i = 0; i < nb_joueurs; i++){
            if (this->nb_cartes != 0){ // Si le jeu de cartes est vide, on break
                playertab[i].addtail(this->head);
                this->head = this->head->suivant;
                this->nb_cartes--;
            } else {
                break;
            }
        }
    }
    return playertab;
}

void jeu_cartes::jouer(int nb_joueurs) {
    this->remplirjeu();
    this->melangerjeu();
    jeu_cartes *playerstab = this->distribuer(nb_joueurs);
    cout << "Voici les cartes de chaque joueur : " << endl << endl;
    for (int i = 0; i < nb_joueurs; i++){
        cout << "Joueur " << i+1 << " : " << endl;
        playerstab[i].afficherjeu();
    }
    cout << "La partie va commencer !" << endl << endl;
    bool play = true;
    carte table[nb_joueurs];// Tableau qui contient les cartes jouées par les joueurs
    jeu_cartes jeu_cartes_gagne; // Jeu de cartes qui contient les cartes que les joueurs peuvent gagner en cas de bataille
    int nbr_players_ingame = 0; // Nombre de joueurs en jeu qui permet de savoir quand la partie est finie (si ==1)
    int nbr_manche = 0; // Nombre de manches jouées
    while (play){

        nbr_players_ingame = 0; // On remet le nombre de joueurs en jeu à 0


        for (int i = 0; i < nb_joueurs; i++){
            if (playerstab[i].nb_cartes != 0){
                table[i] = *playerstab[i].head;
                playerstab[i].head = playerstab[i].head->suivant;
                playerstab[i].nb_cartes--;
                nbr_players_ingame++;
            } else {
                table[i] = carte(-1, -1); // Si le joueur n'a plus de cartes, on met une carte vide dans le tableau
            }
        }

        // on determine le/les gagnant de la manche
        cout << "Voici les cartes jouees par les joueurs pour la manche " << nbr_manche << endl;
        for (int i = 0; i < nb_joueurs; i++){
                if (table[i].valeur != -1){ // Si la carte n'est pas vide
                    table[i].gagnant = false;
                    bool winround= true;
                    cout << "Joueur " << i+1 << " : " << table[i].valeur << endl;
                    for (int j = 0; j <nb_joueurs;  j++) {
                        if (table[i].valeur < table[j].valeur){
                            winround = false;
                        }
                    }
                    if (winround){
                        table[i].gagnant = true;
                    } else {
                        jeu_cartes_gagne.addtail(&table[i]); // Si le joueur n'a pas gagné la manche, on ajoute sa carte dans le jeu de cartes a gagner en fin de manche
                    }
                } else {
                    cout << "Joueur " << i+1 << " ne joue plus" << endl;
                }
        }
        //on compte le nombre de gagnant
        int nbr_gagnant = 0;
        for (int i = 0; i <nb_joueurs;i++) {
            if (table[i].gagnant){
               nbr_gagnant++;
            }
        }

        if (nbr_gagnant == 1){
            for (int i = 0; i < nb_joueurs; i++){
                if (table[i].gagnant){
                    cout << "Le joueur " << i+1 << " a gagne la manche" << endl;
                    while (jeu_cartes_gagne.nb_cartes != 0){
                        playerstab[i].addtail(jeu_cartes_gagne.head);
                        jeu_cartes_gagne.head = jeu_cartes_gagne.head->suivant;
                        jeu_cartes_gagne.nb_cartes--;
                    }
                }
            }
        } else {
            cout << "Il y a une bataille !" << endl;
            //faire algo bataille (fonction séparée pour plus de lisibilité)
        }

        if (nbr_players_ingame == 1){ // Si il ne reste qu'un joueur en jeu, on sort de la boucle
            for (int i = 0; i < nb_joueurs; i++){
                if (playerstab[i].nb_cartes != 0){
                    cout << "Le joueur " << i+1 << " a gagne la partie" << endl;
                    break;
                }
            }
            play = false;
        }

        //////// Vider la table !!
        play = false;
        nbr_manche++;
    }
}


