#include "joueur.h"

#include <stdio.h>

// Initialisations variables d'instance
unsigned char Joueur::m_prochain_num_libre = 0 ;

// Constructeur(s)
Joueur::Joueur() {
  m_numero = m_prochain_num_libre ;
  m_prochain_num_libre += 1 ;

  positions = std::vector<int>(0) ;
  derniere_position_connue = std::vector<int>(0) ;
  derniere_maj = std::vector<int>(0) ;
  dep_depuis_maj = std::vector<int>(0) ;
}

void Joueur::set_nb_joueurs(unsigned char nb_joueurs) {
  m_nb_joueurs = nb_joueurs ;
  
  positions.resize(nb_joueurs) ;
  derniere_position_connue.resize(nb_joueurs) ;
  derniere_maj.resize(nb_joueurs) ;
  dep_depuis_maj.resize(nb_joueurs) ;
}

void Joueur::reset() {
  for (unsigned char i=0 ; i<m_nb_joueurs ; i++){
    positions[i] = 0 ;
    derniere_position_connue[i] = 0 ;
    derniere_maj[i] = 0 ;
    dep_depuis_maj[i] = 0 ;
  }
}

//Méthodes
void Joueur::aff() {
  printf("Je suis le numéro %u, je dispose des infos suivantes :\n", m_numero) ;
  printf("positions :") ;
  for (unsigned char i=0 ; i<m_nb_joueurs ; i++){
    printf(" %d", positions.at(i)) ;
  }
  printf("\nderniere_position_connue :") ;
  for (unsigned char i=0 ; i<m_nb_joueurs ; i++){
    printf(" %d", derniere_position_connue.at(i)) ;
  }
  printf("\nderniere_maj :") ;
  for (unsigned char i=0 ; i<m_nb_joueurs ; i++){
    printf(" %d", derniere_maj.at(i)) ;
  }
  printf("\ndep_depuis_maj :") ;
  for (unsigned char i=0 ; i<m_nb_joueurs ; i++){
    printf(" %d", dep_depuis_maj.at(i)) ;
  }
  printf("\n") ;
}

int Joueur::get_position() {
  return positions[m_numero] ;
}

unsigned char Joueur::get_numero() {
  return m_numero ;
}

void Joueur::recevoir_maj(unsigned char expediteur, int nouv_position) {
  // TODO : on ne fait pas de vérification. Chercher un cas pathologique qui pourrait tout faire foirer
  positions[expediteur] = nouv_position ;
  derniere_position_connue[expediteur] = nouv_position ;
  derniere_maj[expediteur] = 0 ;
  dep_depuis_maj[expediteur] = 0 ;
}

std::vector<bool> Joueur::bouger(int dep, bool verbose /*=true*/) {
  int position_precedente = positions[m_numero] ; // La position que nous avons au moment de la demande de déplacement.
  int ancienne_position ; //La position que nous avions lors de la dernière mise à jour reçue.
  std::vector<bool> maj = std::vector<bool>(m_nb_joueurs) ; // Le vecteur qui sera retourné par la fonction (indique si mise à jour à envoyer)

  if (dep > D_MAX) {
    dep = D_MAX ;
  } else if (dep < -D_MAX) {
    dep = -D_MAX ;
  }

  for ( int i = 0 ; i < m_nb_joueurs ; i++) {
    derniere_maj[i]++ ;
  }

  for ( int i = 0 ; i < m_nb_joueurs ; i++) {
    if (i == m_numero) {
      // On a affaire à nous même : mettre à jour directement
      if ( ((dep > 0) && (positions[i] > INT_MAX - dep)) || ((dep < 0) && (positions[i] < INT_MIN - dep)) ) {
	printf("Le joueur %u a un overflow sur sa position...", m_numero) ;
	printf("Position avant déplacement : %d", positions.at(i)) ;
	exit(2) ;
      }
      
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
	if (verbose) printf("Je suis %d, et il va falloir que je mette à jour %d\n", m_numero, i) ;
	maj[i] = true ;
      } else {
	maj[i] = false ;
      }
      //positions[i] = //Pour l'instant, on ne bouge pas l'autre (x = 0)
      dep_depuis_maj[i] += dep ;
    }
  }
  
  //newposition = positions[m_numero] + bouger ;
  return maj ;
}
