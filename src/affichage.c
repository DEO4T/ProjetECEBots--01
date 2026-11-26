#include <stdio.h>
#include <conio.h>
#include "affichage.h"
#include "simulation.h"
#include "affichage_console.h"

void init_affichage(void) {
    // [LAISSE VIDE POUR LE MEMBRE 2]
    // TODO : Appeler clrscr() et hide_cursor() de affichage_console.h
}

void afficher_grille(const Simulation *sim) {
    // [LAISSE VIDE POUR LE MEMBRE 2]
    // TODO : Dessiner la grille (LIGNES x COLONNES), le drone et le robot avec gotoxy() et text_color()
    (void)sim;
}

void afficher_legende(void) {
    // [LAISSE VIDE POUR LE MEMBRE 2]
    // TODO : Afficher la légende des symboles et des touches
}

void afficher_statistiques(const Simulation *sim) {
    // [LAISSE VIDE POUR LE MEMBRE 2]
    // TODO : Afficher la charge du robot et les infos de simulation
    (void)sim;
}

void rafraichir_ecran(const Simulation *sim) {
    afficher_grille(sim);
    afficher_statistiques(sim);
    afficher_legende();
}

void traiter_entrees_clavier(Simulation *sim) {
    // [LAISSE VIDE POUR LE MEMBRE 2]
    // TODO : Utiliser _kbhit() et _getch() pour appeler deplacer_drone(), deplacer_robot() et quitter (Echap)
    (void)sim;
}