#include "file.h"
#include "pile.h"

#define ADJACENCE 1
#define INCIDENCE 2
#define TAILLE_MAX 1000

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "fonctions.h"



int TabFile[50];

// sert au parcours en largeur
File *maFile;
int compteurSommetsPasses;
int SommetsPasses[50];

// sert au parcours en profondeur
Pile *maPile;
int sommetsMarques[50];
int sommetsvisites[50];
int compteurMarque;
int compteurVisite;


void AdjToInc(struct Graphe *g)
{
    int i,j,tailleX,tailleY;
    int c=0;

    tailleX=g->tailleX;
    tailleY=g->tailleY;

    // calcul du nombre d'arretes
    for(i=0;i<tailleX;i++)
    {
        for(j=i+1;j<tailleY;j++)
        {
            if(g->matAdj[i][j]!=0) c++;
        }
    }

    g->tailleInc=c;
    c=0;

    //conversion
    for(i=0;i<tailleX;i++)
    {
        for(j=i+1;j<tailleY;j++)
        {
            if(g->matAdj[i][j]!=0)
            {
                g->matInc[i][c]=1;
                g->matInc[j][c]=1;
                g->matInc[tailleX][c]=g->matAdj[i][j];
                c++;
            }

        }
    }
}

void IncToAdj(struct Graphe *g)
{
    int i,j;
    int poids;

    g->tailleY=g->tailleX;

    for(i=0;i<g->tailleInc;i++)
    {
        poids=g->matInc[g->tailleX][i];

        for(j=0;j<g->tailleX;j++)
        {
            if(g->matInc[j][i]!=0)
            {
                g->matAdj[j][i]=poids;
                g->matAdj[i][j]=poids;
            }
        }
    }
}

void afficherMatrice(struct Graphe g)
{
    int i,j;

    printf("données affichage : \n");
	printf("g.TailleX :%d \n",g.tailleX);
	printf("g.TailleY :%d \n",g.tailleY);
	printf("g.tailleInc :%d\n",g.tailleInc);


    printf("Matrice d'adjacence:\n");
	char car='A';
	printf("Graphe:\n ");
	for(i=0; i<g.tailleX;i++)
	{
		printf(" %c ",car);
		car++;
	}
	printf("\n");
	car='A';
	for(i=0; i<g.tailleX; i++)
   	{
		printf("%c ",car);
        for(j=0; j<g.tailleY; j++)
        {
            printf("%d ",g.matAdj[i][j]);
			if(g.matAdj[i][j]<10) printf(" ");
        }
		car++;
        printf("\n");
    }
	printf("\n");

	printf("Matrice d'incidence:\n");

	printf("arcs --> \n");
	for(i=0;i<g.tailleX+1;i++)
	{
		for(j=0;j<g.tailleInc;j++)
		{
			printf("%d",g.matInc[i][j]);
			if(j!=g.tailleInc-1)
			{
				printf("-");
			}
		}
		printf("\n");
	}
}

struct Graphe getMatrice(char* nomFichier)
{
	FILE *fp;
	fp = fopen(nomFichier, "r");

	if (fp == NULL) {
	  fprintf(stderr, "Impossible d'ouvrir le fichier!\n");
	  return ;
	}

	struct Graphe g;
    int c;

    int i=0;
    int j=0;

    int type;
    fscanf(fp,"%d",&c);
    type=c;

    //printf("type:%d\n",type);

    if(type==ADJACENCE)
    {
        fscanf(fp,"%d",&c);
        g.tailleX=c;
        fscanf(fp,"%d",&c);
        g.tailleY=c;
        for(i=0;i<g.tailleX;i++)
        {
            for(j=0;j<g.tailleY;j++)
            {
                fscanf(fp,"%d",&c);
                g.matAdj[i][j]=c;
            }
        }
        // calcul de la matrice d'incidence
        AdjToInc(&g);
    }
    else if(type==INCIDENCE)
    {
        fscanf(fp,"%d",&c);
        g.tailleInc=c;
        fscanf(fp,"%d",&c);
        g.tailleX=c-1;
        for(i=0;i<g.tailleX+1;i++)
        {
            for(j=0;j<g.tailleInc;j++)
            {
                fscanf(fp,"%d",&c);
                g.matInc[i][j]=c;
            }
        }
        // calcul de la matrice d'adjacence
        IncToAdj(&g);
    }
    fclose(fp);
	return g;
}

