

#include "../include/menu.h"


int isImage(unsigned char image_name) {
	if(image_name == 8)
		return 1;
	return 0;
}



void readFolder(char ***name, int *nb, const char* path) {
	int i = 0;
	char* copyPath = "";
	DIR *dir = opendir(path);
    struct dirent *lecture;
	const char* end = "\0";
	copyPath = malloc(strlen(path)+1+4);
	strcpy(copyPath ,path);

	strcat(copyPath, end);
    char* repertory = copyPath;
	char *link = NULL;
	assert(NULL != name);
	assert(NULL != nb);

    if(dir == NULL)
        return;

    else {
        while((lecture = readdir(dir))) {
	        if(isImage(lecture->d_type)) {
	            link = malloc((lecture->d_reclen + strlen(repertory))*sizeof(char));
	            strcpy(link, repertory);
	            strcat(link, lecture->d_name);
	            strcpy((*name)[i],link);
	            i++;
	        }
        }
    }
    closedir(dir);
    *nb = i;
}



void drawImageFileMenu(char *name[50], int nb, char* path) {
	int i = 0, j = 0;
	int size = 103;
	int ecart = 20;
	assert(NULL != name);
	
	
	while(i * 4 + j < nb) {
		if(!strcmp(path, "image/")){
			MLV_Image* image;
			image = MLV_load_image(name[i * 4 + j]);
			MLV_draw_text(WIDTH_WIN/2 - 40, 2, "IMAGE CHOICE", MLV_COLOR_WHITE);
			MLV_resize_image(image, size, size);
			MLV_draw_image(image, ecart + j * (size + ecart), ecart + i * (size + ecart));
			MLV_free_image(image);
		}

		if(!strcmp(path, "file/")){
			MLV_draw_text(WIDTH_WIN/2 - 40, HEIGHT_WIN/2, "FILE CHOICE", MLV_COLOR_ORANGE_RED);

			
			MLV_actualise_window();
			MLV_draw_adapted_text_box(ecart + j  * (size + ecart), ecart + HEIGHT_WIN/2 + i * (size + ecart ), name[i * 4 + j], 2, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
		}

		if(j + 1 < WIDTH_WIN/(size - 1 + ecart))
			j++;
		else {
			i++;
			j = 0;
		}
	}
}


int Choice(MLV_Image** image, Tree* quadT) {
	char **arg;
	char **argF;

	int nb_image = 0, nb_file = 0, select, selectF;
	int x, y;
	assert(NULL != image);
	
	arg = malloc(50*sizeof(*arg));
	for(int i = 0; i < 50; i++)
		arg[i] = malloc(50*sizeof(char));

	argF = malloc(50*sizeof(*arg));
	for(int i = 0; i < 50; i++)
		argF[i] = malloc(50*sizeof(char));

	readFolder(&arg, &nb_image, "image/");

	readFolder(&argF, &nb_file, "file/");
	
	
	if (nb_image != 0)
		drawImageFileMenu(arg, nb_image, "image/");
	
	if (nb_file != 0)
		drawImageFileMenu(argF, nb_file, "file/");
		
	MLV_actualise_window();


	while(*image == NULL && *quadT == NULL) {
		MLV_wait_mouse(&x, &y);
		select = ((x - 20) / 120) + ((y - 20) / 120) * 4;
		selectF = ((x - 20) / 120) + ((y - HEIGHT_WIN/2- 20) / 120) * 4;
		

		if(select < nb_image && y > 0 && y <= HEIGHT_WIN/2 ){

			*image = MLV_load_image(arg[select]);
			MLV_resize_image(*image, IMAGE_SIZE, IMAGE_SIZE);
		}
		else if(selectF < nb_file &&  y > HEIGHT_WIN/2 && y <= HEIGHT_WIN )
			*quadT = loadTree(argF[selectF]);
	}
    return 1;
}
