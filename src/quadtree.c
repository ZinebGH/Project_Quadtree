#include "../include/quadtree.h"



Tree allocateNode( int r, int g, int b, int a){
    Tree tmp;
    tmp = (Tree)malloc(sizeof(Node));
    if(tmp == NULL)
      return NULL;

    tmp->red = r;
    tmp->green = g;
    tmp->blue = b;
    tmp->alpha = a;
    tmp->NO = NULL;
    tmp->NE = NULL;
    tmp->SO = NULL;
    tmp->SE = NULL;
    return tmp;
}

double dist(Tree quadT, Tree quadT2){
    return sqrt(pow(quadT->red - quadT2->red, 2) + pow(quadT->green - quadT2->green, 2) + pow(quadT->blue - quadT2->blue, 2) + pow(quadT->alpha - quadT2->alpha, 2)); 
}

void errorDist(Tree quadT, Tree quadT2, double* err){

    double d;


    if (quadT == NULL){
        return;
    }

    //Incrémente err avec la valeur de d qui est la somme de la distance entre chaque pixel rencontré lors du parcours en longueur
    d = dist(quadT, quadT2);
    *err += d;
    
    errorDist(quadT->NO, quadT2, err);
    errorDist(quadT->NE, quadT2, err);
    errorDist(quadT->SE, quadT2, err);
    errorDist(quadT->SO, quadT2, err);

}

int isLeaf(Tree quadT){
    return quadT->red != -1;
}

void averagePixelAux(Tree quadT, int* r, int* g, int* b, int* a, int* cpt){
    
    if(quadT == NULL)
        return;
    //Verifie si on est dans une feuille : si oui on incrémente r, g, b et a avec les nouvelles valeurs de notre feuille
    if(isLeaf(quadT)){
        *r += quadT->red;
        *g += quadT->green;
        *b += quadT->blue;
        *a += quadT->alpha;

        *cpt += 1;
        return;
    }
    //Parcours en longueur de tout l'arbre afin de récupérer toute les feuilles
    averagePixelAux(quadT->NO, r, g, b, a, cpt);
    averagePixelAux(quadT->NE, r, g, b, a, cpt);
    averagePixelAux(quadT->SE, r, g, b, a, cpt);
    averagePixelAux(quadT->SO, r, g, b, a, cpt);

}

int* averagePixel(Tree quadT){
    int* tab = (int*)malloc(sizeof(int)*4);
    int r = 0, g = 0, b = 0, a = 0, cpt = 0;

    averagePixelAux(quadT, &r, &g, &b, &a, &cpt);

    tab[0] = r/cpt;
    tab[1] = g/cpt;
    tab[2] = b/cpt;
    tab[3] = a/cpt;
    return tab;
}

void saveTreeQTN(Tree quadT, FILE* file){
    int average;
    if (file == NULL)
		return;
    if (quadT == NULL){
        return;
    }
    //Vérifie si c'est un noeud, pas besoin des 4 couleurs : lors de l'allocation un noeud à -1 dans les 4
     if (quadT->red == -1)
        fprintf(file, "0 ");
    else{
        //moyenne faite pour savoir si la couleur se rapproche plus du noir ou du blanc
        average = (quadT->red + quadT->green + quadT->blue)/3;
        if(average >= 0 && average <= 255/2)
            //Si compris entre 0 et 127 sa sera du noir
            fprintf(file, "1 1 ");
        if(average > 255/2 && average <= 255)
            //SI compris entre 128 et 255 sa sera du blanc
            fprintf(file, "1 0 ");
    }

    //Parcours en longueur
    saveTreeQTN(quadT->NO, file);
    
    saveTreeQTN(quadT->NE, file);
    
    saveTreeQTN(quadT->SE, file);
    
    saveTreeQTN(quadT->SO, file);
    
}

void saveTreeQTC(Tree quadT, FILE* file){
    
    if (file == NULL)
		return;
    if (quadT == NULL){
        return;
    }
     if (quadT->red == -1)
        fprintf(file, "0 ");
    else
        //Si une feuille met un 1 suivi des nuances de rouge, vert, bleu et alpha
        fprintf(file, "1 %d %d %d %d ", quadT->red, quadT->green, quadT->blue, quadT->alpha);
    saveTreeQTC(quadT->NO, file);
    
    saveTreeQTC(quadT->NE, file);
    
    saveTreeQTC(quadT->SE, file);
    
    saveTreeQTC(quadT->SO, file);
    
}


