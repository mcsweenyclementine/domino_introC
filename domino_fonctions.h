#ifndef DOMINO_FONCTIONS_H
#define DOMINO_FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <domino.h>

// ce projet contient les différentes fonctions utilisées pour le projet


//initialisation
struct table *M = NULL;
int stock[28]; // table de 28 éléments dans laquelle on va placer les dominos

// fonction qui crée un nouvel espace (utilise lorsque le joeur doit piocher)
struct table *nouvelle_espace() {
    struct table *temp=NULL;
    temp=calloc(1,sizeof(struct table)); //inicializada en 0
    return temp;
}


// fonction qui enelève un domino (idenitifié par l'indice) des dominos du joueur
struct domino *supprimer_indice(struct table *m, int indice) {
    int i = indice;
    struct domino *k=NULL;
    k=m->dominos[indice];
    while(i<m->total-1) {
       m->dominos[i]=m->dominos[i+1];
       i++;
    }
    m->dominos[i]=NULL;
    m->dominos=realloc(m->dominos,sizeof(struct domino*)*(m->total-1)); // on libére l'espace par le domino supprimé
    m->total--;
    return k;

}



// fonction qui place sur un élement table un domino

void distribuer_domino(struct table *m,struct domino *f){
if(m) {
    if(f) {
        m->dominos=realloc(m->dominos,sizeof(struct domino *) *(m->total+1));  //on crée de la mémoire pour y placer un domino (ex domino pioché par 1 joueur)
        m->dominos[m->total]=f;
        m->total++;
        m->premier=m->dominos[0];
        m->dernier=m->dominos[m->total-1];
    }
    else {
        printf("erreur dans le domino");
}
}
}


//fonction qui affiche un domino

void afficher_domino(struct domino *f){
    printf("domino: [%i|%i]\n",f->valeurs[0],f->valeurs[1]);
}



// fonction qui affiche le jeu (ie: la table)
void afficher_table(struct table *m){
int i=0;
while (i<m->total){
    printf("[%d|%d]",m->dominos[i]->valeurs[0],m->dominos[i]->valeurs[1]);
    i++;
}
printf("\n");
}

void distribuer_domino_deux(struct table *m,struct domino *f,bool position) {
    if(m) {
        if(f){
            m->dominos=realloc(m->dominos,sizeof(struct domino *)*(m->total+1));
            if(position) {
                int i=m->total;
                while(i>0){
                    m->dominos[i]=m->dominos[i-1];
                    i--;
                }
                m->dominos[0]=f;
            }
            else {
                m->dominos[m->total]=f;
            }
            m->total++;
            m->premier=m->dominos[0];
            m->dernier=m->dominos[m->total-1];
        }
        else {
            printf("erreur dans le domino"); // l'allocation de la mémoire s'est mal déroulée
        }
    }
    else {
        printf("erreur dans le domino");  // l'allocation de la mémoire s'est mal déroulée
    }
}


// la fonction suivante permet de rechercher une valeur dans un jeu de dominos

int recherche_valeur(struct table *m,int valeur){
    int v=-1;
    struct domino *actuel=NULL;
    bool c=false;
    int i=0;
    while (i<m->total) {
        actuel=m->dominos[i];
        if(actuel->valeurs[0] == valeur||actuel->valeurs[1]==valeur){
            printf("%d",i);
            printf("\n");
            v=i;
            c=true;
        }
        i++;
    }
    return v;
}


// la fonction suivante permet de rechercher un double (si jamais il existe) dans un jeu de dominos

int recherche_double(struct table *m,int valeur) {
    int v=-1;
    struct domino *actuel=NULL;
    bool c =false;
    int i=0;
    while(!c  && i<m->total) {
        actuel = m->dominos[i];
        if(actuel->valeurs[0] == valeur && actuel->valeurs[1]==valeur) {
            v=i;
            c=true;
        }
        i++;
    }
    return v;
}

// la fonction suivante permet de créer un domino dont les deux valeurs sont a et b

struct domino *creer_domino(int a,int b) {
    struct domino *nouveau=calloc(sizeof(struct domino),1);
    nouveau->valeurs[0]=a;
    nouveau->valeurs[1]=b;
    return nouveau;
}


// la fonction suivant permet de regarder les valeurs extremes du jeu (ie 5 et 4 si jeu=[4|6][6|3][3|5])
struct domino *regarder_valeurs(struct table *m) {
    struct domino *f = malloc(sizeof(struct domino));
    f->valeurs[0]=m->premier->valeurs[0];
    f->valeurs[1]=m->dernier->valeurs[1];
    return f;

}


struct domino *echanger_domino(struct domino *f) {
    int temp=f->valeurs[0];
    f->valeurs[0]=f->valeurs[1];
    f->valeurs[1]=temp;

   return f;
}

// la fonction dis_alea permet de distribuer aléoirement les dominos en cherchant aléatoirement ceux du stock créé + haut qui n'ont pas encore
// été distribué
void dis_alea() {
    int i=0,valeur_aleatoire;
    int arreglo_no_repetidos[28];
    memset(&arreglo_no_repetidos,0,sizeof(int)*28);
    srand(time NULL);
    while(i<28) {
        valeur_aleatoire=rand()%28;
        if(arreglo_no_repetidos[valeur_aleatoire]==0){
            stock[i]=valeur_aleatoire;
            i++;
            arreglo_no_repetidos[valeur_aleatoire]=1;
        }
    }

}



#endif // DOMINO_FONCTIONS_H
