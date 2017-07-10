#ifndef __SOKO__
#define __SOKO__

/* Aliace ajaxVitre avec commande UNIX pour effacer l'écran du terminal */
#ifndef __UNIX__
	#define ajaxVitre system("clear");
#endif

#include <stdio.h>
#include <stdlib.h>

#define LARGEUR 24	/* AXE des Y */
#define HAUTEUR 12	/* AXE des X */
#define MAXCH 40

/* Définition des termes qui ont des valeurs correspondant aux entiers */
typedef enum {false=0, true}Boolean;
typedef enum {MUR='#', CAISSE='O', CIBLE='o', SOKOBAN='S', VIDE='.'}Symbole;
typedef enum {HAUT='h', BAS='b', GAUCHE='g', DROITE='d', AIDE='a', QUITTER='q'}Commande;
typedef enum {NO_SOKOBAN=0, G_INCORECT, UNE_CAISSE, DIF_CAICIB}CodeErreur;

typedef char Ligne[LARGEUR+1];
typedef Ligne Grille[HAUTEUR];
typedef struct{
    int x, y;
} Position;

/* Définition des fonctions */
void aide();
void error(CodeErreur code);
void afficheGrille(Grille g);
void nouveauJeu(Grille init, Grille g);
void deplace(Grille jeu, Position pos_a, Position pos_b, Grille init);
int compte(Grille g, char c);
Position getSokoban(Grille g);
Position pas(Position pos_depart, Commande instruction);
Position joue(Grille jeu, Commande dir, Position depart, Grille init);
Boolean verif(Grille g);
Boolean possible(Grille g, Position pos);
Boolean gagne(Grille jeu, Position soko, Grille init);

#endif
