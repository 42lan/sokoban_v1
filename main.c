#include "sokoban.h"

int main(int argc, char ** argv){

	Grille initiale = {
		"########################",
		"#.........#......#.....#",
		"##.....O###............#",
		"###.............O#.....#",
		"####.............#O....#",
		"##################.....#",
		"####.............#.....#",
		"###...............O..###",
		"##...........#########o#",
		"#....................oo#",
		"#S....................o#",
		"########################"
	};

	Boolean encore;
	Grille jeu;
	Position position_sokoban;
	
	int coups=0;
	char instruction[MAXCH+1];
	encore=true;

	nouveauJeu(initiale, jeu);
	position_sokoban=getSokoban(jeu);
	
	/* printf("Nombre de fois qu'apparait le caractère: %d\n", compte(jeu, 'o')); */
	
	if((position_sokoban.x==0) && (position_sokoban.y==0))
		error(0);
	else
		printf("La position du Sokoban est en (%d;%d)\n", position_sokoban.x, position_sokoban.y);

	verif(jeu);	/* if(verif(jeu)==false) error(1); */
	
	ajaxVitre;
	do{		
		int i;
		afficheGrille(jeu);
		printf("> ");
		if(fgets(instruction, MAXCH, stdin)==NULL );
		for(i=0; instruction[i]!='\n'; i++){
			ajaxVitre;
			position_sokoban=getSokoban(jeu);
			switch(instruction[i]){
				case HAUT: 		joue(jeu, instruction[i], position_sokoban, initiale); break;
				case BAS: 		joue(jeu, instruction[i], position_sokoban, initiale); break;
				case GAUCHE: 	joue(jeu, instruction[i], position_sokoban, initiale); break;
				case DROITE: 	joue(jeu, instruction[i], position_sokoban, initiale); break;
				case AIDE:		aide(); break;
				case QUITTER: 	encore=false; break;
				default: printf("Instruction inconnu\n"); break;
			}
			coups++;
		}
		if(gagne(jeu, getSokoban(jeu), initiale)==true)
			printf("Félicitations! Tu as gagné en %d coups\n", coups);
	} while(encore==true);
	
	return 0;
}