void saveGraphe(struct Graphe g)
{
    FILE *f;
    char nomGraphe [50];
    char chemin[50]="Graphes/";
    int type;
    printf("Entrez le type de graphe :\n");
    printf("ADJACENCE :1\n");
    printf("INCIDENCE :2\n");
    scanf("%d",&type);

    printf("Entrez le nom de graphe :\n");
    scanf("%s",&nomGraphe);

    strcat(chemin,nomGraphe);
    strcat(chemin,".txt");

    f=fopen(chemin,"w");

    int i,j;

    if(f == NULL) //if file does not exist, create it
    {
        freopen(chemin, "w", f);
    }

    char write[100];

    // récupération type et tailles
    sprintf(write, "%d", type);
    fprintf(f,"%s",write);
    fprintf(f," ");
    sprintf(write, "%d", g.tailleX);
    fprintf(f,"%s",write);
    fprintf(f," ");
    sprintf(write,"%d", g.tailleInc);
    fprintf(f,"%s",write);
    fprintf(f,"\n");

    switch(type)
    {
    case 1:
         for(i=0;i<g.tailleX;i++)
        {
            for(j=0;j<g.tailleY;j++)
            {
                sprintf(write, "%d", g.matAdj[i][j]);
                if(j<g.tailleX-1) strcat(write," ");
                fprintf(f,"%s",write);
            }
            if(i<g.tailleX+1) fprintf(f,"\n");
        }
        break;
    case 2:
        for(i=0;i<g.tailleX+1;i++)
        {
            for(j=0;j<g.tailleInc;j++)
            {
                sprintf(write, "%d", g.matInc[i][j]);
                if(j<g.tailleInc-1) strcat(write," ");
                fprintf(f,"%s",write);
            }
            if(i<g.tailleX+1) fprintf(f,"\n");
        }
      break;
    default:
      printf("erreur");
      break;
    }
    fclose(f);
}

struct Graphe setGraphe(int type)
{
    int tailleX;
    int tailleY;
    struct Graphe g;

    printf("Entrez la taille x de la matrice: --> \n");
    scanf("%d",&tailleY);
    if(type==ADJACENCE){
    	tailleX=tailleY;
    }
    else if(type==INCIDENCE){
        printf("Entrez la taille y de la matrice: | \n");
        scanf("%d",&tailleX);
        g.tailleInc=tailleX;
	}

    g.tailleX=tailleX;
    g.tailleY=tailleY;

    int i,j,val;
    for(i=0;i<tailleX;i++)
    {
        for(j=0;j<tailleY;j++)
        {
            printf("[%d][%d]:",i,j);
            scanf("%d",&val);
            if(type==INCIDENCE){
            	g.matInc[i][j]=val;
            }
            if(type==ADJACENCE){
            	g.matAdj[i][j]=val;
            }

        }
    }

    if(type==ADJACENCE) AdjToInc(&g);
    else if(type==INCIDENCE) IncToAdj(&g);

    return g;
}

void RechercheVoisins(int depart,struct Graphe g)
{

	int i=0;
	int j=0;

	int flag=0;

	printf("tableau file :\n");
	StockerFile(maFile,TabFile);
	for(i=0;i<10;i++){

		printf("%d-",TabFile[i]);

	}
		printf("\n");
	printf("SommetsPasses :\n");
	for(i=0;i<10;i++){
		printf("%d-",SommetsPasses[i]);

	}
	printf("\n");
	printf("============\n");

	for(i=0;i<g.tailleY;i++)
	{
		if(g.matAdj[depart][i]!=0)
			{
				printf("%d est voisin avec %d \n",depart,i);
				for(j=0;j<10;j++){
					if(i==SommetsPasses[j]){
						printf("%d est deja passÃ© \n", i);
						flag=1;
						break;
					}else if(i==TabFile[j]){
					printf("%d est deja dans la file \n", i);
					flag=1;
					break;
					}
				}
				if(flag!=1){
						printf("ajout de : %d Ã  la file \n",i);
						enfiler(maFile,i);
						printf("ajout de : %d en sommet passÃ© \n",depart);
						SommetsPasses[compteurSommetsPasses]=depart;

					}
				printf("ajout de : %d en sommet passÃ© \n",depart);
				SommetsPasses[compteurSommetsPasses]=depart;
				j=0;
				flag=0;


			}
	}
	compteurSommetsPasses++;

}

