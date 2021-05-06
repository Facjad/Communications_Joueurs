Un petit programme visant à tester le nombre de messages échangés sue le réseau pour un jeu mutlijoueur distribué. Modèle simpliste pour l'instant, mais destiné à évoluer.

Pour compiler :
     make mesures -> sortie : mesures. Permet de lancer un grand nombre de test (1000 si pas de changement ultérieur) dans lesquels chaque joueur prend chaque fois une nouvelle vitesse au hasard. Affiche le nombre (moyen) de messages échangés pour une expérience.
     make mesures_500 -> sortie : mesures. Fait une seule expérience non aléatoire, en donnant à chaque joueur une vitesse déterministe (le premier a une vitesse de -Vmax, puis (-Vmax + 1), etc. (utilisation d'un modulo).
     make pasapas -> sortie : pasapas. Deux joueurs, un à vitesse nulle, l'autre de vitesse 1. Affiche en mode verbose tout ce qui se passe, et écrit dans le fichier nb_messages.txt pour chaque tour le somme des messages échangés jusque là. (pour tracer une courbe logarithmique).
