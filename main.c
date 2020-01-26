#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <domino.h>
#include <domino_fonctions.h>


// le proket contient trois fichier
//le fichier domino.h contient les différentes structures créés
//le fichier domino_fonctions.h contient les différentes fonctions créés
//la fonction main.c contient l'execution du jeu

//le joueur 2 est l'ordinateur
//le joueur 1 est uner personne
//le joueur 1 pioche sans qu 'on lui demande s'il ne peut pas faire autrement
//dans ce cas on place le domino qu'il pioché à sa place
//la personne qui joue pour le joueur 1 n'a pas la main sur le premier tour (placement du premier domino)

//chaque joueur recoit 7 dominos
//le stock initial de dominos est composé de 28 dominos

//pour modéliser ce jeu de domino nous avons utilisé des pointeurs

//on tire au hazard le joueur qui commence la partie; celui-ci devra jouer son + grand double
//si le joueur n'a pas de double il laisse le tour à l'autre joueur
// si ce dernier joueur n'a lui même pas de double alors la partie s'arrête

int main() {
    printf("Vous êtes le joueur 1\n");
    struct domino *k;
    struct domino *dominos=NULL;
    int compteur=0;
    int i=0, j=0;
    while(i<=6){
        j=0;
        while(j<=i) {

            dominos=realloc(dominos,(compteur+1)*sizeof(struct domino)); // création de mémoire pour placer un domino
            k = creer_domino(i,j);
            dominos[compteur].valeurs[0]=i;
            dominos[compteur].valeurs[1]=j;

            compteur++;
            j++;
        }
        i++;
    }
    dis_alea();
    i=0;
    while(i<compteur){
        i++;
    }

    struct table *joueur1=NULL;
    struct table *joueur2=NULL;

    joueur1=nouvelle_espace();
    joueur2=nouvelle_espace();
    struct domino* aux=NULL;
    printf("\n");


    //on distribue les dominos aux deux joueurs

    printf("distribution des dominos au joueur 1\n");
    i=0;
    while(i<7) {     // chacun des 2 joueurs reçoit 7 dominos
        distribuer_domino(joueur1,&dominos[stock[i]]);
        afficher_domino(&dominos[stock[i]]);
        i++;
    }
    printf("distribution des dominos au joueur 2\n");
    while (i<14) {
        distribuer_domino(joueur2,&dominos[stock[i]]);
        afficher_domino(&dominos[stock[i]]);
        i++;
    }

    int tour;
    tour=rand()%2;
    struct table* joueur_actuel;
    if (tour%2==0){
        joueur_actuel=joueur1;
    }
    else {
        joueur_actuel=joueur2;
    }
    printf("Le joueur %i commence \n",tour+1);
    int indice=-1;
    int recherche=6;
    printf("recherche de double\n");
    while(indice==-1 && recherche>=0) {
        indice=recherche_double(joueur_actuel,recherche);
        //printf("recherche du double %i: resultado %i\n",recherche,indice);
        recherche--;
    }

    if(indice !=-1) {
        aux=supprimer_indice(joueur_actuel,indice);
    }
    else {
        tour++;
        printf("changement de joueur %i\n",(tour %2)+1);
        if (tour%2==0){
            joueur_actuel=joueur1;
        }
        else {
            joueur_actuel=joueur2;
        }
        //indice=-1;
        recherche=6;
        while(indice==-1 && recherche>=0) {
            indice=recherche_double(joueur_actuel,recherche);
            //printf("recherche de double %i:resultat %i\n",recherche, indice);
            recherche--;
        }
        if(indice!=-1) {
            aux=supprimer_indice(joueur_actuel,indice);
        }
        else {
            printf("il n'y pas de double distribué: personne ne gagne\n");

        }
    }
    M = nouvelle_espace();
    distribuer_domino(M,aux);
    printf("le joueur %i a joué\n",(tour%2)+1);
    printf("domino joué: \n");
    afficher_domino(aux);
    printf("table actuelle: \n");
    afficher_table(M);

    bool pas_de_gagnant=true;
    bool position;
    bool no_domino;
    no_domino=true;


    while(pas_de_gagnant) {
        tour++;
        printf("tour du joueur %i\n",(tour%2)+1);
        if (tour%2==0){
            joueur_actuel=joueur1;
        }
        else {
            joueur_actuel=joueur2;
        }

        aux=regarder_valeurs(M);
        do {
            indice=recherche_valeur(joueur_actuel,aux->valeurs[0]);
            if(indice==-1) {
                no_domino=true;
                indice=recherche_valeur(joueur_actuel,aux->valeurs[1]);
                if(indice==-1) {
                    no_domino=true;
                }

                else {

                    recherche=aux->valeurs[1];
                    no_domino=false;
                    position=false;
                }
            }

            else {
                recherche = aux->valeurs[0];
                no_domino=false;
                position=true;

                if (tour%2==0){

                    printf("la table: \n");
                    afficher_table(M);
                    printf("vos dominos \n");
                    afficher_table(joueur_actuel);
                    printf("\n");

                    int x=0;
                    printf("domino ?\n");
                    scanf("%d",&x);
                    struct domino*d=joueur1->dominos[x];

                    int dg=d->valeurs[0];
                    int dt=d->valeurs[1];
                    int tg=aux->valeurs[0];
                    int td=aux->valeurs[1];



                    while ((dg!=tg) && (dg!=td) && (dt!=tg) && (dt!=td)) {
                    printf("IMPOSSIBLE !\n");

                    printf("table\n");
                    afficher_table(M);
                    printf("\n");

                    printf("vos dominos\n");
                    afficher_table(joueur1);
                    printf("\n");

                    int x=0;
                    printf("domino ?\n");
                    scanf("%d",&x);
                    printf("domino choisi: \n");
                    struct domino*d=joueur1->dominos[x];
                    afficher_domino(d);
                    printf("\n");

                    }

                    indice=x;


                }
            }
            if (no_domino) {

                if(i<28) {
                    printf("le joueur doit piocher\n");
                    afficher_domino(&dominos[stock[i]]);
                    distribuer_domino(joueur_actuel,&dominos[stock[i]]);
                    i++;
                }

            else {
                printf("le joueur %i perd\n",(tour%2)+1);
                exit(0);
            }

            }
        }while (no_domino);
    free(aux);
    aux=supprimer_indice(joueur_actuel,indice);
    printf("le joueur joue le ");
    afficher_domino(aux);
    printf("\n");

    if(position) {
        if(M->premier->valeurs[0]!=aux->valeurs[1]) {
            echanger_domino(aux);
        }
    }

    distribuer_domino_deux(M,aux,position);
    printf("table actuelle: ");
    afficher_table(M);
    if(joueur1->total==0) {
        pas_de_gagnant=false;
        printf("Vous avez gagné :) !!!\n");
    }
    else if(joueur2->total==0) {
        pas_de_gagnant=false;
        printf("Vous avez perdu :( !!!\n");
    }
}


    return 0;
}



