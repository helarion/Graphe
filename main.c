#include <stdio.h>
#include <string.h>
#include "file.h"
#include "file.c"

#define TAILLE_MAX 1000

struct Matrice
{
	int tailleX;
	int tailleY;

	int tailleInc;

	int matAdj[100][100]; // valeurs
	int matInc[100][100]; // booleene
};

void AdjToInc(struct Matrice *m){
	int i,j,tailleX,tailleY;
	int c=0;

    tailleX=m->tailleX;
    tailleY=m->tailleY;

    //printf("test 1\n");

    for(i=0;i<tailleX;i++)
    {
        for(j=i+1;j<tailleY;j++)
        {
        	if(m->matAdj[i][j]!=0) c++;
        }
    }

    m->tailleInc=c;

    for(i=0;i<tailleX;i++)
    {
    	c=0;
        for(j=i+1;j<tailleY;j++)
        {
        	if(m->matAdj[i][j]!=0)
        	{
        		m->matInc[i][c]=1;
        		m->matInc[j][c]=1;
        		m->matInc[tailleX][c]=m->matAdj[i][j];
        		c++;
        	}
        }
    }
   
}

void IncToAdj(struct Matrice *m){
	int i,j,tailleX,tailleY;
	int poids;

    tailleX=m->tailleInc-1;
    tailleY=m->tailleX;

    for(i=0;i<tailleX+1;i++)
    {
    	poids=m->matInc[m->tailleInc+1][i];

        for(j=0;j<m->tailleInc;j++)
        {

        	if(m->matInc[j][i]!=0)
        	{
        		//printf("poids : %d i: %d j: %d \n",poids,i,j);
        		m->matAdj[j][i]=poids;
        		m->matAdj[i][j]=poids;
        	}
        }
    }

    m->tailleY=tailleY;
   
}

void afficherMatrice(struct Matrice m)
{
    int i;
    int j;

    int compteur=0;

    printf("x: %d,y: %d, inc: %d \n",m.tailleX,m.tailleY,m.tailleInc);


    printf("Matrice d'adjacence:\n");
	for(i=0;i<m.tailleX;i++)
	{
		for(j=0;j<m.tailleY;j++)
		{
			printf("%d",m.matAdj[i][j]);
			if(j!=m.tailleY-1)
			{
				printf("-");	
			}
		}
		printf("\n");
	}

	printf("Matrice d'incidence:\n");

	printf("arcs --> \n");
	for(i=0;i<m.tailleX+1;i++)
	{
		for(j=0;j<m.tailleInc;j++)
		{
			printf("%d",m.matInc[i][j]);
			if(j!=m.tailleInc-1)
			{
				printf("-");	
			}
		}
		printf("\n");
	}
	
}

struct Matrice getMatriceAdj(char* nomFichier)
{
	FILE *fp;
	fp = fopen(nomFichier, "r");

	if (fp == NULL) {
	  fprintf(stderr, "Impossible d'ouvrir le fichier!\n");
	  return;
	}

	struct Matrice m;
    int c;
    int compteur=0;

    int i=0;
    int j=0;

    fscanf(fp,"%d",&c);
    m.tailleX=c;
    fscanf(fp,"%d",&c);
    m.tailleY=c;

    for(i=0;i<m.tailleX;i++)
    {
        for(j=0;j<m.tailleY;j++)
        {
            fscanf(fp,"%d",&c);
            m.matAdj[i][j]=c;
        }
    }
    fclose(fp);

    AdjToInc(&m);

	return m;
}

struct Matrice getMatriceInc(char* nomFichier)
{
	FILE *fp;
	fp = fopen(nomFichier, "r");

	if (fp == NULL) {
	  fprintf(stderr, "Impossible d'ouvrir le fichier!\n");
	  return;
	}

	struct Matrice m;
    int c;
    int compteur=0;

    int i=0;
    int j=0;

    fscanf(fp,"%d",&c);
    m.tailleInc=c;
    fscanf(fp,"%d",&c);
    m.tailleX=c-1;

