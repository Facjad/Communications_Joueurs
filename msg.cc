#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "joueur.h"

#define MIN_AFF -20
#define MAX_AFF 20

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

void mettre_a_jour(std::vector<bool> resultat, std::vector<Joueur> &joueurs, unsigned char demandeur){
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
		    bool bouger = true,
		    bool afficher = true) {
  if (bouger) {
    std::vector<std::vector<bool>> resultats = std::vector<std::vector<bool>>(joueurs.size()) ;
    for (unsigned i=0 ; i<joueurs.size() ; i++){
      resultats[i] = joueurs.at(i).bouger(directions.at(i)) ;
    }
    for (unsigned i=0 ; i<joueurs.size() ; i++){
      mettre_a_jour(resultats.at(i), joueurs, joueurs.at(i).get_numero()) ;
      compter_messages(nb_messages, resultats.at(i)) ;
    }
  }
  if (afficher) {
    for (unsigned i=0 ; i<joueurs.size() ; i++){
      joueurs.at(i).aff() ;
    }
    afficher_pos(joueurs) ;

    printf("###################################\n") ;
  }
}

int main(int argc, char* argv[]) {
  //*** Test du nombre d'arguments
  if (argc != 3) {
    printf("Ce programme prend des arguments en entrée :\n") ;
    printf("1) Le nombre de joueurs pour la simulation\n") ;
    printf("2) Le nombre de tours à exécuter\n") ;
    exit(1) ;
  }

  //*** Déclarations et initialisations

  unsigned char nb_joueurs = atoi(argv[1]) ;
  unsigned int nb_tours = atoi(argv[2]) ;
  
  std::vector<Joueur> joueurs = std::vector<Joueur>(nb_joueurs) ; //vecteur de tous les joueurs
  std::vector<int> directions = std::vector<int>(nb_joueurs) ; //vecteur contenant la vitesse de chaque joueur.

  unsigned int nb_messages = 0 ; //Compteur pour savoir combien de messages auront été échangés

  // Initialiser joueurs
  for ( unsigned i=0 ; i<nb_joueurs ; i++ ) {
    joueurs.at(i).set_nb_joueurs(nb_joueurs) ;
  }

  // Initialiser directions 
  directions[0] = 2 ;
  directions[1] = -1 ;
  srand((unsigned)time(0));
  for (unsigned i=2 ; i<directions.size() ; i++) {
    directions[i] = - D_MAX + rand() % (2*D_MAX + 1) ;
  }

  //*** Départ du "véritable" traitement

  lancer_un_tour(joueurs, directions, nb_messages, false, false) ;

  for (unsigned int i=0 ; i<nb_tours ; i++) {
    lancer_un_tour(joueurs, directions, nb_messages, true, false ) ;
  }

  printf("\n") ;
  printf("***************************************************\n") ;
  printf("******* On a échangé %u messages en tout *******\n", nb_messages) ;
  printf("***************************************************\n") ;
    
  return(0) ;
}
