#ifndef joueur_h
#define joueur_h

#include <vector>
#include <cmath>
#include <limits.h>

#define D_MAX 2
#define TOLERANCE 0.2

class Joueur{
  static unsigned char m_prochain_num_libre ; // Utilisé à l'initialisation pour donner un numero
    
  unsigned char m_numero ; // Numéro du joueur
  unsigned char m_nb_joueurs ;

  std::vector<int> positions ; // Positions supposées des autres joueurs
  std::vector<int> derniere_position_connue ;
  std::vector<int> derniere_maj ; // Nombre de tours depuis la dernière mise à jour
  std::vector<int> dep_depuis_maj ; // Déplacement que ce joueur a fait depuis le dernier envoi de maj

 public:
  Joueur() ;
  void set_nb_joueurs(unsigned char nb_joueurs) ;
  void reset() ;
  void aff() ;
  int get_position() ;
  unsigned char get_numero() ;

  /*   Fait passer un tour, exécute les mises à jour locales, et teste à qui il faut
 * envoyer des mises à jour.
 *   Renvoie un tableau contenant la liste des joueurs à qui on veut envoyer une mise à
 * jour. C'est donc le main qui va boucler dessus, récupérer la position du joueur (avec get_position), et demander la mise à jour de l'autre joueur dont il est question. Il faudra améliorer ça...
 */
  void recevoir_maj(unsigned char expediteur, int nouv_position) ;
  std::vector<bool> bouger(int dep, bool verbose=true) ;
};

#endif
