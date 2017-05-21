#include <stdio.h>
#include <string.h>
#include "file.h"
#include "file.c"
#include "pile.h"
#include "pile.c"

#define ADJACENCE 1
#define INCIDENCE 2
#define TAILLE_MAX 1000

File *maFile;
Pile *maPile;
int compteurSommetsPasses=0;
int SommetsPasses[50];

int sommetsMarques[50];
int sommetsvisites[50];
int compteurMarque=0;
int compteurVisite=0;

struct Graphe
{
	int tailleX;
	int tailleY;

	int tailleInc;

	int matAdj[100][100]; // valeurs
	int matInc[100][100]; // booleene
};

void AdjToInc(struct Graphe *g){
	int i,j,tailleX,tailleY;
	int c=0;

    tailleX=g->tailleX;
    tailleY=g->tailleY;

    printf("x:%d y:%d\n",tailleX, tailleY);

    for(i=0;i<tailleX;i++)
    {
        for(j=i+1;j<tailleY;j++)
        {
        	if(g->matAdj[i][j]!=0) c++;
        }
    }

    g->tailleInc=c;
    c=0;

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

void IncToAdj(struct Graphe *g){
    int i,j,tailleX,tailleY;
    int poids;

    g->tailleY=g->tailleX;


    printf("données : \n");
    printf("g.TailleX :%d \n",g->tailleX);
    printf("g.TailleY :%d \n",g->tailleY);
    printf("g.tailleInc :%d\n",g->tailleInc);



    for(i=0;i<g->tailleInc;i++)
    {
        poids=g->matInc[g->tailleX][i];
        //printf(" poids colonne %d =%d \n",i,poids);

        for(j=0;j<g->tailleX;j++)
        {
            if(g->matInc[j][i]!=0)
            {
                //printf("poids : %d i: %d j: %d \n",poids,i,j);
                g->matAdj[j][i]=poids;
                g->matAdj[i][j]=poids;
            }
        }
    }
}

void afficherMatrice(struct Graphe g)
{
    int i;
    int j;

    int compteur=0;

    printf("x: %d,y: %d, inc: %d \n",g.tailleX,g.tailleY,g.tailleInc);

    printf("données affichage : \n");
	printf("g.TailleX :%d \n",g.tailleX);
	printf("g.TailleY :%d \n",g.tailleY);
	printf("g.tailleInc :%d\n",g.tailleInc);


    printf("Matrice d'adjacence:\n");
	for(i=0;i<g.tailleX;i++)
	{
		for(j=0;j<g.tailleY;j++)
		{
			printf("%d",g.matAdj[i][j]);
			if(j!=g.tailleY-1)
			{
				printf("-");
			}
		}
		printf("\n");
	}

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
	  return;
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
        IncToAdj(&g);
    }
    fclose(fp);
	return g;
}

struct Graphe getMatriceInc(char* nomFichier)
{
	FILE *fp;
	fp = fopen(nomFichier, "r");

	if (fp == NULL) {
	  fprintf(stderr, "Impossible d'ouvrir le fichier!\n");
	  return;
	}

	struct Graphe g;
    int c;
    int compteur=0;

    int i=0;
    int j=0;

    fscanf(fp,"%d",&c);
    g.tailleInc=c;
    fscanf(fp,"%d",&c);
    g.tailleX=c-1;

    for(i=0;i<g.tailleX+1;i++)
    {
        for(j=0;j<g.tailleInc;j++)
        {
            fscanf(fp,"%d",&c);
            //printf("c:%d \n",c);
            g.matInc[i][j]=c;
        }
    }

    fclose(fp);

    IncToAdj(&g);

	return g;
}

void saveGraphe(struct Graphe g)
{
    FILE *f;
    char nomGraphe [50];
    char chemin[50]="./";

    printf("Entrez le nom de votre graphe:");
    scanf("%s",nomGraphe);
    strcat(chemin,nomGraphe);
    strcat(chemin,".txt");

    f=fopen(chemin,"w");
    int i,j;

    if(f == NULL) //if file does not exist, create it
    {
        freopen(chemin, "w", f);
    }
    char* write;
    sprintf(write, "%d", g.tailleX);
    fprintf(f,"%s",write);
    fprintf(f," ");
    sprintf(write,"%d", g.tailleY);
    fprintf(f,"%s",write);
    fprintf(f,"\n");
    for(i=0;i<g.tailleX;i++)
	    {
	        for(j=0;j<g.tailleY;j++)
	        {
	        	sprintf(write, "%d", g.matAdj[i][j]);
	        	if(j<g.tailleY-1) strcat(write," ");
	        	fprintf(f,"%s",write);
	        }
	        if(i<g.tailleX-1) fprintf(f,"\n");
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

void RechercheVoisins(int depart,struct Graphe g){

	int i=0;
	int j=0;

	int flag=0;

	for(i=0;i<g.tailleY;i++)
	{
		if(g.matAdj[depart][i]!=0)
			{
				//printf("%d est voisin avec %d \n",depart,i);
				for(j=0;j<50;j++){
					if(i==SommetsPasses[j]){
						//printf("%d est deja passé \n", i);
						flag=1;
						break;
					}
				}
				if(flag!=1){
						enfiler(maFile,i);
						//printf("ajout de : %d en sommet passé \n",depart);
						SommetsPasses[compteurSommetsPasses]=depart;

					}
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
	int j=0;
	int parcours[50];

	int compteur=0;
	enfiler(maFile,0);
	int flag=0;


	while(estVide(maFile)!=0){

		RechercheVoisins(getPremierElement(maFile),g);
		parcours[compteur]=getPremierElement(maFile);
		compteur++;
		defiler(maFile);
		//afficherFile(maFile);
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
	int k=0;
	int flag=0;
	int flag2=0;
	int compteurSucesseurs=0;
	int fin;
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
				if(i==sommetsvisites[i]){
					printf("voisin déjà visité, next :\n");
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
		//printf("premier element de la pile : %d \n",getPremierElementP(maPile));
		RechercheVoisinsProfondeur(getPremierElementP(maPile),g);
		/*
		printf("Pile : \n");
		printf("___debut ___\n");
		afficherPile(maPile);
		printf("___fin ___\n");
		printf("sommets marqués :  sommets visités :\n");
		for(j=0;j<7;j++){
			printf("%d                  %d\n",sommetsMarques[j],sommetsvisites[j]);
		}*/

	}

	//for(j=0;j<10;j++){
	j=0;
	while(sommetsMarques[j]!=(-1)){
		printf("%d->",sommetsMarques[j]);
		j++;
	}

	printf("\n");
}

void menu(struct Graphe g1)
{
    char nomGraphe[100];
    int type1;
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

int main()
{
    struct Graphe g1;
    g1=getMatrice("matriceIncidence.txt");
    //IncToAdj(&g1);
    afficherMatrice(g1);
    return 0;
}
