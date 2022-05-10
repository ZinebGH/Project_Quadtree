#include "../include/compress.h"


int i, j;


void addInQuadT(Tree quadT, Tree* compressedT){
    int* color;
    color = averagePixel(quadT);
    (*compressedT) = allocateNode(color[0], color[1], color[2], color[3]);
}

void sortQuadT(double* err, Tree* filsOriginT, Tree* compressedT){
    double tmp;
    Tree tmpOrigin, tmpCompressed;
    for (i = 0; i < 4; i++){
        for (j = i + 1; j < 4; j++){
            //trie en gardant chaque valeurs liées à l'indice dans le même ordre
            if (err[i] < err[j]){
            
                tmp =  err[i];
                err[i] = err[j];
                err[j] = tmp;

                tmpOrigin = filsOriginT[i];
                filsOriginT[i] = filsOriginT[j];
                filsOriginT[j] = tmpOrigin;

                tmpCompressed = compressedT[i];
                compressedT[i] = compressedT[j];
                compressedT[j] = tmpCompressed;
            }
        }
    }
}

void becomeNode(Tree compressedT){

    compressedT->red = -1;
    compressedT->green = -1;
    compressedT->blue = -1;
    compressedT->alpha = -1;
    return; 
}


void compressQuadTAux(Queue queueOriginal, Queue queueCompressed, Tree root, int hauteur) {
    if (queueOriginal == NULL || queueCompressed == NULL) {
        return;
    }
    //On récupére les arbres des éléments supprimé dans la file queueOriginal et queueCompressed
    Tree originT = defiler(&queueOriginal);
    Tree compressedT = defiler(&queueCompressed);

    if (originT == NULL || isLeaf(originT) || compressedT == NULL) {
        return;
    }

    int i;
    double err[4] = {0, 0, 0, 0};

    //On prend les sous arbres respectifs de originT et compressedT que l'on met dans leur tableau tableau d'arbre respectif
    Tree filsOriginT[4] = {originT->NO, originT->NE, originT->SE, originT->SO};
    Tree filsCompressedT[4] = {compressedT->NO, compressedT->NE, compressedT->SE, compressedT->SO};

    
    if (hauteur % TAUX_R <  8){
        drawQuadT(root);
    }
    
    becomeNode(compressedT);

    //On ajoute dans filsCompressedT chaque moyenne obtenue de filsOriginT[i] pour les 4 sous arbres 
    for (i = 0; i < 4; i++) {
        addInQuadT(filsOriginT[i], &(filsCompressedT[i]));
    }

    //On affecte chaque moyenne obtenue dans filsCompressedT à chaque sous arbre de compressedT, qui leurs est respective pour les actualiser
    compressedT->NO = filsCompressedT[0];
    compressedT->NE = filsCompressedT[1];
    compressedT->SE = filsCompressedT[2];
    compressedT->SO = filsCompressedT[3];


    //On calcul l'erreur de chaque sous-arbre[i] de filsOriginT et filsCompressedT et on affecte la valeur à err[i]
    for (i = 0; i < 4; i++) {
        errorDist(filsOriginT[i], filsCompressedT[i], &err[i]);
    }

    //On trie les éléments mais on retrouvera au même indice les valeurs respectives à chacun
    sortQuadT(err, filsOriginT, filsCompressedT);
    
    for (i = 0; i < 4; i++) {
        if (err[i] == 0) {
            /* La distance d'erreur est nulle <=> le sous arbre est fidèle à la couleur réelle */
            continue;
        }
        //On ajoute chaque sous-arbre de filsOriginT dans la file queueOriginal
        enfiler(&queueOriginal, filsOriginT[i]);
        //On ajoute chaque sous-arbre de filsCompressedT dans la file queueCompressed
        enfiler(&queueCompressed, filsCompressedT[i]);
    }
    //On rappel cette fonction pour continuer la compression jusqu'à que l'on se retrouve
    compressQuadTAux(queueOriginal, queueCompressed, root, hauteur + 1);

    return;
}

Tree compressQuadT(Tree originT){
    Tree firstT = NULL;
    int* color = NULL;
    int hauteur = 1;
    Queue queueOriginal = NULL, queueCompressed = NULL;
    //On fait la moyenne de l'image totale
    color = averagePixel(originT);
    //On alloue a un arbre les valeurs des nuance (rgba) obtenue de la moyenne color
    firstT = allocateNode(color[0], color[1], color[2], color[3]);
    //On alloue a queueOriginal l'arbre d'origine
    queueOriginal = allocateElement(originT);
    //On alloue a queueOriginal l'arbre de compression que l'on vient de créer
    queueCompressed = allocateElement(firstT);
    //Lancement de la compression 
    compressQuadTAux(queueOriginal, queueCompressed, firstT, hauteur);

    return firstT;
}