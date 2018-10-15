#include "joueur.h"

#include <stdio.h>

// Initialisations variables d'instance
unsigned char Joueur::prochain_num_libre = 0 ;

// Comstructeur(s)
Joueur::Joueur() {
  numero = prochain_num_libre ;
  prochain_num_libre += 1 ;
}

//Méthodes
void Joueur::aff() {
  printf("Je suis le numéro %u, je dispose des infos suivantes :\n", numero) ;
  printf("positions :") ;
  for (int i=0 ; i<NB_MAX_JOUEURS ; i++){
    printf(" %d", positions.at(i)) ;
  }
  printf("\nderniere_position_connue :") ;
  for (int i=0 ; i<NB_MAX_JOUEURS ; i++){
    printf(" %d", derniere_position_connue.at(i)) ;
  }
  printf("\nderniere_maj :") ;
  for (int i=0 ; i<NB_MAX_JOUEURS ; i++){
    printf(" %d", derniere_maj.at(i)) ;
  }
  printf("\ndep_depuis_maj :") ;
  for (int i=0 ; i<NB_MAX_JOUEURS ; i++){
    printf(" %d", dep_depuis_maj.at(i)) ;
  }
  printf("\n") ;
}

int Joueur::get_position() {
  return positions[numero] ;
}

unsigned char Joueur::get_numero() {
  return numero ;
}

void Joueur::recevoir_maj(unsigned char expediteur, int nouv_position) {
  // TODO : on ne fait pas de vérification. Chercher un cas pathologique qui pourrait tout faire foirer
  positions[expediteur] = nouv_position ;
  derniere_position_connue[expediteur] = nouv_position ;
  derniere_maj[expediteur] = 0 ;
  dep_depuis_maj[expediteur] = 0 ;
}

std::vector<bool> Joueur::bouger(int dep) {
  int position_precedente = positions[numero] ; // La position que nous avons au moment de la demande de déplacement.
  int ancienne_position ; //La position que nous avions lors de la dernière mise à jour reçue.
  std::vector<bool> maj = std::vector<bool>(NB_MAX_JOUEURS) ; // Le vecteur qui sera retourné par la fonction (indique si mise à jour à envoyer)

  if (dep > D_MAX) {
    dep = D_MAX ;
  } else if (dep < -D_MAX) {
    dep = -D_MAX ;
  }

  for ( int i = 0 ; i < NB_MAX_JOUEURS ; i++) {
    derniere_maj[i]++ ;
  }

  for ( int i = 0 ; i < NB_MAX_JOUEURS ; i++) {
    if (i == numero) {
      // On a affaire à nous même : mettre à jour directement
      positions[i] += dep ;
      derniere_position_connue[i] = positions[i] ;
      derniere_maj[i] = 0 ;
      dep_depuis_maj[i] = 0 ;
      maj[i] = false ;
    } else {
      // Calcul des variables dont nous nous sommes servi sur papier
      ancienne_position = position_precedente - dep_depuis_maj[i] ;
      int d_0 = abs(derniere_position_connue[i] - ancienne_position) ; // TODO : voir -> enlever abs() et tester si <0 : si c'est le cas (dépassement), tjrs mettre à jour.
      int dep_sum ; // Prendra le déplacement total depuis la dernière mise à jour, en relatif par rapport à la position de l'autre (<0 si réduit la distance, >0 si on s'éloigne)
      if (ancienne_position < derniere_position_connue[i]) {
	// si la condition est vraie, alors un dep > 0 réduit d_0
	dep_sum = - (dep_depuis_maj[i] + dep) ;
      } else if (derniere_position_connue[i] < ancienne_position) {
	dep_sum = dep_depuis_maj[i] + dep ;
      } else { // égalité
	dep_sum = abs(dep_depuis_maj[i] + dep) ;
      }

      // Départ du test de mise à jour à proprement parler
      //if ( d_0 // Je voulais tester si d_0 < 0 (mais n'a pas de sens avec la valeur abolue dans la définition).
      if ( derniere_maj[i] * D_MAX > (d_0 + dep_sum)*TOLERANCE) {
	printf("Je suis %d, et il va falloir que je mette à jour %d\n", numero, i) ;
	maj[i] = true ;
      } else {
	maj[i] = false ;
      }
      //positions[i] = //Pour l'instant, on ne bouge pas l'autre (x = 0)
      dep_depuis_maj[i] += dep ;
    }
  }
  
  //newposition = positions[numero] + bouger ;
  return maj ;
}
