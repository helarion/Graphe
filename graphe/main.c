#include <stdio.h>
#include <string.h>

#include "fonctions.h"

int main()
{
    struct Graphe g1;
    //menu(g1);
    g1=getMatrice("graphes/matrice.txt");
    dijkstra(g1);
    return 0;
}
