#ifndef __QUADTREE__ 
#define __QUADTREE__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include <dirent.h>




#define WIDTH_WIN 512
#define HEIGHT_WIN 700
#define IMAGE_SIZE 512

typedef struct node{
    
    int red;
    int green;
    int blue;
    int alpha;
    
    struct node *NO, *NE, *SO, *SE;
}Node, *Tree;

/**Paramètres : entier r, g, b, a.
 * Permet d'alloué un noeud dans un arbre avec les valeurs données dans 
 * les arguments (r pour red, g pour green, b pour blue et a pour alpha).
*/
Tree allocateNode( int r, int g, int b, int a);

/**Paramètres : deux arbres quadratique quadT et quadT2.
 * Formule de la distance entre deux pixels. On prend pour chaque arbres sa valeur de rouge, vert, bleu et alpha 
 * qui forment le pixel respectif à chacun.
 * Renvoie un double.
*/
double dist(Tree quadT, Tree quadT2);

/**Paramètres : un arbre quadratique quadT, un autre arbre quadratique quadT_2, un pointeur de double err.
 * L'erreur est l'addition la somme obtenue de la distance entre deux pixels : un de l'arbre qui correspond à l'image 
 * originale et un de l'arbre contenant la moyenne des pixels.
 * L'erreur se calcul avec un parcours en profondeur sur l'arbre de l'image original.
*/
void errorDist(Tree quadT, Tree quadT_2, double* err);

/**Paramètres : un arbre quadratique quadT.
 * Fais la moyenne de la somme obtenue par AveragePixelAux de chaque couleur (r, g, b, a) en 
 * fonction du nombre de feuille rencontrée (cpt).
 * Un tableau d'entier de longueur 4 récupére la moyenne obtenue de chaque couleur.
 * Renvoie le tableau des couleurs moyennes.
*/
int* averagePixel(Tree quadT);

/**Paramètres : un arbre quadratique quadT.
 * Fonction booléenne qui renvoie 1 si on est sur une feuille, 0 sinon.
*/
int isLeaf(Tree quadT);

/** Paramètres : un arbre quadratique quadT, 4 pointeurs d'entiers respectifs à chaque couleur  d'une feuille
 * et un pointeur d'entier pour avoir un compteur cpt.
 * Fais la somme de toutes les couleurs rouge, vert, bleu et alpha de chaque feuilles rencontrées durant le 
 * parcours en longueur de l'arbre. Pour chaque feuille passé le compteur s'incrémente de un.
*/
void averagePixelAux(Tree quadT, int* r, int* g, int* b, int* a, int* cpt);

/** Paramètres : un arbre quadratique quadT et un fichier.
 *  En effectuant un parcours en profondeur (préfixe), le fichier contiendra la
 * description des noeuds du quadT rencontres sur une seule ligne. Un noeud
 * est code par 0, une feuille par 1 suivi de la nuance noire (1) ou blanche (0).
*/
void saveTreeQTN(Tree quadT, FILE* file);

/** Paramètres : un arbre quadratique quadT et un fichier.
 * En effectuant un parcours en profondeur (préfixe), le fichier contiendra la
 * description des noeuds du quadT rencontres sur une seule ligne. Un noeud
 * est code par 0, une feuille par 1 suivi de la nuance de rouge, vert, bleu et alpha.
*/
void saveTreeQTC(Tree quadT, FILE* file);


/**Non terminée*/
int equal2Trees(Tree quadT, Tree quadT2, double d);

/** Paramètres : un fichier, un arbre quadratique quadT et une chaîne de caractère.
 * transformerFichier permet de transformer un fichier (contenant la description d'un arbre 
 * quadratique) en quadTree en fonction de son extension .qtn ou .qtc.
 * Renvoie 1 si l'allocation est passée sinon 0.
*/
int transformFile(FILE* file, Tree* quadT, const char* text);

/**Paramètre : chaîne de caractère qui 
 *  Le but de cette methode est de charger un Tree quadratique a partir d'un fichier .qtc ou .qtn.
 * Renvoie l'arbre obtenu par le fichier
*/
Tree loadTree(const char* text); 
#endif