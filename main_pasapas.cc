#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <iostream>
#include <fstream>

#include "routines.h"

#define nb_joueurs 2

int main(int argc, char* argv[]) {
  //*** Test du nombre d'arguments
  if (argc != 2) {
    printf("Ce programme prend des arguments en entrée :\n") ;
    printf("1) Le nombre de tours à exécuter\n") ;
    exit(1) ;
  }

  //*** Déclarations et initialisations
  unsigned int nb_messages = 0 ;
  unsigned int nb_tours = atoi(argv[1]) ;
  
  std::vector<Joueur> joueurs = std::vector<Joueur>(nb_joueurs) ; //vecteur de tous les joueurs
  std::vector<int> directions = std::vector<int>(nb_joueurs) ; //vecteur contenant la vitesse de chaque joueur.
  std::ofstream fichier_sortie ;

  // Initialiser joueurs
  for ( unsigned i=0 ; i<nb_joueurs ; i++ ) {
    joueurs.at(i).set_nb_joueurs(nb_joueurs) ;
  }

  // Initialiser directions
  directions[0] = 0 ;
  directions[1] = 1 ;
  
  //*** Départ du "véritable" traitement

  fichier_sortie.open("nb_messages.txt") ;
  if (! fichier_sortie.is_open()) {
    printf("échec de l'ouverture du fichier\n") ;
  }
  lancer_un_tour(joueurs, directions, nb_messages, false, true) ;
  
  for (unsigned i=0 ; i<nb_tours ; i++) {
    fichier_sortie << nb_messages << "\n";
    lancer_un_tour(joueurs, directions, nb_messages, true, true) ;
    //      printf("     %u", nb_messages) ;
  }
  if (fichier_sortie.is_open()) {
    fichier_sortie.close();
  }
  
  return(0) ;
}
