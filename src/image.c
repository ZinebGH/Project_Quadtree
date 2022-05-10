

#include "../include/image.h"



void drawQuadT(Tree tree) {
    MLV_Image *image = NULL;

    image = MLV_create_image(IMAGE_SIZE, IMAGE_SIZE);
    createImage(tree, image, 0, 0, IMAGE_SIZE);

    MLV_draw_image(image, 0, 0);
    MLV_actualise_window();
    MLV_free_image(image);
}

int* isMonochrome(MLV_Image* image, int x, int y, int length){ 
	int* tab = NULL;
    //ON alloue l'espace de 4 entier pour les couleurs r, g, b et a
    tab = (int*)malloc(sizeof(int) * 4);
    int i, j;
    int red, blue, green, alpha;
    //On prend un pixel à une coordonnées prise en argument et on met les couleurs rouge, verte, bleue et alpha dans notre tab
    MLV_get_pixel_on_image(image, x, y, &tab[0], &tab[1], &tab[2], &tab[3]);
    for (i = x; i < x + length; i++){
        for (j = y; j < y + length; j++){
            //On prend un pixel à (i, j), et on prend les couleurs obtenues de chaque nuance
            MLV_get_pixel_on_image(image, i, j, &red, &green, &blue, &alpha);
            //Si les couleurs du premier pixel et du deuxieme ne sont pas identique on renvoie null
            if (tab[0] != red || tab[1] != green || tab[2] != blue || tab[3] != alpha){
			    return NULL;
            }
        }
    }
    
    //sinon on renvoi le tab contenant les nuances
    return tab;


}

int convertImage(MLV_Image* image, Tree* quadT, int x, int y, int length){
	int* color = NULL;
	
	
    color = isMonochrome(image, x, y, length);
	
    if (color != NULL){
        //on alloue une feuille avec la couleurs des nuances obtenue plus haut
		if ((*quadT = allocateNode(color[0], color[1], color[2], color[3])) == NULL){
			return 0;
    	}
	    return 1;
    }
    //Sinon on alloue un noeud 
	if ((*quadT = allocateNode(-1, -1, -1, -1)) == NULL){
		return 0;
    }
    
	return convertImage(image, &((*quadT)->NO), x, y, length/2)
        && convertImage(image, &((*quadT)->NE), x + (length/2), y, length/2)
        && convertImage(image, &((*quadT)->SE), x + (length/2), y + (length/2), length/2) 
        && convertImage(image, &((*quadT)->SO), x, y + (length/2), length/2);    
}



int createImage(Tree quadT, MLV_Image* image, int x, int y, int length){

    int color;
    if (quadT == NULL)
        return 0;
    //si on a une feuille
    if (quadT->red != -1){
        int i, j;
    
        for (i = x; i < x + length; i++){
            for (j = y; j < y + length; j++){
                //on prend la couleur obtenue avec les valeur de notre arbre pour chaque nuance
                color = MLV_rgba(quadT->red, quadT->green, quadT->blue, quadT->alpha);
                //on affecte un pixel de cette couleur a notre image à la position (i, j)
                MLV_set_pixel_on_image(i, j, color, image);
            }
        }
        return 1;
    }
    length = length/2;
    return createImage(quadT->NO ,image , x, y, length) &&
		   createImage(quadT->NE ,image , x + length, y, length) &&
		   createImage(quadT->SE ,image , x + length, y + length, length) &&
		   createImage(quadT->SO ,image , x, y + length, length);
}