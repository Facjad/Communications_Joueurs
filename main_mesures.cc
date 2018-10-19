#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "routines.h"

#define NB_ESSAIS 1000

int main(int argc, char* argv[]) {
  //*** Test du nombre d'arguments
  if (argc != 3) {
    printf("Ce programme prend des arguments en entrée :\n") ;
    printf("1) Le nombre de joueurs pour la simulation\n") ;
    printf("2) Le nombre de tours à exécuter\n") ;
    exit(1) ;
  }

  //*** Déclarations et initialisations

  unsigned int nb_joueurs = atoi(argv[1]) ;
  unsigned int nb_tours = atoi(argv[2]) ;
  
  std::vector<Joueur> joueurs = std::vector<Joueur>(nb_joueurs) ; //vecteur de tous les joueurs
  std::vector<int> directions = std::vector<int>(nb_joueurs) ; //vecteur contenant la vitesse de chaque joueur.

  unsigned int nb_messages = 0 ; //Compteur pour savoir combien de messages auront été échangés
  float moyenne_messages = 0.0 ;
  
  // Initialiser joueurs
  for ( unsigned i=0 ; i<nb_joueurs ; i++ ) {
    joueurs.at(i).set_nb_joueurs(nb_joueurs) ;
  }

  // Initialiser directions 
  srand((unsigned)time(0));
  for (unsigned i=0 ; i<directions.size() ; i++) {
    directions[i] = - D_MAX + rand() % (2*D_MAX + 1) ;
  }

  //*** Départ du "véritable" traitement

  //lancer_un_tour(joueurs, directions, nb_messages, false, false) ;

  for (unsigned essai=0 ; essai<NB_ESSAIS ; essai++) {
    // Réinitialisation
    nb_messages = 0 ;
    for (unsigned j=0 ; j<joueurs.size() ; j++) {
      joueurs.at(j).reset() ;
    }
    for (unsigned d=0 ; d<directions.size() ; d++) {
      directions[d] = - D_MAX + rand() % (2*D_MAX + 1) ;
    }

    // Lancer la boucle
    for (unsigned i=0 ; i<nb_tours ; i++) {
      lancer_un_tour(joueurs, directions, nb_messages, true, false) ;
      //      printf("     %u", nb_messages) ;
    }
    
    //printf("\n") ;
    // printf("***************************************************\n") ;
    // printf("******* On a échangé %u messages en tout *******\n", nb_messages) ;
    // printf("***************************************************\n") ;
  
    moyenne_messages = moyenne_messages + (nb_messages - moyenne_messages) / (essai+1) ;
  }

  printf("moyenne = %f\n", moyenne_messages) ;

    
  return(0) ;
}
