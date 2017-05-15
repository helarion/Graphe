#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

Pile *initialiserP()
{
    Pile *pile = malloc(sizeof(*pile));
    pile->premier = NULL;
}

void empiler(Pile *pile, int nvNombre)
{
    ElementP *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->nombre = nvNombre;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}

int depiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDepile = 0;
    ElementP *elementDepile = pile->premier;

    if (pile != NULL && pile->premier != NULL)
    {
        nombreDepile = elementDepile->nombre;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }

    return nombreDepile;
}

void afficherPile(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    ElementP *actuel = pile->premier;

    while (actuel != NULL)
    {
        printf("%d\n", actuel->nombre);
        actuel = actuel->suivant;
    }

    printf("\n");
}

int getPremierElementP(Pile *pile)
{
    int first;

    if (pile == NULL)
    {
     exit(EXIT_FAILURE);
    }

    ElementP *element = pile->premier;
    return element->nombre;

}

int estVideP(Pile *pile)
{
    ElementP *element = pile->premier;
    if(element==NULL){
        return 0;
    }else{
        return -1;
    }


}
