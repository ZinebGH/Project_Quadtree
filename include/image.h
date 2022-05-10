#ifndef __IMAGE__ 
#define __IMAGE__


#include "quadtree.h"

/**Paramètres  : un arbre quadratique tree
 * Dessine à partir de la bibliothèque MLV l'arbre quadratique donné en argument.
*/ 
void drawQuadT(Tree tree);

/**Paramètres : une image de type MLV, deux entiers x, y, et une taille length.
 * Cette fonction nous aide a savoir si une partie d'image est monochrome ou pas.
 * Elle renvoie la couleur de l'image, sous forme de tableau d'entier avec les 4 couleurs si elle est monochrome,
 * sinon elle renvoie null. 
*/
int* isMonochrome(MLV_Image* image, int x, int y, int length);

/**Paramètres : une image de type MLV, un arbe quadratique, deux entiers x, y, et une taille length.
 * Cette fonction a pour but de convertir une image en arbre quadratique.
 * Renvoie 1 lors de la fin de l'allocation d'une feuille.
*/
int convertImage(MLV_Image* image, Tree* quadT, int x, int y, int length);

/**Paramètres : une image de type MLV, deux entiers x, y, et une taille length. 
 * Cette fonction a pour but de convertir un arbre quadratique en image.
 * Renvoie 1 quand on a affecter tout les pixels dans l'image de la zone de l'arbre qu'on a en argument.
*/
int createImage(Tree quadT, MLV_Image* image, int x, int y, int length);



#endif