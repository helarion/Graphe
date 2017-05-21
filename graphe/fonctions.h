struct Graphe
{
	int tailleX;
	int tailleY;

	int tailleInc;

	int matAdj[100][100]; // valeurs
	int matInc[100][100]; // booleene
};

static void AdjToInc(struct Graphe *g);

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
/*
void composanteFortementConnexe(int resultat[100][100], struct graphe graphe) {

    int adjacence[100][100] = matrice;

    int matricePuissance[100][100] = adjacence;
    int puissance[100][100] = adjacence;
    int puissance2[100][100];
    int i,e;
    int tailleMatPuissance=0;
    int taillePuissance=0;
    int taillePuissance2=0;
    int tailleTmp=0;

    for (i = 0; i < taillePuissance; i++) {
        int tmp[100];

        for (e = 0; e < taillePuissance; e++) {
                tmp[tailleTmp]=0;
                tailleTmp++;
                puissance2[taillePuissance2][e]=0;
        }
    }

    //On récupère ensuite la matrice contenant tout les chemins
    while (!equal(puissance.begin(), puissance.end(), puissance2.begin())) {

        puissance2 = puissance;
        puissance = produitMatriciel(puissance, adjacence);

        for (int i = 0; i < matricePuissance.size(); i++) {

            for (int e = 0; e < matricePuissance.at(i).size(); e++) {
                matricePuissance.at(i).at(e) += puissance.at(i).at(e);
                if (matricePuissance.at(i).at(e) > 1)
                    matricePuissance.at(i).at(e) = 1;
            }

        }

    }

    vector<vector<int>> composante;
    vector<vector<int>> structure;

    //On cherche ensuite les différentes composantes connexe
    for (int i = 0; i < matricePuissance.size(); i++) {

        vector<int> structSommet;

        for (int e = 0; e < matricePuissance.at(i).size(); e++) {
            structSommet.push_back(matricePuissance.at(e).at(i));
        }

        bool trouve = false;
        int indiceComposante = 0;

        //On parcourt les différentes colonnes que l'on a retenu
        for (int e = 0; e < structure.size(); e++) {
            if (equal(structure.at(e).begin(), structure.at(e).end(), structSommet.begin())) {
                indiceComposante = e;
                trouve = true;
            }
        }

        //Si aucune n'a été trouvé on l'ajoute
        if (!trouve) {
            vector<int> tmp;
            tmp.push_back(i);
            composante.push_back(tmp);
            structure.push_back(structSommet);
        }
        else { //Sinon on ajoute le sommet dans la composante
            composante.at(indiceComposante).push_back(i);
        }

    }

    //On retourne les composantes
    return composante;

}
*/

void menu(struct Graphe g1);

// affichage du tableau des antécédents

void afficherPrecedent(int precedent[2][10], int c);




