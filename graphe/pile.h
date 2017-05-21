#ifndef H_PILE
#define H_PILE

typedef struct ElementP ElementP;
struct ElementP
{
    int nombre;
    ElementP *suivant;
};

typedef struct Pile Pile;
struct Pile
{
    ElementP *premier;
};

Pile *initialiserP();
void empiler(Pile *pile, int nvNombre);
int depiler(Pile *pile);
void afficherPile(Pile *pile);

#endif
