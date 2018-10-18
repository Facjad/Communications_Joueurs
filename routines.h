#ifndef ROUTINES_H
#define ROUTINES_H

#include "joueur.h"

#define MIN_AFF -20
#define MAX_AFF 20

void afficher_pos(std::vector<Joueur> joueurs) ;
void mettre_a_jour(std::vector<bool> resultat, std::vector<Joueur> &joueurs, unsigned char demandeur) ;
void compter_messages(unsigned int &nb, std::vector<bool> tab) ;
void lancer_un_tour(std::vector<Joueur> &joueurs,
		    std::vector<int> directions,
		    unsigned int &nb_messages,
		    bool bouger = true,
		    bool verbose = true) ;

#endif