void parcoursLargeur(struct Graphe g)
{

	maFile =initialiser();
	int i=0;
	int parcours[50];

	int compteur=0;
	enfiler(maFile,0);

	while(estVide(maFile)!=0){

		RechercheVoisins(getPremierElement(maFile),g);
		parcours[compteur]=getPremierElement(maFile);
		compteur++;
		defiler(maFile);
	}

	for(i=0;i<g.tailleX;i++){
		printf("%d ->",parcours[i]);
	}
	printf("\n");
	compteurSommetsPasses=0;
	for(i=0;i<50;i++){
	SommetsPasses[i]=0;
	}

}

void RechercheVoisinsProfondeur(int depart,struct Graphe g)
{
	int i=0;
	int j=0;
	int flag=0;
	int compteurSucesseurs=0;
	sommetsvisites[compteurVisite]=depart;
	compteurVisite++;


	printf("depart : %d \n",depart);
	for(i=0;i<g.tailleY;i++)
	{
		// si depart a un voisin
		if(g.matAdj[depart][i]!=0)
		{
			compteurSucesseurs++;
		}
	}
	if(compteurSucesseurs<=1){
		printf("%d n'a pas de descendant : marquage \n",depart);
		sommetsMarques[compteurMarque]=depart;
		compteurMarque++;
		//50 valeur arbitraire
		depiler(maPile);
		return;
	}
	compteurSucesseurs=0;

	//parcours voisins de depart
	for(i=0;i<g.tailleY;i++)
	{
		printf("parcours de voisin \n");
		// si depart a un voisin
		printf("recherche en [%d][%d] \n",depart,i);
		if(g.matAdj[depart][i]!=0)
		{
			printf("voisin trouvé en : %d \n",i);
			for(j=0;j<50;j++){
				// si ce voisin est marqué
				printf("j: %d",j);
				if(i==sommetsMarques[j]){
					printf("voisin déjà marqué, next :\n");
					flag=1;
					break;
				}

				if(i==sommetsvisites[j]){
					printf("voisin dÃ©jÃ  visitÃ©, next :\n");
					flag=1;
					break;
				}
			}
			// si voisin non marqué
				if(flag!=1){
				printf("voisin non marqué ni visité, ajout à la pile \n");
				empiler(maPile,i);
				return;
			   	}
				flag=0;

		}

	}
	printf("Aucun voisin non marqué ou non visité : marquage \n");
	depiler(maPile);
	sommetsMarques[compteurMarque]=depart;
	compteurMarque++;

}

void parcoursProfondeur(struct Graphe g)
{
	maPile= initialiserP();
	empiler(maPile,0);
	int i=0;
	int j=0;
	for(i=0;i<50;i++){
		sommetsMarques[i]=-1;
		sommetsvisites[i]=-1;
	}

	while(estVideP(maPile)!=0){
		RechercheVoisinsProfondeur(getPremierElementP(maPile),g);
		printf("sommets marquÃ©s :  sommets visitÃ©s :\n");
		for(j=0;j<7;j++){
			printf("%d                  %d\n",sommetsMarques[j],sommetsvisites[j]);
		}

	}

	//for(j=0;j<10;j++){
	j=0;
	while(sommetsMarques[j]!=(-1)){
		printf("%d->",sommetsMarques[j]);
		j++;
	}

	printf("\n");
}

//affichage du tableau des poids

void afficherPoids(int poids[3][100], int c)
{
    int i;
	printf("\nTable des poids:\n");
	for(i=0; i<c; i++)
	{
		char car='A';
		car+=poids[0][i];
		printf("%c: poids=%d ",car,poids[1][i] );
		if(poids[2][i]==1) printf("scanne");
		else printf("non scanne");
		printf("; \n");
	}
}

