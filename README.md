<div align="center">

# 🌿 EcoBots — Surveillance & Nettoyage d'une Réserve Naturelle

**Projet Informatique 1 (ING1) — ECE Paris**  
*Simulation en langage C de détection et collecte autonome de déchets par drone et robot tout-terrain.*

![Langage](https://img.shields.io/badge/Langage-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Plateforme](https://img.shields.io/badge/Plateforme-Windows%20Console-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Statut](https://img.shields.io/badge/Statut-En%20développement-success?style=for-the-badge)

</div>

---

## 📖 Présentation du projet

Dans une réserve naturelle fragile parsemée d'obstacles naturels (forêts denses, falaises, plans d'eau), l'intervention humaine est difficile. **EcoBots** simule le déploiement coordonné d'un **drone de surveillance** et d'un **robot de collecte** afin de repérer et recycler les déchets abandonnés par les visiteurs.

### 🎯 Fonctionnalités principales
* **Terrain dynamique :** Grille rectangulaire comprenant zones libres, obstacles infranchissables et centres de collecte.
* **Apparition aléatoire :** Génération continue de déchets tout au long de la simulation.
* **Reconnaissance aérienne (Drone) :** Détection des déchets cachés dans un rayon de **8 cases voisines** autour du drone.
* **Collecte terrestre (Robot) :** Récupération des déchets préalablement localisés et transport vers un centre de tri.
* **Temps réel non bloquant :** Pilotage fluide au clavier via `<conio.h>` et affichage console optimisé sans scintillement (`affichage_console.h`).

---

## 🎮 Commandes en jeu

| Entité / Action | Touches | Description |
| :--- | :---: | :--- |
| **🚁 Drone de surveillance** | `Z` `Q` `S` `D` | Déplacement aérien (Haut, Gauche, Bas, Droite) et scan automatique des 8 cases adjacentes. |
| **🤖 Robot de collecte** | `↑` `←` `↓` `→` | Déplacement au sol, ramassage des déchets détectés et dépôt au centre de collecte. |
| **🚪 Quitter** | `Échap` (`ESC`) | Arrête proprement la simulation. |

---

## 🏗️ Architecture du projet

Le code respecte une **séparation stricte entre le moteur de simulation (logique pure) et l'IHM (affichage et entrées clavier)** :

```text
EcoBots/
├── README.md                  # Présentation et documentation du dépôt
├── .gitignore                 # Exclusions Git (*.exe, *.o, bin/, obj/)
├── include/                   # Fichiers d'en-tête (.h)
│   ├── types.h                # Structures de données (Grille, Drone, Robot, Stats, Simulation)
│   ├── simulation.h           # Prototypes du moteur de simulation
│   ├── affichage.h            # Prototypes de l'interface console et du clavier
│   └── affichage_console.h    # Bibliothèque console fournie (gotoligcol, color, etc.)
└── src/                       # Fichiers sources (.c)
    ├── main.c                 # Boucle principale et synchronisation
    ├── simulation.c           # Règles métier (sans aucun printf ni conio.h)
    └── affichage.c            # Rendu graphique console et écoute clavier
```

---

## 🚀 Compilation et exécution

### Prérequis
* Système d'exploitation **Windows** (requis pour `<conio.h>` et `affichage_console.h`).
* Compilateur C (**GCC / MinGW** via VS Code ou Code::Blocks).

### Compiler depuis le terminal
Placez-vous à la racine du dépôt et exécutez :

```bash
gcc -Wall -Wextra -Iinclude src/main.c src/simulation.c src/affichage.c -o EcoBots.exe
```

### Lancer la simulation
```bash
./EcoBots.exe
```

---

## ✨ Extensions intégrées

En complément du cahier des charges de base, le projet intègre les évolutions suivantes :
1. **🔋 Gestion énergétique :** Suivi du niveau de batterie du drone et du robot avec déploiement de **stations de recharge** sur la carte.
2. **♻️ Typologie des déchets & Statistiques :** Classification des déchets (*Plastique, Verre, Métal*) et tableau de bord en temps réel (déchets générés, détectés, recyclés et score).

---

## 📅 Jalons du projet

* **09/11/2026 :** Lancement du projet et analyse du cahier des charges.
* **23/11/2026 :** Rendu de conception à mi-parcours (planning, logigrammes, structures de données).
* **14/12/2026 :** Rendu final du code source et du compte rendu technique.
* **Janvier 2027 :** Soutenances devant le jury.

---

## 👥 L'équipe (ING1 — ECE)

| Membre | Rôle & Responsabilités |
| :--- | :--- |
| **Membre 1** | **Lead Dev & Architecte** — Architecture modulaire, structures de données et moteur de simulation (`simulation.c`). |
| **Membre 2** | **Développeur IHM** — Affichage console, couleurs, légende et gestion clavier non bloquante (`affichage.c`). |
| **Membre 3** | **Concepteur Algorithmique** — Logigrammes et développement des extensions (batteries & statistiques). |
| **Membre 4** | **Chef de Projet & Qualité** — Planification, cahier de tests, documentation et soutenance. |