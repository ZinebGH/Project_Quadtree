#ifndef __QUEUE__
#define __QUEUE__

#include "quadtree.h"

typedef struct element {
    Tree tree;
    struct element* next;
} Element, *Queue;

/**Paramètres : un arbre quadratique quadT.
 * Ca alloue un élément avec comme arbre l'arbre donné en paramètre dans une file.
 * Renvoie la file composé de l'élément 
*/
Queue allocateElement(Tree tree);

/**Paramètres : un pointeur d'une file queue et un arbre tree quadratique.
 * La fonction permet d'ajouter l'arbre passé en argument à la fin de la file queue
 * si celle-ci n'était pas vide, sinon elle sera en début de file.
 * Renvoie 0 si l'ajout c'est bien passé.
*/ 
int enfiler(Queue* queue, Tree tree);


/**Paramètres : un pointeur d'une file queue
 * Cette fonction permet de supprimer un élément de la file tout en gardant l'arbre associé 
 * à celui-ci.
 * Renvoi l'arbre de l'élément supprimé.
*/
Tree defiler(Queue *queue);

#endif