void dijkstra(struct Graphe g)
{
    printf("Calcul du plus cours chemin:\n");
    int poids[3][100];
    int precedent[2][100];
    int taille=g.tailleX;
    int i;
    char* adresses[100];
    for(i=0; i<taille; i++) // remplissage de la liste des adresses
		{
			char car='A';
			car+=i;
			adresses[i]=car;
		}

    afficherMatrice(g);
    int depart;
    int arrivee;
    char car1,car2;
    printf("Entrez le noeud de depart (maj):");
    scanf("%s",&car1);
    printf("\nEntrez le noeud d'arrivee:");
    scanf("%s",&car2);
     for(i=0; i<taille; i++) // création des index des adresses entrées
		{
			char* ad = adresses[i];
			if(ad==car1) depart=i;
			if(ad==car2) arrivee=i;
		}
    //afficherPoids(poids,taille);
    debut(poids,precedent,depart,taille);
    //afficherPoids(poids,taille);
    chercherDijkstra(g.matAdj,poids,precedent,depart,arrivee,taille);
    int liste[10];
    int compt=fin(precedent,arrivee,depart,taille,liste);
    car1='A';
    car1+=depart;
    car2='A';
    car2+=arrivee;
    if(poids[1][arrivee]!=0)
    {
        printf("Pour aller de %c vers %c",car1, car2);
        printf(" il faut emprunter les noeuds suivants:\n");
        int i;
        for(i=compt-1; i>=0; i--)
        {
            car1='A';
            car1+=liste[i];
            printf("%c",car1);
            if(car1!=car2) printf(" vers ");
        }
        printf(" pour un poids total de %d",poids[1][arrivee]);
    }
    else
    {
        printf("Aucun chemin de %c à %c \n",car1,car2);
    }
}

// initialisation des tableaux de poids et d'antécédents

void debut(int poids[100][100] , int precedent[][100] , int depart, int c)
{
    int i;
	for(i=0; i<c;i++)
		{
		    afficherPoids(poids,c);
			poids[0][i]=i;
			poids[1][i]=-1;
			poids[2][i]=0;
			precedent[0][i]=i;
			precedent[1][i]=-1;
		}
	poids[1][depart]=0; // puisque c'est le point de départ : sa distance à lui même est de 0
}

// stocke le chemin le plus court déterminé précédement et renvoi le nombre de routeurs empruntés

int fin(int precedent[2][100], int arrivee, int depart, int c, int liste[100])
{
	int actuel=arrivee;
	liste[0]=actuel;
	int compt=1;
	while(actuel != depart)
	{
	    int i;
		for(i=0; i<c; i++)
		{
			if(precedent[0][i]==actuel)
			{
				actuel=precedent[1][i];
				liste[compt]=actuel;
				compt++;
				break;
			}
		}
	}
	return compt;
}

// scan du graphe pour trouver le chemin le plus court
void chercherDijkstra(int graphe[100][100], int poids[3][100], int precedent[2][100], int depart, int arrivee, int c)
{
	int id;//=depart;
	int i;
	do
	{
		int min=100;
		afficherPoids(poids,c);
		for(i=0;i<c;i++)
		{
		    int p=poids[1][i];
		    //printf("poids:%d\n",p);
			if(p<min && p!=-1 && poids[2][i]==0)
			{
				min=poids[1][i];
				id=i;
			}
		}
		if(id!=arrivee) // si on a pas atteint l'arrivee
		{
			poids[2][id]=1; // marque
			int i;
			for(i=0;i<c;i++)
			{
				if(graphe[i][id]!=0 && poids[2][i]==0) // si le noeud-fils n'a pas encore été parcouru
				{
				    // si Poids(Noeud-père) + Poids(Liaison Noeud-père/Noeud-fils) < Poids(Noeud-fils)
                    // OU Poids(Noeud-fils) = -1
					if((poids[1][id]+graphe[i][id])<poids[1][i] || poids[1][i]==-1)
					{
						poids[1][i]=(poids[1][id]+graphe[i][id]);
						precedent[1][i]=id;
					}
				}
			}
		}
		_sleep(500);
	}
	while(id!=arrivee); // tant que le poids parcouru le plus faible n'est pas l'arrivee, on cherche
}

