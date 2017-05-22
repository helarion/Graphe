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

// Convertis une matrice d'adjacence en matrice incidente
void AdjToInc(struct Graphe *g);

// Convertis une matrice incidente en matrice d'adjacence
void IncToAdj(struct Graphe *g);

// Affiche la matrice dans ses 2 formats
void afficherMatrice(struct Graphe g);

//  Récupère la matrice depuis un fichier Texte
struct Graphe getMatrice(char* nomFichier);

//Sauvegarde legraphe au format souhaité(adj ou Inc)
void saveGraphe(struct Graphe g);

//Crée un graphe depuis le terminal
struct Graphe setGraphe(int type);

// Fonctionne de paire avec parcoursLargeur
void RechercheVoisins(int depart,struct Graphe g);

// Effectue un parcours en largeur du graphe
void parcoursLargeur(struct Graphe g);

// Fonctionne de paire avec parcoursProfondeur
void RechercheVoisinsProfondeur(int depart,struct Graphe g);

// Effectue un parcours en profondeur du graphe
void parcoursProfondeur(struct Graphe g);

//affichage du tableau des poids
void afficherPoids(int poids[3][100], int c);

// Implémete l'algorithme de dijkstra
void dijkstra(struct Graphe g);

// initialisation des tableaux de poids et d'antécédents
void debut(int poids[100][100] , int precedent[][100] , int depart, int c);

// stocke le chemin le plus court déterminé précédement et renvoi le nombre de routeurs empruntés
int fin(int precedent[2][100], int arrivee, int depart, int c, int liste[100]);

// scan du graphe pour trouver le chemin le plus court
void chercherDijkstra(int graphe[100][100], int poids[3][100], int precedent[2][100], int depart, int arrivee, int c);

// Implémete l'algorithme de de Kurskal
void Kruskal(struct Graphe g1);

// permet l'utilisation de de réuinir les fonction dnas un menu
void menu(struct Graphe g1);

// affichage du tableau des antécédents
void afficherPrecedent(int precedent[2][10], int c);

#endif
