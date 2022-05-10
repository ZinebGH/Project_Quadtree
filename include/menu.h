#ifndef __MENU__ 
#define __MENU__


#include "quadtree.h"


/**Paramètres : unsigned char image_name 
 * Vérifie si le type de notre image est bien en 8 bits (comprend 256 couleurs).
 */
int isImage(unsigned char image_name);


/**Paramètres : pointeur d'un pointeur sur une chaine de caractère name, pointeur d'entier nb
 * et une chaine de caractère path.
 * Permet de lire les différents fichier dans un répertoir donné. 
 * Tant que l'on a un fichier, on regarde s'il et de type image. Ensuite on alloue l'espace
 * de la longueur de l'image additionné a la longueur du nom répertoire dans lequel il se trouve 
 * sur un pointeur d'une chaine de caractères .
 * Ensuite on copie dans cette chaîne de caractère le nom de l'image et son répertoire (ex :
 * rep : image/ et nom : Tableau.png alors on aura image/Tableau.png). 
 * Pour par la suite copier la chaine de caractère dans notre chaine titres_img (permet d'avoir tout les 
 * nom d'image et leur répertoire) à l'indice i (correspond au nombre d'images que l'on trouvera).
 */
void readFolder(char ***name, int *nb, const char* path);


/**Paramètres : chaine de 50 caractère name, un entier nb et une chaine de caractère path.
 * Affiche les différentes images et file, trouvé dans path en fonction du nombre d'éléments compté, l'une à
 * coté de l'autre dans notre fenêtre.
 */
void drawImageFileMenu(char *name[50], int nb, char* path);


/**Paramètres : pointeur d'une image de type MLV, pointeur d'un arbre quadT quadratique
 * Permet d'affecter à image ou quadT l'image ou le fichier selectionné par l'utilisateur.
*/
int Choice(MLV_Image** image, Tree* quadT);


#endif