#include <stdio.h>
#include <string.h>

#include "fonctions.h"

int main()
{
    struct Graphe g1;
    g1=getMatrice("graphes/matrice.txt");
    //IncToAdj(&g1);
    afficherMatrice(g1);
    dijkstra(g1);
    return 0;
}
