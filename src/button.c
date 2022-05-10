

#include "../include/button.h"

void drawSaveButtons(){
   
    MLV_draw_text_box( X_BOUTON1, Y_BOUTON1, 205, 35, "SAVE QTN", 10, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box( X_BOUTON1 + 230, Y_BOUTON1, 205, 35, "SAVE QTC", 10, MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_actualise_window();
}

int choiceSaveButton(int x, int y){
    
    if ((x >= X_BOUTON1) && (x <= X_BOUTON1 + 205) && (y >= Y_BOUTON1) && (y <= Y_BOUTON1 + 35)){
        return 1; // SAVE QTN
    }
    if ((x >= X_BOUTON1 + 230) && (x <= X_BOUTON1 + 435) && (y >= Y_BOUTON1 ) && (y <= Y_BOUTON1 + 35)){
        return 2; // SAVE QTC
    }
    return 0;
}
