#ifndef joueur_h
#define joueur_h

#include <vector>
#include <cmath>

#define NB_MAX_JOUEURS 2
//TODO : pour l'instant, traité comme le nombre de joueurs et pas le nombre max
#define D_MAX 2
#define TOLERANCE 0.5

class Joueur{
  static unsigned char prochain_num_libre ; // Utilisé à l'initialisation pour donner un numero
    
  unsigned char numero ; // Numéro du joueur
  std::vector<int> positions = std::vector<int>(NB_MAX_JOUEURS) ; // Positions supposées des autres joueurs
  std::vector<int> derniere_position_connue = std::vector<int>(NB_MAX_JOUEURS) ;
  std::vector<int> derniere_maj = std::vector<int>(NB_MAX_JOUEURS) ; // Nombre de tours depuis la dernière mise à jour
  std::vector<int> dep_depuis_maj = std::vector<int>(NB_MAX_JOUEURS) ; // Déplacement que ce joueur a fait depuis le dernier envoi de maj

 public:
  Joueur() ;
  void aff() ;
  int get_position() ;
  unsigned char get_numero() ;

  /*   Fait passer un tour, exécute les mises à jour locales, et teste à qui il faut
 * envoyer des mises à jour.
 *   Renvoie un tableau contenant la liste des joueurs à qui on veut envoyer une mise à
 * jour. C'est donc le main qui va boucler dessus, récupérer la position du joueur (avec get_position), et demander la mise à jour de l'autre joueur dont il est question. Il faudra améliorer ça...
 */
  void recevoir_maj(unsigned char expediteur, int nouv_position) ;
  std::vector<bool> bouger(int dep) ;
};

#endif
