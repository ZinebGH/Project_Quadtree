#ifndef __COMPRESS__ 
#define __COMPRESS__

#include "queue.h"
#include "image.h"
#define TAUX_R 60

/**Paramètres : un arbre quadratique quadT et un pointeur sur un arbre quadratique compressedT
 * Cette fonction permet d'allouer une arbre avec la moyenne de l'arbre quadT donné en argument 
 * dans l'arbre compresser compressedT passé en argument.
*/ 
void addInQuadT(Tree quadT, Tree* compressedT);

/**Paramètres : arbre quadratique compressedT.
 * On rend compressedT en un noeud.
*/ 
void becomeNode(Tree compressedT);

/**Paramètres : tableau de double err, deux tableaux de deux arbres quadratiques filsOriginT
 * et compressedT.
 * Elle trie les valeurs de err par ordre décroissant et trie de la même manière les deux 
 * autres tableaux pour avoir chacune des valeurs respectives aux mêmes indices que dans le tableau err
*/ 
void sortQuadT(double* err, Tree* filsOriginT, Tree* compressedT);

/**Paramètres : deux files queueOriginal et queueCompressed, un arbre root, et un entier hauteur.
 * Cette fonction permet de faire la compression sur un parcours en largeur en fonction des files
 * données en arguments et afficher pas à pas root à chaque hauteur passé, plus ou moins vite en fonction de notre hauteur.
*/
void compressQuadTAux(Queue queueOriginal, Queue queueCompressed, Tree root, int hauteur);


/**Paramètres : un arbre quadratique vquadT
 * Lance la compression de notre arbre d'origine.
 * Renvoie l'arbre compressé.
*/ 
Tree compressQuadT(Tree quadT);


#endif