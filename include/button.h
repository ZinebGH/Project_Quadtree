#ifndef __BUTTON__ 
#define __BUTTON__

#define X_BOUTON1 10
#define Y_BOUTON1 560

#include "quadtree.h"

/**Dessine à partir de la bibliothèque MLV les boutons indiqués.*/
void drawSaveButtons();

/**Dans cette fonction on renvoie le numero de chaque bouton de coordonne (x, y)*/
int choiceSaveButton(int x, int y);
#endif