#include "sokoban.h"

/*** Première itération ***/
/*	Affiche la grille passée en paramètre précédée d'une ligne blanche.
 */
void afficheGrille(Grille g){
	int i, j;
	for(i=0; i<HAUTEUR; i++){
		for(j=0; j<LARGEUR; j++)
			printf("%c", g[i][j]);
		printf("\n");
	}
}



/*** Deuxième itération ***/
/* Retourne la position du sokoban dans la grille passée en paramètre,
 *	ou {0,0} s'il n'est pas trouvé.
 */
Position getSokoban(Grille g){
	int i, j;
	Position position = {0, 0};

	for(i=0; i<HAUTEUR; i++){
		for(j=0; j<LARGEUR; j++){
			if(g[i][j]=='S'){
				position.x = i;
				position.y = j;
			}
		}
	}
	return position;
}



/* Messages d'erreur en fonction de l'entier passé en paramètre puis qui
 *	termine le programme en retournant ce code d'erreur
 */
void error(CodeErreur code){
	switch(code){
		case NO_SOKOBAN : fprintf(stderr,"Pas de Sokoban!\n"); break;
		case G_INCORECT : fprintf(stderr,"Grille initiale incorrecte !\n"); break;
		case UNE_CAISSE : fprintf(stderr,"Au moins une Caisse doit etre presente\n"); break;
		case DIF_CAICIB : fprintf(stderr,"Nombre de Caisses et des Cibles n'est pas egal\n"); break;
		default: fprintf(stderr,"Code erreur inconnu!\n");
	}
	exit(code);
}

/* Ou on peut faire l'etape precedent comme ci-dessus */
/*
const char * strError[] = {
	"passssss de Sokoban!\n",
	"Grille initiale incorrecte !\n",
	"Au moins une caisse doit etre presente\n",
	"Le nombre de caisses et des cibles n'est pas egal\n"
};
void error(CodeErreur code){
	if((code==NO_SOKOBAN)||(code==G_INCORECT)||(code==DIF_CAICIB))
		printf("%s\n", strError[code]);
	else
		printf("code erreur inconnu!\n");
}
*/



/*** Troisième itération ***/
/* Recopie la grille initiale passée en premier paramètre dans
 *	une nouvelle grille de jeu passée en deuxième paramètre
 */
void nouveauJeu(Grille init, Grille g){
	int i, j;
	for(i=0; i<HAUTEUR; i++){
		for(j=0; j<LARGEUR+1; j++){
			g[i][j] = init[i][j];
			if((init[i][j]==CAISSE)||(init[i][j]==SOKOBAN))
				init[i][j]=VIDE;
		}
	}
}



/*** Quatrième itération ***/
Boolean verif(Grille g){
	int i, j, nbCaisses=0, nbCibles=0;

	for(i=0; i<HAUTEUR; i++){
		j=0;
		/* Vérifie si chaque ligne de la grille est une chaîne de caractères */
		while(g[i][j]!='\0')
			j++;
		if(LARGEUR!=j)
			error(1); /*return false;*/
	}


	/* Parcour du table pour compter le nombre de caisses et des cibles
	 *	pour la vérification qui suit
	 */
	for(i=0; i<HAUTEUR; i++){
		for(j=0; j<LARGEUR; j++){
			if(g[i][j]==CAISSE)
				nbCaisses++;
			if(g[i][j]==CIBLE)
				nbCibles++;
		}
	}
	/* Vérifie s'il y a au moins une caisse */
	if(nbCaisses==0)
		error(2);
	/* Vérifie s'il y a autant de caisse que de cibles */
	if(nbCaisses!=nbCibles)
		error(3);
	return true;
}



/*** Cinquième itération ***/
/* Compte dans la grille passée en premier paramètre le nombre de fois
 *	qu'apparaît le caractère passé en second paramètre
 */
int compte(Grille g, char c){
	int i, j, nb_occ=0;

	for(i=0; i<HAUTEUR; i++)
		for(j=0; j<LARGEUR; j++)
			if(g[i][j]==c)
				nb_occ++;
	return nb_occ;
}



/**** Sixième itération ****/
/* Rendre le jeu interactif en permettant de saisir des commandes
 * Afficher la légende des différents symboles et les commandes disponibles
 */
void aide(){
	printf("Aide:\n");
	printf("  (%c)MUR, (%c)CAISSE, (%c)CIBLE, (%c)SOKOBAN, (%c)VIDE\n", MUR, CAISSE, CIBLE, SOKOBAN, VIDE);
	printf("  (%c)ide, (%c)quitter, (%c)aut, (%c)as, (%c)auche, (%c)roite\n", AIDE, QUITTER, HAUT, BAS, GAUCHE, DROITE);
}



/**** Septième itération ****/
/* Fait un pas dans la direction indiquée par la commande passée en
 * second paramètre à partir de la Position passée en premier paramètre.
 */
Position pas(Position pos_depart, Commande cmd){
	Position position_actuelle;
	position_actuelle=pos_depart;

	switch (cmd){
		case HAUT:		position_actuelle.x--; break;
		case BAS:		position_actuelle.x++; break;
		case GAUCHE:	position_actuelle.y--; break;
		case DROITE:	position_actuelle.y++; break;
		default: break;
	}
	return position_actuelle;
}



/* Vérifie que la Position passée en second paramètre est une destination possible
 * dans la grille passée en premier paramètre
 */
Boolean possible(Grille g, Position pos){
	if((g[pos.x][pos.y]==MUR)||(g[pos.x][pos.y]==CAISSE))
		return false;
	return true;
}



/* Remplace, dans la grille de jeu, le symbole à la position de destination par le symbole de la position de départ.
 * Puis, elle remplace le symbole à la position de départ par VIDE ou CIBLE
 */
void deplace(Grille jeu, Position pos_a,Position pos_b, Grille g){
	jeu[pos_b.x][pos_b.y]=jeu[pos_a.x][pos_a.y];
	jeu[pos_a.x][pos_a.y]=g[pos_a.x][pos_a.y];
}


/* Calcule la future position du joueur et verifie que cette position est une destination possible.
 * Si oui, deplace le joueur. Sinon, si c'est un mur, affiche un message appropprié. Ou si, c'est
 * une caisse deplace la caisse et le sokoban.
 */
Position joue(Grille jeu, Commande dir, Position depart, Grille init){
	Position futur_pos;
	futur_pos=pas(depart, dir);
	
	if(possible(jeu, futur_pos)==true)
		deplace(jeu, depart, futur_pos, init);
	else{
		if(jeu[futur_pos.x][futur_pos.y]==MUR)
			printf("Impossible à cause d'un Mur devant\n");
		if(jeu[futur_pos.x][futur_pos.y]==CAISSE){
			if(possible(jeu, pas(futur_pos, dir))==true){
				deplace(jeu, futur_pos, pas(futur_pos, dir), init);
				deplace(jeu, depart, futur_pos, init);
			}
		}
	}
	return futur_pos;
}



/**** Huitième itération ****/
/* Detecte que le joueur a gagné et qu'il n'a plus de Cible dans la grille et
 * que Sokoban n'occupe pas la position d'une Cible dans la grille initiale 
 */
Boolean gagne(Grille jeu, Position soko, Grille init){
	int i, j, nbCibles=0;
	for(i=0; i<HAUTEUR; i++){
		for(j=0; j<LARGEUR; j++){
			if(jeu[i][j]==CIBLE)
				nbCibles++;
		}
	}
	if((nbCibles==0)&&(init[soko.x][soko.y]!=CIBLE))
		return true;
	return false;
}
