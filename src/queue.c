#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"

Queue allocateElement(Tree tree) {
    Element* element = (Element*)malloc(sizeof(Element));

    if (NULL == element) {
        exit(EXIT_FAILURE);
    }

    element->tree = tree;
    element->next = NULL;

    return element;
}


int enfiler(Queue* file, Tree tree) {
    Element* elementActuel = NULL;
    Element* nouveau = allocateElement(tree);

    if (*file != NULL) { /* La file n'est pas vide */
        elementActuel = *file;
        /* On se positionne à la fin de la file */
        while (elementActuel->next != NULL) {
            elementActuel = elementActuel->next;
        }
        elementActuel->next = nouveau;
    }
    else { /* La file est vide, notre élément est le premier */
        *file = nouveau;
    }

    return 0;
}



Tree defiler(Queue* file) {
    if (file == NULL) {
        return NULL;
    }

    Tree tree = NULL;

    /* On vérifie s'il y a quelque chose à défiler */
    if (*file != NULL) {
        Element* element = *file;

        tree = (*file)->tree;
        *file = (*file)->next;
        free(element);
    }

    return tree;
}