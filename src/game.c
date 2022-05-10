
#include "../include/game.h"




int game(){
    MLV_Image *image = NULL;
    MLV_Image *image2 = NULL;

    Tree tree, quadT, quadT2 = NULL;
    FILE* file = NULL;
    int x, y;
    //crée une fenêtre de taille WIDTH_WIN- HEIGHT_WIN avec comme nom Compression d'image
    MLV_create_window( "Compression d'image", "quadTree", WIDTH_WIN, HEIGHT_WIN);
    

    //Choix entre sélectionner une image ou un fichier pour lui faire une compression
    if(!Choice(&image, &quadT2)) {
	  	printf("ERROR, no file found !\n");
		return 0;
	}
    MLV_clear_window(MLV_COLOR_BLACK);

    //SI le mode compression à partir d'un fichier a été selectionné on obtient un arbre à partir de celui-ci
    if(quadT2 != NULL){
        
        image2 = MLV_create_image(IMAGE_SIZE, IMAGE_SIZE);
        //Affiche l'image d'origine
        createImage(quadT2, image2, 0, 0, IMAGE_SIZE);

        MLV_actualise_window();
        MLV_draw_image(image2, 0, 0);
       
        
        MLV_actualise_window();
        MLV_wait_mouse(NULL, NULL);
        //On a un nouvel arbre contennant la compression de notre quadT2
        quadT = compressQuadT(quadT2);
        drawSaveButtons();
        //Attend que l'utilisateur clique sur un des mode de sauvegarde soit .qtc soit .qtn
        while(1){
            MLV_wait_mouse(&x, &y);
            if(choiceSaveButton(x, y) == 1){
                //crée un fichier file.qtn dans le dossier doc pour sauvegarder l'arbre en question
                file = fopen("doc/file.qtn", "w");
                saveTreeQTN(quadT, file);
                fclose(file);
                break;
            }
            if(choiceSaveButton(x, y) == 2){
                //crée un fichier file.qtc dans le dossier doc pour sauvegarder l'arbre en question
                file = fopen("doc/file.qtc", "w");
                saveTreeQTC(quadT, file);
                fclose(file);
                break;

            }
        }
        
        MLV_free_image(image2);

       
    }
    //SI le mode compression à partir d'une image a été selectionné on obtient celle-ci
    if(image != NULL){
        //affiche l'image d'origine
        MLV_draw_image(image, 0, 0 ); // On dessine la 1ere image
        
        MLV_actualise_window();
        MLV_wait_mouse(NULL,NULL);

        //converti l'image en arbre quadratique
        convertImage(image, &tree, 0, 0, IMAGE_SIZE);
  
        //on prend l'arbre en question et on le compresse
        quadT = compressQuadT(tree);


        drawSaveButtons();
        //Attend que l'utilisateur clique sur un des modes de sauvegarde soit .qtc soit .qtn
        while(1){
            MLV_wait_mouse(&x, &y);

            if(choiceSaveButton(x, y) == 1){
                //crée un fichier image.qtn dans le dossier doc pour sauvegarder l'arbre en question

                file = fopen("file/image.qtn", "w");
                saveTreeQTN(quadT, file);
                fclose(file);
                break;
            }
            if(choiceSaveButton(x, y) == 2){
                //crée un fichier image.qtc dans le dossier doc pour sauvegarder l'arbre en question

                file = fopen("file/image.qtc", "w");
                saveTreeQTC(quadT, file);
                fclose(file);
                break;
            }
            
        }
        
        MLV_free_image(image);

    }

     MLV_free_window();

     return 0;
}