int equal2Trees(Tree quadT, Tree quadT2, double d){
	
    if (quadT == NULL){
        if (quadT2 == NULL)
            return 1;
        return 0;
    }
    if (quadT2 == NULL)
        return 0;

    if(isLeaf(quadT) && isLeaf(quadT2)){
        d = dist(quadT, quadT2);
    }

   
    if (isLeaf(quadT) && !isLeaf(quadT2)){
        // for(int i = 0; i < 4; i++){
            d += dist(quadT, quadT2)/4;
            equal2Trees(quadT, quadT2->NO, d);
            equal2Trees(quadT, quadT2->NE, d);
            equal2Trees(quadT, quadT2->SE, d);
            equal2Trees(quadT, quadT2->SO, d);

        // }
    }

    if (!isLeaf(quadT) && isLeaf(quadT2)){
        // for(int i = 0; i < 4; i++){
            d += dist(quadT, quadT2)/4;
            equal2Trees(quadT->NO, quadT2, d);
            equal2Trees(quadT->NE, quadT2, d);
            equal2Trees(quadT->SE, quadT2, d);
            equal2Trees(quadT->SO, quadT2, d);
        // }
    }

    if (!isLeaf(quadT) && !isLeaf(quadT2)){
        // for(int i = 0; i < 4; i++){
            d += dist(quadT, quadT2)/4;
            equal2Trees(quadT->NO, quadT2->NO, d);
            equal2Trees(quadT->NE, quadT2->NE, d);
            equal2Trees(quadT->SE, quadT2->SE, d);
            equal2Trees(quadT->SO, quadT2->SO, d);
        // }
    }
    return 0;
}


int transformFile(FILE* file, Tree* quadT, const char* text){

    int node, bw;
    int color[4] = {};
    //si l'extension du fichier est .qtn
    if(!strcmp(text, ".qtn")){
        if (fscanf(file, "%d", &node) < 1)
            return 0;
        //on regarde si on est sur une feuille et pas un noeud car 0 noeud - 1 feuille
        if(node == 1){
            if (fscanf(file, "%d", &bw) < 1)
                return 0;
            //on regarde la couleur suivi du 1 soit 0 pour blanc soit 1 pour noir
            if(bw == 0){
                //Alloue une noeud avec la couleur blanche
                if((*quadT = allocateNode(255, 255, 255, 255)) == NULL)
                    return 0;
                return 1;
            }
            if(bw == 1){
                //Alloue une noeud avec la couleur noire
                if((*quadT = allocateNode(0, 0, 0, 255)) == NULL)
                    return 0;
                return 1;   
            }
        }
    }
    //Si l'extension du fichier est .qtc
    if(!strcmp(text, ".qtc")){
        if (fscanf(file,"%d",&node ) < 1)
            return 0;
        //on regarde si on est sur une feuille et pas un noeud car 0 noeud - 1 feuille
        if(node == 1){
                //Si on a 4 entiers à la suite de 1
                if (fscanf(file,"%d %d %d %d", &color[0], &color[1], &color[2], &color[3]) < 1)
                    return 0;
                //On récupére ces entiers et on les alloues pour avoir notre couleur dans une feuille de l'arbre
                if((*quadT = allocateNode(color[0], color[1], color[2], color[3])) == NULL)
                    return 0;
                return 1;
            }
    }
    
    //Si on est pas sur un 1 on alloue un noeud avec les entiers -1 pour chaque couleurs    
    if((*quadT = allocateNode(-1, -1, -1, -1)) == NULL)
        return 0;
            
    //On parcours l'arbre
    return transformFile(file, &((*quadT)->NO), text) &&
           transformFile(file, &((*quadT)->NE), text) &&
           transformFile(file, &((*quadT)->SE), text) &&
           transformFile(file, &((*quadT)->SO), text);
}


Tree loadTree(const char* text){

    Tree quadT = NULL;
    //On ouvre le fichier text pour le lire
    FILE* file = fopen(text, "r");
    //SI son extension à .qtc alors on appel la fonction pour les fichiers d'abre binaire en couleur
    if(strstr(text, ".qtc") != NULL){
        transformFile(file, &quadT, ".qtc");
    }
    //SI son extension à .qtn alors on appel la fonction pour les fichiers d'abre binaire en noir et blanc
    if(strstr(text, ".qtn") != NULL)
        transformFile(file, &quadT, ".qtn");

    fclose(file);

    return quadT;
}
