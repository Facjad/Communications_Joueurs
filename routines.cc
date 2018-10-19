#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "routines.h"

void afficher_pos(std::vector<Joueur> joueurs) {
  static unsigned char tour = 0 ;
  unsigned int taille = MAX_AFF - MIN_AFF + 1 ;

  std::vector<char> ligne = std::vector<char>(taille, '-') ;
  int pos ;

  printf("Tour %d\nPositions réelles :", tour) ;
  // Mettre un 'J' là où il y a un joueur
  for (unsigned i=0 ; i<joueurs.size() ; i++){
    pos = joueurs.at(i).get_position() ;
    printf(" %d", pos) ;
    if (pos > MIN_AFF && pos < MAX_AFF) {
      ligne[pos-MIN_AFF] = 'J' ;
    }
  }
  printf("\n") ;

  for (unsigned ici=0 ; ici<ligne.size() ; ici++){
    printf("%c", ligne.at(ici)) ;
  }
  printf("\n") ;
  tour += 1 ;
}

void mettre_a_jour(std::vector<bool> resultat, std::vector<Joueur> &joueurs, unsigned int demandeur){
  for (unsigned i=0 ; i<resultat.size() ; i++){
    if (resultat.at(i)) {
      joueurs.at(demandeur).recevoir_maj(i, joueurs.at(i).get_position()) ;
    }
  }
}

//Compte le nombre de true dans tab, et ajoute cette valeur à nb
void compter_messages(unsigned int &nb, std::vector<bool> tab) {
  for (unsigned i=0 ; i<tab.size() ; i++) {
    if (tab.at(i)) {
      // Mettre à jour sauf si overflow
      if (nb != INT_MAX) {
	nb ++ ;
	//if (nb%1000000 == 0) printf("                           %d\n", nb) ;
      } else {
	printf("Erreur : il y a eu un overflow dans le comptage des messages échangés. Arrêt du programme.\n") ;
	exit(2) ;
      }
    }
  }
}

void lancer_un_tour(std::vector<Joueur> &joueurs,
		    std::vector<int> directions,
		    unsigned int &nb_messages,
		    bool bouger,
		    bool verbose) {
  if (bouger) {
    std::vector< std::vector<bool> > demandes_maj = std::vector< std::vector<bool> >(joueurs.size()) ;
    // Faire bouger tous les joueurs
    for (unsigned i=0 ; i<joueurs.size() ; i++){
      demandes_maj[i] = joueurs.at(i).bouger(directions.at(i), verbose) ;
    }
    // Une fois qu'ils ont tous bougés, faire les mises à jour
    for (unsigned i=0 ; i<joueurs.size() ; i++){
      mettre_a_jour(demandes_maj.at(i), joueurs, joueurs.at(i).get_numero()) ;
      compter_messages(nb_messages, demandes_maj.at(i)) ;
    }
  }
  if (verbose) {
    // Si verbose, alors afficher les infos de chaque joueur
    for (unsigned i=0 ; i<joueurs.size() ; i++){
      joueurs.at(i).aff() ;
    }
    afficher_pos(joueurs) ;

    printf("###################################\n") ;
  }
}
