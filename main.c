


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct matrice_demineur
{
    int tableau[16][16];
    int taille;
    int nb_de_mine;
    int compteur;
    int fonc;
    char drapeau;
};
typedef struct matrice_demineur grille;

void afficher_tableau(grille m) //initialisation de le grille
{
        int i,j;
        if(m.taille==9)     //si la taille est egale a 9
        {
            printf("    A B C D E F G H I\n");
            for(i=0;i<m.taille;i++)
            {
                printf("%02d|",i+1);
                for(j=0;j<m.taille;j++)
                {
                    printf(" %c","............012345678.;@"[m.tableau[i][j]]);
                }
                printf("\n");
            }
        }
        else
        {
            printf("    A B C D E F G H I J K L M N O P\n");
            for(i=0;i<16;i++)
            {
                printf("%02d|",i+1);
                for(j=0;j<m.taille;j++)
                {
                    printf(" %c","............012345678.;@"[m.tableau[i][j]]);
                }
                printf("\n");
            }
        }
}

void afficher_tableau_ouvert(grille m)
{
        int i,j;
        if(m.taille==9)
        {
            printf("    A B C D E F G H I\n");
            for(i=0;i<m.taille;i++)
            {
                printf("%02d|",i+1);
                for(j=0;j<m.taille;j++)
                {
                    printf(" %c","............012345678.;@"[m.tableau[i][j]+12]);
                }
                printf("\n");
            }
        }
        else
        {
            printf("    A B C D E F G H I J K L M N O P\n");
            for(i=0;i<16;i++)
            {
                printf("%02d|",i+1);
                for(j=0;j<m.taille;j++)
                {
                    printf(" %c","............012345678.;@"[m.tableau[i][j]+12]);
                }
                printf("\n");
            }
        }
}

void choix(grille *m)
{
    int a;
    do
    {
        printf("faite votre choix : \n 1-Debutant\n 2-expert\n");
        scanf("%d",&a);
    }
    while(a!=1 && a!=2);
    if(a==1) m->taille=9,m->nb_de_mine=10;
    else     m->taille=16,m->nb_de_mine=40;
    printf("vous avez choisi la %d\n\n",a);
    printf("         A vous de jouer\n\n");
}

void bombe(grille *m)
{
    int i,j,c=m->taille*m->taille,b=m->nb_de_mine;

    for(i=0;i<m->taille;i++)
    for(j=0;j<m->taille;j++)
    {
        if(rand()%c<b) m->tableau[i][j]=10, c--,b--;
        else           m->tableau[i][j]= 9, c--;
    }
}

void adjacent_bombe(grille *m)
{
	int i,j,x,z,cpt=0;
	for(i=0;i<m->taille;i++)
    for(j=0;j<m->taille;j++)
    {
    	if(m->tableau[i][j]==9)
    	{
    	    for(x=-1;x<2;x++)
            {
                for(z=-1;z<2;z++)
    			{
    				if(j+z>=0 && i+x>=0 && j+z<16 && i+x<16 && m->tableau[i+x][j+z]==10) cpt++;
				}
            }
			m->tableau[i][j]=cpt;
			cpt=0;
	    }
	}
}

void jeu(int *i, int *j, int t, grille *m)
{
    char cc;
    if(t==9)
    while(1)
    {
        getchar();
        printf("\nouvrez une case 'r' ou '@'(pour drapeau) devant les coordonnees :");
        cc=getchar();
        if(cc=='@')
        {
            m->drapeau='@';
        }
        else
        {
            m->drapeau='r';
        }
        printf("\nouvrez une case :");
        cc=getchar();
        cc|=32;
        if(cc<'a' || cc>'i') continue;
        *j=cc-'a';
        cc=getchar();
        if(cc<'1' || cc>'9') continue;
        *i=cc-'1';
        return;
    }
    if(t==16)
    while(1)
    {
        getchar();
        printf("\nouvrez une case 'r' ou '@'(pour drapeau) devant les coordonnees :");
        cc=getchar();
        if(cc=='@')
        {
            m->drapeau='@';
        }
        else
        {
            m->drapeau='r';
        }
        printf("\nouvrez une case :");
        cc=getchar();
        cc|=32;
        if(cc<'a' || cc>'p') continue;
        *j=cc-'a';
        cc=getchar();
        if(cc<'1' || cc>'9') continue;
        *i=cc-'1';
        cc=getchar();
        if(cc>='0' && cc<='6'){
            *i=((*i+1)*10)+cc-'0'-1;
        }
        return;
    }
}

void jeu_ordi(int *i, int *j, int t)
{
        printf("\nouvrir :");
        *j=rand()%t;
        *i=rand()%t;
        return;
}

void choix_jeu(grille *m)
{
    int a;
    do
    {
        printf("qui joue? \n 1- Humain\n 2-ordinateur\n");
        scanf("%d",&a);
    }
    while(a!=1 && a!=2);
    m->fonc=a;
}

void devoile(int i2,int j2, grille*m)
{
    m->tableau[i2][j2]+=12;
    int i,j;
    if(m->drapeau=='@')
    {
        m->tableau[i2][j2]=23;
    }
    else
    if(m->tableau[i2][j2]==12)
    for(i=i2-1;i<i2+2;i++) if(i>=0 && i<m->taille)
    for(j=j2-1;j<j2+2;j++) if(j>=0 && j<m->taille)
    if(m->tableau[i][j]<12)
    {
        m->compteur++;
        devoile(i,j,m);
    }
}

int main()
{
    grille m;
    m.compteur=0;
    srand(time(NULL));
    choix(&m);
    choix_jeu(&m);
    bombe(&m);
    adjacent_bombe(&m);
    printf("\n\n");
    while(1)
    {
            int i2=-1,j2=-1;
            afficher_tableau(m);
            if(m.fonc==1)
            {
                jeu(&i2,&j2,m.taille,&m);
            }
            else
            {
                jeu_ordi(&i2,&j2,m.taille);
            }
            if(m.tableau[i2][j2]>=12)
            {
                printf("vous avez deja ouvert cette case\n\n");
                continue;
            }

            devoile(i2,j2,&m);
            m.compteur++;
            printf("i=%d,j=%d c=%d\n",i2,j2,m.compteur);
            if(m.compteur+m.nb_de_mine==m.taille*m.taille)
            {
                printf("Toutes les cases ont etait ouverte, vous avez gagner\n");
            }
            if(m.tableau[i2][j2]==22)
            {
                printf("vous avez perdu\n\n");
                afficher_tableau(m);
                exit(0);
            }
    }
}