void Kruskal(struct Graphe g1){

// Définit une arrète
    struct Arrete{
       int sommetA;
       int sommetB;
       int poids;
       };


	//50 : arbitraire <=> nombre d'arc possible
	struct Arrete listeArc[50];
	int i,j;
	int compteur=0;
	int poidsTotal;
    int Parent[20];
    int origineA;
    int origineB;

    // Remplissage de la liste d'arrètes à partir d'une matrice
	for(i=0;i<g1.tailleInc;i++)
    {
        for(j=0;j<g1.tailleX;j++)
        {
        	if(g1.matInc[j][i]==1&&compteur==0){
                listeArc[i].sommetA=j;
                compteur++;
        	}
            if(g1.matInc[j][i]==1&&compteur>0){
            listeArc[i].sommetB=j;
            compteur++;
        	}
        }
        compteur=0;
        listeArc[i].poids=g1.matInc[g1.tailleX][i];
    }
    //////////////////////////////////////////////////////////


    // Tri à bulle de la liste en fonction du poids des arrètes
	int enOordre = 0;
    int tailleListe = g1.tailleInc;
    int temp;
    while(enOordre==0)
    {
        enOordre = 1;
        for(i=0 ; i < tailleListe-1 ; i++)
        {
            if(listeArc[i].poids > listeArc[i+1].poids)
            {
            	temp=listeArc[i].poids;
            	listeArc[i].poids=listeArc[i+1].poids;
            	listeArc[i+1].poids=temp;


                temp=listeArc[i].sommetB;
            	listeArc[i].sommetB=listeArc[i+1].sommetB;
            	listeArc[i+1].sommetB=temp;

                temp=listeArc[i].sommetA;
            	listeArc[i].sommetA=listeArc[i+1].sommetA;
            	listeArc[i+1].sommetA=temp;

                enOordre = 0;
            }
        }
        tailleListe--;
    }
///////////////////////////////////////////////////////////////////

    poidsTotal=0;
    for(i=0;i<g1.tailleX;i++){
        Parent[i]=i;
    }

        printf("Les arrèètes de l'arbre couvrant minimal sont :\n");
        for(i=0;i<g1.tailleInc;i++)
        {
            // recherche de cycle
           j = Parent[listeArc[i].sommetA];
           while(j!=Parent[j]){
                 j=Parent[j];
           }
           origineA=j;

           j = Parent[listeArc[i].sommetB];
           while(j != Parent[j])
           {
               j = Parent[j];
           }
           origineB=j;

           // En cas de non-cycle :
           if(origineA!=origineB)
           {
               Parent[origineB]=origineA;
               Parent[listeArc[i].sommetA]=origineA;
               Parent[listeArc[i].sommetB]=origineA;
               poidsTotal+=listeArc[i].poids;

                // Affichage des arrètes retenues :
               printf("[%d,%d] ",listeArc[i].sommetA,listeArc[i].sommetB);
           }
        }
    printf("\nLe poids minimal est : %d\n",poidsTotal);
}

void menu(struct Graphe g1)
{
    char nomGraphe[100];
    int type2;
    int choix;
    char choix2;

    printf("importer un graphe existant ou en creer un nouveau ?\n");
    printf("	1)importer\n");
    printf("	2)nouveau graphe\n");
    scanf("%d",&choix);

    switch (choix)
    {
    case 1:
        printf("nom du graphe à importer :\n");
        scanf("%s",nomGraphe);
        char fichier[100]="graphes/";
        strcat(fichier,nomGraphe);
        strcpy(nomGraphe,fichier);
        strcat(nomGraphe,".txt");
        g1 = getMatrice(nomGraphe);
        afficherMatrice(g1);
     break;
    case 2:
        printf("type à écrire ?\n");
        printf("	1)matrice Incidente\n");
        printf("	2)matrice Adjacente\n");
        scanf("%d",&type2);
        switch (type2)
        {
            case 1:
            g1=setGraphe(1);
            //printf(" x: %d, y: %d, inc: %d \n",g1.tailleX,g1.tailleY,g1.tailleInc);
            IncToAdj(&g1);
            break;
            case 2:
            g1=setGraphe(2);
            AdjToInc(&g1);
            break;
            default:
             printf("Erreur de saisie");
            break;
        }
        afficherMatrice(g1);

        printf("sauvegarder graphe ? y/n\n");
        scanf(" %c",&choix2);
        switch (choix2)
        {
            case 'y':
            saveGraphe(g1);
            break;
            case 'n':
            break;
            default:
             printf("Erreur de saisie");
            break;
        }

      break;
    default:
      printf("Erreur de saisie");
    break;
    }
}


