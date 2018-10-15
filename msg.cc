#include <stdio.h>
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
    pos = joueurs[i].get_position() ;
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

void mettre_a_jour(std::vector<bool> resultat, std::vector<Joueur> &joueurs, unsigned char expediteur){
  for (unsigned i=0 ; i<resultat.size() ; i++){
    if (resultat.at(i)) {
      joueurs.at(i).recevoir_maj(expediteur, joueurs.at(expediteur).get_position()) ;
    }
  }
}

int main() {
  Joueur j1 ;
  Joueur j2 ;

  std::vector<Joueur> joueurs = std::vector<Joueur>(2) ;
  std::vector<bool> resultat1 = std::vector<bool>(2) ;
  std::vector<bool> resultat2 = std::vector<bool>(2) ;
  joueurs[0] = j1 ;
  joueurs[1] = j2 ;
  //for ( int i=0 ; i<joueurs.size() ; i++ ) {
  //  joueurs[i] = Joueur() ;
  //}

  //j1.aff() ;
  //  printf("et ma position est %d\n", j1.get_position()) ;
  //  j2.aff() ;
  //  printf("et ma position est %d\n", j2.get_position()) ;
  //  j1.bouger(2) ;
  //  j2.bouger(-1) ;

  joueurs[0].aff() ;
  joueurs[1].aff() ;
  afficher_pos(joueurs) ;

  printf("###################################\n") ;
  
  resultat1 = joueurs[0].bouger(2) ;
  resultat2 = joueurs[1].bouger(-1) ;
  mettre_a_jour(resultat1, joueurs, joueurs.at(0).get_numero()) ;
  mettre_a_jour(resultat2, joueurs, joueurs.at(1).get_numero()) ;
  joueurs[0].aff() ;
  joueurs[1].aff() ;
  afficher_pos(joueurs) ;

  printf("###################################\n") ;
  
  resultat1 = joueurs[0].bouger(2) ;
  resultat2 = joueurs[1].bouger(-1) ;
  mettre_a_jour(resultat1, joueurs, joueurs.at(0).get_numero()) ;
  mettre_a_jour(resultat2, joueurs, joueurs.at(1).get_numero()) ;
  joueurs[0].aff() ;
  joueurs[1].aff() ;
  afficher_pos(joueurs) ;

  printf("###################################\n") ;
  
  resultat1 = joueurs[0].bouger(2) ;
  resultat2 = joueurs[1].bouger(-1) ;
  mettre_a_jour(resultat1, joueurs, joueurs.at(0).get_numero()) ;
  mettre_a_jour(resultat2, joueurs, joueurs.at(1).get_numero()) ;
  joueurs[0].aff() ;
  joueurs[1].aff() ;
  afficher_pos(joueurs) ;

  printf("###################################\n") ;
  
  resultat1 = joueurs[0].bouger(2) ;
  resultat2 = joueurs[1].bouger(-1) ;
  mettre_a_jour(resultat1, joueurs, joueurs.at(0).get_numero()) ;
  mettre_a_jour(resultat2, joueurs, joueurs.at(1).get_numero()) ;
  joueurs[0].aff() ;
  joueurs[1].aff() ;
  
  afficher_pos(joueurs) ;

  printf("###################################\n") ;
  
  resultat1 = joueurs[0].bouger(2) ;
  resultat2 = joueurs[1].bouger(-1) ;
  mettre_a_jour(resultat1, joueurs, joueurs.at(0).get_numero()) ;
  mettre_a_jour(resultat2, joueurs, joueurs.at(1).get_numero()) ;
  joueurs[0].aff() ;
  joueurs[1].aff() ;
  
  afficher_pos(joueurs) ;

  printf("###################################\n") ;
  
  resultat1 = joueurs[0].bouger(2) ;
  resultat2 = joueurs[1].bouger(-1) ;
  mettre_a_jour(resultat1, joueurs, joueurs.at(0).get_numero()) ;
  mettre_a_jour(resultat2, joueurs, joueurs.at(1).get_numero()) ;
  joueurs[0].aff() ;
  joueurs[1].aff() ;
  
  afficher_pos(joueurs) ;

  printf("###################################\n") ;
  
  resultat1 = joueurs[0].bouger(2) ;
  resultat2 = joueurs[1].bouger(-1) ;
  mettre_a_jour(resultat1, joueurs, joueurs.at(0).get_numero()) ;
  mettre_a_jour(resultat2, joueurs, joueurs.at(1).get_numero()) ;
  joueurs[0].aff() ;
  joueurs[1].aff() ;
  
  afficher_pos(joueurs) ;

  printf("###################################\n") ;
  
  resultat1 = joueurs[0].bouger(2) ;
  resultat2 = joueurs[1].bouger(-1) ;
  mettre_a_jour(resultat1, joueurs, joueurs.at(0).get_numero()) ;
  mettre_a_jour(resultat2, joueurs, joueurs.at(1).get_numero()) ;
  joueurs[0].aff() ;
  joueurs[1].aff() ;
  
  afficher_pos(joueurs) ;

  printf("###################################\n") ;
  
  resultat1 = joueurs[0].bouger(2) ;
  resultat2 = joueurs[1].bouger(-1) ;
  mettre_a_jour(resultat1, joueurs, joueurs.at(0).get_numero()) ;
  mettre_a_jour(resultat2, joueurs, joueurs.at(1).get_numero()) ;
  joueurs[0].aff() ;
  joueurs[1].aff() ;
  
  afficher_pos(joueurs) ;

  printf("###################################\n") ;
  
  resultat1 = joueurs[0].bouger(2) ;
  resultat2 = joueurs[1].bouger(-1) ;
  mettre_a_jour(resultat1, joueurs, joueurs.at(0).get_numero()) ;
  mettre_a_jour(resultat2, joueurs, joueurs.at(1).get_numero()) ;
  joueurs[0].aff() ;
  joueurs[1].aff() ;
  
  afficher_pos(joueurs) ;
    
  return(0) ;
}
