#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "routines.h"

int main(int argc, char* argv[]) {
  /* ATENTION !!
   * Ce main est super sale !! (mais le but n'est pas de faire un truc propre)
   * Pour réaliser cette expérience, il faut le lancer une fois avec une valeur de D_MAX à 500 et une autre fois à 2. Le but est de voir si, avec une distribution uniforme, le fait d'avoir des joueurs aux mêmes vitesses joue un rôle si grand que ça.
  */
  //*** Test du nombre d'arguments
  if (argc != 2) {
    printf("Ce programme prend un seul argument en entrée :\n") ;
    printf("1) Le nombre de tours à exécuter\n") ;
    exit(1) ;
  }

  //*** Déclarations et initialisations

  unsigned int nb_joueurs = 1001 ;
  unsigned int nb_tours = atoi(argv[1]) ;
  
  std::vector<Joueur> joueurs = std::vector<Joueur>(nb_joueurs) ; //vecteur de tous les joueurs
  std::vector<int> directions = std::vector<int>(nb_joueurs) ; //vecteur contenant la vitesse de chaque joueur.

  unsigned int nb_messages = 0 ; //Compteur pour savoir combien de messages auront été échangés
  //float moyenne_messages = 0.0 ;

  // Initialiser joueurs
  for ( unsigned i=0 ; i<nb_joueurs ; i++ ) {
    joueurs.at(i).set_nb_joueurs(nb_joueurs) ;
  }

  // Initialiser directions 
  for (unsigned i=0 ; i<directions.size() ; i++) {
    directions[i] = - D_MAX + i % (2*D_MAX + 1) ;
    printf("%d\n", directions.at(i)) ;
  }

  //*** Départ du "véritable" traitement

  for (unsigned i=0 ; i<nb_tours ; i++) {
    lancer_un_tour(joueurs, directions, nb_messages, true, false) ;
    //      printf("     %u", nb_messages) ;
  }
  
  printf("\n") ;
  printf("***************************************************\n") ;
  printf("******* On a échangé %u messages en tout *******\n", nb_messages) ;
  printf("***************************************************\n") ;
  
  return(0) ;
}
