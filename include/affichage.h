#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "types.h"

// Prototypes des fonctions à implémenter par le Membre 2 dans affichage.c
void init_affichage(void);
void afficher_grille(const Simulation *sim);
void afficher_legende(void);
void afficher_statistiques(const Simulation *sim);
void rafraichir_ecran(const Simulation *sim);
void traiter_entrees_clavier(Simulation *sim);

#endif // AFFICHAGE_H