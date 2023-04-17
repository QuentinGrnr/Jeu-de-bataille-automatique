#include "jeu_cartes.h"
#include "carte.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
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
    if (this->nb_cartes == 0){
        cout << "Le jeu de cartes est vide" << endl << endl;
        return;
    }
    for (int i = 0; i < this->nb_cartes; i++){
        switch (tmp->valeur) {
            case 11:
                cout << "Valet";
                break;
            case 12:
                cout << "Dame";
                break;
            case 13:
                cout << "Roi";
                break;
            case 14:
                cout << "As";
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
    cout << nb_cartes   << endl;
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
    if (this->head == nullptr && this->tail != nullptr){
        this->head = this->tail;
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

void jeu_cartes::melangerjeu(int nb_melanges) {
    jeu_cartes jeu_vide;
    carte *tmp;
    for (int i = 0; i < nb_melanges; i++){ // Melange n fois en utilisant la methode tail/head alternée
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
    cout << "Le jeu de cartes a ete melange " << nb_melanges<< " fois" << endl << endl;
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
    if (nb_joueurs >10){
        cout << "ce programme ne supporte qu'une dizaine de joueur maximum" << endl << endl;
        return;
    }
    srand (time(NULL));// on ajoute l'aléatoire
    this->remplirjeu();

    // j'ai pu constater que certains nombre de mélange causaient des batailles infinie qui empéchait le jeu de se terminer, ce qui, dans le vrais jeu a une probalitée infime de se produire
    // le cas de bataille infini étant presque impossible a fix avec seulement deux classes (jeu de carte et carte) j'ai décidé de faire un nombre de mélange aléatoire entre 0 et 200 dans un premier temps
    //Puis de mélanger chaque jeux de chaques joueurs entre 0 et 200 fois aussi. Ce qui fait diparaitre ce cas rarissime.
    this->melangerjeu(rand() % 201);
    jeu_cartes *playerstab = this->distribuer(nb_joueurs);
    cout << "Voici les cartes de chaque joueur : " << endl << endl;
    for (int i = 0; i < nb_joueurs; i++){
        cout << "Joueur " << i+1 << " : " << endl;
        playerstab[i].melangerjeu(rand() % 201);
        playerstab[i].afficherjeu();
    }
    cout << "La partie va commencer !" << endl << endl;
    bool play = true;
    carte table[nb_joueurs];// Tableau qui contient les cartes jouées par les joueurs
    jeu_cartes jeu_cartes_gagne; // Jeu de cartes qui contient les cartes que les joueurs peuvent gagner en cas de bataille
    int nbr_players_ingame = 0; // Nombre de joueurs en jeu qui permet de savoir quand la partie est finie (si ==1)
    int nbr_manche = 0; // Nombre de manches jouées
    while (play){
        nbr_manche++;

        for (int i = 0; i < nb_joueurs; i++){
            if (playerstab[i].nb_cartes != 0){
                table[i] = *playerstab[i].head;
                playerstab[i].head = playerstab[i].head->suivant;
                playerstab[i].nb_cartes--;
            } else {
                table[i] = carte(-1, -1); // Si le joueur n'a plus de cartes, on met une carte vide dans le tableau
            }
        }

        // on determine le/les gagnant de la manche
        cout << "Voici les cartes jouees par les joueurs pour la manche " << nbr_manche << endl;
        int nbr_gagnant = 0; // Nombre de joueurs gagnant la manche
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
                        nbr_gagnant++;
                    } else {
                        jeu_cartes_gagne.addtail(&table[i]); // Si le joueur n'a pas gagné la manche, on ajoute sa carte dans le jeu de cartes a gagner en fin de manche
                        table[i] = carte(-1, -1); // On met une carte vide dans le tableau pour elever le joueur de la manche
                    }
                } else {
                    cout << "Joueur " << i+1 << " ne joue plus" << endl;
                }
        }

        if (nbr_gagnant == 1){
            for (int i = 0; i < nb_joueurs; i++){
                if (table[i].gagnant){
                    cout << endl << "Le joueur " << i+1 << " a gagne la manche" << endl;
                    playerstab[i].addtail(&table[i]); // On ajoute la carte du joueur qui a gagné la manche dans son jeu de cartes
                    while (jeu_cartes_gagne.nb_cartes != 0){
                        playerstab[i].addtail(jeu_cartes_gagne.head);
                        cout << "Le joueur " << i+1 << " a gagne la carte " << jeu_cartes_gagne.head->valeur << endl;
                        jeu_cartes_gagne.head = jeu_cartes_gagne.head->suivant;
                        jeu_cartes_gagne.nb_cartes--;
                    }
                }
            }
        } else {
            cout << "Il y a une bataille !" << endl;
            while (nbr_gagnant != 1) {
                for (int i = 0; i < nb_joueurs; i++) {
                    if (table[i].gagnant && table[i].valeur != -1) {
                        if (playerstab[i].nb_cartes >= 2) {
                                jeu_cartes_gagne.addtail(
                                        &table[i]); // On ajoute les cartes des joueurs qui ont gagné la manche dans le jeu de cartes a gagner en fin de manche
                                jeu_cartes_gagne.addtail(
                                        playerstab[i].head); // on ajoute la carte mise face caché par le joueur dans le jeu de cartes a gagner en fin de manche
                                cout << "Joueur " << i + 1 << " pose la carte " << playerstab[i].head->valeur
                                     << " face cache" << endl;
                                playerstab[i].head = playerstab[i].head->suivant; // On enleve la carte mise face caché par le joueur de son jeu de cartes
                                playerstab[i].nb_cartes--;
                                table[i] = *playerstab[i].head; // On ajoute la carte mise face visible par le joueur sur la table
                                playerstab[i].head = playerstab[i].head->suivant; // On enleve la carte mise face visible par le joueur
                                playerstab[i].nb_cartes--;
                                cout << "et la carte " << table[i].valeur << " face visible" << endl;
                        } else {
                            cout << "Le joueur " << i + 1 << " n'a plus assez de cartes pour jouer la bataille" << endl;
                            jeu_cartes_gagne.addtail(
                                    &table[i]); // On ajoute la carte des joueurs qui n'ont pas assez de cartes pour jouer la bataille dans le jeu de cartes a gagner en fin de manche
                            table[i] = carte(-1,
                                             -1); // On met une carte vide dans le tableau pour elever le joueur de la manche
                        }
                    }
                }
                nbr_gagnant = 0;
                for (int i = 0; i < nb_joueurs; i++) {
                    table[i].gagnant = false;
                    if (table[i].valeur != -1) {
                        bool winround = true;
                        for (int j = 0; j < nb_joueurs; j++) {
                            if (table[i].valeur < table[j].valeur) {
                                winround = false;
                            }
                        }
                        if (winround) {
                            table[i].gagnant = true;
                            nbr_gagnant++;
                        } else {
                            jeu_cartes_gagne.addtail(
                                    &table[i]); // Si le joueur n'a pas gagné la manche, on ajoute sa carte dans le jeu de cartes a gagner en fin de manche
                            table[i] = carte(-1,
                                             -1); // On met une carte vide dans le tableau pour elever le joueur de la manche
                        }
                    }
                }
            }
            for (int i = 0; i < nb_joueurs; i++){
                if (table[i].gagnant){
                    cout << "Le joueur " << i+1 << " a gagne la bataille" << endl;
                    jeu_cartes_gagne.addtail(&table[i]);
                    while (jeu_cartes_gagne.nb_cartes != 0){
                        cout << "Le joueur " << i+1 << " a gagne la carte " << jeu_cartes_gagne.head->valeur << endl;
                        playerstab[i].addtail(jeu_cartes_gagne.head);
                        jeu_cartes_gagne.head = jeu_cartes_gagne.head->suivant;
                        jeu_cartes_gagne.nb_cartes--;
                    }
                }
            }
        }

        for (int i = 0; i < nb_joueurs; i++){
            table[i] = carte(-1, -1);// on vide la table
        }

        // On compte le nombre de joueurs encore en jeu
        nbr_players_ingame = 0;
        for (int i = 0; i < nb_joueurs; i++){
            if (playerstab[i].nb_cartes != 0){
                nbr_players_ingame++;
            }
        }

        cout << endl;
        for (int i = 0; i < nb_joueurs; i++){
            cout << "Joueur " << i+1 << " : " << endl;
            playerstab[i].afficherjeu();
        }

        for (int i = 0; i < nb_joueurs; i++){
            cout << "Joueur " << i+1 << " : " << endl;
            playerstab[i].afficherjeu();
        }

        if (nbr_players_ingame == 1){
            for (int i = 0; i < nb_joueurs; i++){
                if (playerstab[i].nb_cartes != 0){
                    cout << "Le joueur " << i+1 << " a gagne la partie" << endl;
                    cout << "Voici son jeu de carte trie : " << endl;
                    playerstab[i].trierjeu();
                    playerstab[i].afficherjeu();
                    play = false;
                }
            }
        }

        jeu_cartes_gagne.viderjeu();
    }
    // gerer cas cartes toutes pareilles => bataille infinie => égalités
    // gérer 17 bizzare
}

void jeu_cartes::trierjeu() {
    bool swapped = true;
    int j = 0;
    carte *ptr1;
    carte *lptr = nullptr;

    if (head == nullptr) {
        return;
    }

    while (swapped) {
        swapped = false;
        ptr1 = head;

        while (ptr1->suivant != lptr) {
            if ((ptr1->forme > ptr1->suivant->forme) ||
                (ptr1->forme == ptr1->suivant->forme && ptr1->valeur > ptr1->suivant->valeur)) {
                swap(ptr1, ptr1->suivant);
                swapped = true;
            }
            ptr1 = ptr1->suivant;
        }
        lptr = ptr1;
    }
}

void jeu_cartes::swap(carte *a, carte *b) {
    int temp_forme = a->forme;
    int temp_valeur = a->valeur;
    bool temp_gagnant = a->gagnant;
    a->forme = b->forme;
    a->valeur = b->valeur;
    a->gagnant = b->gagnant;
    b->forme = temp_forme;
    b->valeur = temp_valeur;
    b->gagnant = temp_gagnant;
}