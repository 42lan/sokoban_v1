# sokoban_v1
Projet 2017: Sokoban v1.0

E3FR2 aslan.malsagov[at]edu.esiee.fr

Dans ce jeu, le sokoban doit ranger des caisses à leur place en poussant une à la fois.



1.1. Affiche la grille passée en paramètre.




2.1 Retourne la position du Sokoban dans la grille, ou {0,0} s'il n'est pas trouvé.

2.2 Affiche les messages d'erreur en fonction de l'entier passé en paramètre puis, termine le programme en retournant ce code d'erreur.



3.1 Recopie la grille initiale dans une nouvelle grille de jeu.




4.1 Vérifie si chaque ligne de la grille est une chaîne de caractères.

4.2 Vérifie s'il y a au moins une caisse et qu'il y a autant de caisses que de cibles.




5.1 Compte dans la grille le nombre de fois qu'apparaît le caractère passé en paramètre.



6.1 Afficher la légende des différents symboles et les commandes disponibles.




7.1 Fait un pas dans la direction indiquée par la commande.

7.2 Vérifie que la position suivante est une destination possible.

7.3 Remplace, dans la grille de jeu, le symbole à la position de destination par le symbole de la position de départ. Puis, remplace le symbole à la position de départ par le vide ou cible.

7.4 Calcule la future position du joueur et verifie que cette position est une destination possible. Si oui, deplace le joueur. Sinon, si c'est un mur, affiche un message appropprié. Ou si, c'est une caisse deplace la caisse et le sokoban.



8.1 Detecte que le joueur a gagné et qu'il n'a plus de Cible dans la grille et que Sokoban n'occupe pas la position d'une Cible dans la grille initiale.

BUGS:

1. Lors de la compilation deux "warning" s'affichent en signalant que les enumerations AIDE et QUITTER ne sont pas traité dans la condtion switch de la fonction pas(). Afin de rectifier ce avertissement, j'ai ajouté l'instruction default pour que les enumerations AIDE et QUITTER soient traité par elle en terminant le switch.

2. Si l'utilisateur depasse la longueur maximale des commandes de tableau MAXCH, le terminal affiche le promt directement suivi de la premiere ligne de la grille, ce qui la decale. Ce problème peut prevenir de fait que le caractere d'entrée - '\n', sort des limites. La rectification n'est pas encore mise en place.

3. Si l'utilisateur appuie sur Entrée sans avoir saisi la commande, la grille precedente ne s'efface pas. Ce probleme n'était pas encore traité.