    for(i=0;i<m.tailleX+1;i++)
    {
        for(j=0;j<m.tailleInc;j++)
        {
            fscanf(fp,"%d",&c);
            //printf("c:%d \n",c);
            m.matInc[i][j]=c;
        }
    }

    fclose(fp);

    IncToAdj(&m);

	return m;
}

void saveGraphe(struct Matrice m)
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
    sprintf(write, "%d", m.tailleX);
    fprintf(f,"%s",write);
    fprintf(f," ");
    sprintf(write,"%d", m.tailleY);
    fprintf(f,"%s",write);
    fprintf(f,"\n");
    for(i=0;i<m.tailleX;i++)
	    {
	        for(j=0;j<m.tailleY;j++)
	        {
	        	sprintf(write, "%d", m.matAdj[i][j]);
	        	if(j<m.tailleY-1) strcat(write," ");
	        	fprintf(f,"%s",write);
	        }
	        if(i<m.tailleX-1) fprintf(f,"\n");
	    }
    fclose(f);
}

struct Matrice setGraphe(int type)
{

    int tailleX;
    int tailleY;
    struct Matrice m;

    printf("Entrez la taille x de la matrice: /| \n");
    scanf("%d",&tailleX);
    if(type==2){
    	tailleY=tailleX;
    }else{
    printf("Entrez la taille y de la matrice: --> \n");
    scanf("%d",&tailleY);
	}

    m.tailleX=tailleX;
    m.tailleY=tailleY;

    int i,j,val;
    for(i=0;i<tailleX;i++)
    {
        for(j=0;j<tailleY;j++)
        {
            printf("[%d][%d]:",i,j);
            scanf("%d",&val);
            if(type==1){
            	m.tailleInc=tailleY;
            	m.matInc[i][j]=val;
            }
            if(type==2){
            	m.matAdj[i][j]=val;	
            }

        }
    }
    return m;
}

void parcoursLargeur(struct Matrice m){

	File *maFile = initialiser();
	int i;
	int j;
/*
	for(i=0;i<m.tailleX;i++)
	{
		for(j=0;j<m.tailleY;j++)
		{
		 if(m.matAdj[i][j]!=0){
		 	enfiler(j);
		 	printf("%d",mafile[0]);
		 }

		}
	}*/


	enfiler(maFile, 4);
    enfiler(maFile, 8);
    enfiler(maFile, 15);

    printf("premier element  :%d",getPremierElement(maFile));
    printf("\nEtat de la file :\n");
    afficherFile(maFile);

    printf("\nJe defile %d\n", defiler(maFile));
    printf("Je defile %d\n", defiler(maFile));

    printf("\nEtat de la file :\n");
    afficherFile(maFile);


}

int main()
{
struct Matrice m1;

/*
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

	printf("quel type de matrice ?\n");
	printf("	1)matrice Incidente\n");
	printf("	2)matrice Adjacente\n");
	scanf("%d",&type1);

	switch (type1)
	{
	case 1:
	  m1 =getMatriceInc(nomGraphe);
	  break;
	case 2:
	  m1 =getMatriceAdj(nomGraphe);
	  break;
	default:
	  printf("Erreur de saisie");
	break;
	}

	afficherMatrice(m1);
 break;
case 2:

	printf("type à écrire ?\n");
	printf("	1)matrice Incidente\n");
	printf("	2)matrice Adjacente\n");
	scanf("%d",&type2);
	switch (type2)
	{
		case 1:
		m1=setGraphe(1);
		//printf(" x: %d, y: %d, inc: %d \n",m1.tailleX,m1.tailleY,m1.tailleInc);
		IncToAdj(&m1);
		break;
		case 2:
		m1=setGraphe(2);
		AdjToInc(&m1);
		break;
		default:
		 printf("Erreur de saisie");
		break;
	}
	afficherMatrice(m1);

	printf("sauvegarder graphe ? y/n\n");
	scanf(" %c",&choix2);
	switch (choix2)
	{
		case 'y':
		saveGraphe(m1);
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

*/

//m1=getMatriceAdj("matrice.txt");
//afficherMatrice(m1);

parcoursLargeur(m1);

return 0;
}
