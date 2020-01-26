#ifndef DOMINO_H
#define DOMINO_H


//ce fichier contient les différentes structures crées pour le projet

// on crée la structure de domino (un domino est identifié par un tableau de deux valeurs)

struct domino {
    int valeurs [2];
};

// on crée la structure de table (c'est à dire le jeu du domino)
// le jeu est identifié par deux valeurs (les valeurs extremes) et par la liste

struct table {
    struct domino **dominos;
    struct domino *premier, *dernier;
    int total;
};


#endif // DOMINO_H
