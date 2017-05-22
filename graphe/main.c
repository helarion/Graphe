#include <stdio.h>
#include <string.h>

#include "fonctions.h"

int main()
{
    struct Graphe g1;
    // r�cup�ration matrice
    g1=getMatrice("Graphes/matrice.txt");
    afficherMatrice(g1);

    // cr�ation de matrice
    setGraphe(1);
    afficherMatrice(g1);

    // sauvegarde de matrice
    saveGraphe(g1);


    dijkstra(g1);

    printf("\n");
    Kruskal(g1);

    //menu(g1);
    return 0;
}
