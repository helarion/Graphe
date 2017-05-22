#ifndef FONCTIONS_H
#define FONCTIONS_H

struct Graphe
{
	int tailleX;
	int tailleY;

	int tailleInc;

	int matAdj[100][100]; // valeurs
	int matInc[100][100]; // booleene
};

void AdjToInc(struct Graphe *g);

void IncToAdj(struct Graphe *g);

void afficherMatrice(struct Graphe g);

struct Graphe getMatrice(char* nomFichier);

void saveGraphe(struct Graphe g);

struct Graphe setGraphe(int type);

void RechercheVoisins(int depart,struct Graphe g);

void parcoursLargeur(struct Graphe g);

void RechercheVoisinsProfondeur(int depart,struct Graphe g);

void parcoursProfondeur(struct Graphe g);

//affichage du tableau des poids

void afficherPoids(int poids[3][100], int c);

void dijkstra(struct Graphe g);

// initialisation des tableaux de poids et d'antécédents

void debut(int poids[100][100] , int precedent[][100] , int depart, int c);

// stocke le chemin le plus court déterminé précédement et renvoi le nombre de routeurs empruntés

int fin(int precedent[2][100], int arrivee, int depart, int c, int liste[100]);

// scan du graphe pour trouver le chemin le plus court
void chercherDijkstra(int graphe[100][100], int poids[3][100], int precedent[2][100], int depart, int arrivee, int c);

void Kruskal(struct Graphe g1);

void menu(struct Graphe g1);

// affichage du tableau des antécédents

void afficherPrecedent(int precedent[2][10], int c);

#endif
