# SpaceDefender

Un tower defense spatial en C++ / SFML. Défendez votre base sur trois planètes de
dix niveaux chacune, en construisant des tours et des murs pour empêcher les vagues
d'ennemis d'atteindre votre base.

Projet réalisé par **Léo RICHEZ** et **Adrien EPPLING**.

---

## Jouer

Le jeu est distribué compilé. Depuis la racine du dépôt :

```sh
cd build/bin
./SpaceDefender.exe
```

Seuls `SpaceDefender.exe`, `openal32.dll` et le dossier `ressources/` sont nécessaires
pour lancer le jeu — tout le reste du dépôt ne sert qu'à la compilation.

### Progression

Seul le premier niveau de la planète 1 est débloqué au départ. Terminer un niveau
débloque le suivant, et terminer une planète débloque la suivante.

Le bouton **Reset Account** dans les réglages remet la progression à zéro : tous les
niveaux sont reverrouillés sauf le premier, comme à la première installation.

---

## Commandes

| Action | Commande |
|---|---|
| Activer / désactiver le mode construction | **Clic droit** |
| Placer la tour ou le mur sélectionné | **Clic gauche** |
| Changer de type de tour | **Flèches ← →** |
| Sélectionner une tour déjà posée (améliorer / vendre) | **Clic gauche** dessus |
| Menu pause | **Échap** |

---

## Règles

### Ressources de départ

Elles dépendent de la difficulté choisie dans les réglages :

| Difficulté | Vies | Pièces | Bonus par vague |
|---|---|---|---|
| Easy | 7 | 450 | 225 |
| Normal | 6 | 400 | 200 |
| Hard | 5 | 350 | 175 |

### Économie

- Tuer un ennemi rapporte des pièces (montant propre à chaque type d'ennemi).
- **Améliorer** une tour coûte le prix de son niveau suivant. Chaque tour a 3 niveaux.
- **Vendre** une tour rembourse la moitié du prix de son niveau actuel.
- Ajouter du **perce-armure** à une tour coûte 50 pièces et donne +5 points, jusqu'à
  un maximum de 30. Indispensable face aux unités blindées (voir plus bas).
- Un **mur** coûte 5 pièces et en rend 2 lorsqu'il est retiré.

### Murs

Les murs rallongent le trajet des ennemis, qui recalculent leur chemin à chaque
modification. Il est impossible de boucler complètement le passage : si un mur coupe
toute route entre un point d'apparition et la base, sa construction est refusée.

Attention aux ennemis de type **Missile** et **DrillTank** : ils foncent dans les murs
et les détruisent au lieu de les contourner.

---

## Les tours

Les valeurs sont données pour les niveaux 1 / 2 / 3. La portée est en cases, la cadence
en secondes entre deux tirs.

| Tour | Prix | Dégâts | Portée | Cadence | Cibles |
|---|---|---|---|---|---|
| **Basic** | 200 / 350 / 500 | 20 / 40 / 60 | 7 / 8 / 10 | 1.5 | Sol |
| **AttackSpeed** | 275 / 400 / 600 | 6 / 8 / 11 | 7 / 8 / 9 | 0.6 / 0.4 / 0.2 | Sol |
| **AntiAir** | 400 / 550 / 700 | 100 / 140 / 180 | 12 / 13 / 15 | 4 / 3.8 / 3.2 | **Aérien uniquement** |
| **Sniper** | 450 / 600 / 800 | 50 / 100 / 150 | 17 / 25 / 30 | 4.5 / 4 / 3.7 | Sol |
| **Freeze** | 350 / 500 / 650 | gel 1.5 / 2.25 / 3 s | 7 / 7 / 8 | 5 | Sol |
| **Splash** | 500 / 700 / 1000 | 15 / 25 / 35 | 10 / 12 / 14 | 3 / 2.5 / 2 | Sol, **3 cibles minimum** |
| **SpeedAura** | 400 / 650 / 900 | +10 / 25 / 40 % de cadence | 10 / 12 / 14 | — | Tours alliées |

Quelques particularités :

- **AntiAir** ne tire *que* sur les unités aériennes ; les autres tours ne tirent *que*
  sur les unités au sol. Prévoyez les deux — mais attention, seules trois unités du jeu
  comptent réellement comme aériennes (voir la section Ennemis).
- **Splash** ne déclenche son tir que si au moins 3 ennemis sont à portée.
- **SpeedAura** n'inflige aucun dégât : elle augmente la cadence des tours à sa portée.

Toutes les tours ne sont pas disponibles partout :

| | Planète 1 | Planète 2 | Planète 3 |
|---|---|---|---|
| Basic, AttackSpeed, AntiAir, Sniper, SpeedAura | ✅ | ✅ | ✅ |
| Freeze | — | ✅ | ✅ |
| Splash | — | — | ✅ |

---

## Ennemis

Dix-neuf types, répartis selon **ce qui peut les toucher** — c'est la distinction qui
compte pour choisir ses tours.

**Vraiment aériens** — seule la tour AntiAir peut les viser :

`Spaceship`, `FastSpaceship`, `TransportSpaceship`

**Tout le reste est ciblé par les tours au sol**, y compris les unités que leur nom
laisserait croire aériennes. `FlyingDrone`, `ArmoredFlyingDrone`, `RegenerateDrone`,
`ArmoredRegenerateDrone`, `DrillTank` et `Missile` sont *semi-aériens* : ils survolent
les obstacles pour calculer leur trajet, mais restent vulnérables aux tours au sol et
insensibles à l'AntiAir.

**Boss** — un par planète, au sol.

Comportements à connaître :

- Les quatre drones (`FlyingDrone`, `ArmoredFlyingDrone`, `RegenerateDrone`,
  `ArmoredRegenerateDrone`) **ignorent complètement les murs** : inutile d'essayer de
  les rallonger.
- **Missile** et **DrillTank** détruisent les murs au lieu de les contourner ; le
  Missile est consommé dans l'opération.
- Les unités **blindées** (`Armored*`) ont 66 % de réduction de dégâts, et les boss
  10 / 30 / 70 % selon la planète. Cette réduction se contre uniquement avec le
  perce-armure acheté sur une tour (50 pièces les +5, maximum 30).
- **RegenerateDrone**, **ArmoredRegenerateDrone** et **BossPlanet1** regagnent des
  points de vie en avançant.
- Atteindre la base coûte 1 vie, mais **3** pour RegenerateDrone, ArmoredRegenerateDrone
  et TransportSpaceship, et **5** pour un boss.

---

## Multijoueur

Depuis le menu **Multiplayer** :

- **Host** affiche votre adresse IP et attend une connexion.
- **Join** demande l'adresse IP de l'hôte.

Les deux joueurs partagent la même partie : constructions, ventes et pièces sont
synchronisées.

---

## Compiler

### Prérequis

- **CMake** 3.23 ou plus
- **MinGW-w64 64 bits** (via [MSYS2](https://www.msys2.org/))
- SFML 2.5.1 — **déjà fourni** dans `include/` et `lib/`, rien à installer

### Commande

```sh
export PATH="/c/msys64/mingw64/bin:$PATH"

cmake -S . -B build_test -G "MinGW Makefiles" \
  -DCMAKE_CXX_COMPILER="C:/msys64/mingw64/bin/g++.exe" \
  -DCMAKE_C_COMPILER="C:/msys64/mingw64/bin/gcc.exe" \
  -DCMAKE_MAKE_PROGRAM="C:/msys64/mingw64/bin/mingw32-make.exe"

cmake --build build_test -j4
```

L'exécutable est produit dans `build_test/bin/`, avec `ressources/` et `openal32.dll`
copiés automatiquement à côté.

Le dossier `build/` versionné ne contient que la version distribuable
(`build/bin/`) ; compilez dans `build_test/`, qui est ignoré par git.

---

## Organisation du code

```text
main.cpp              Point d'entrée, menus et boucle de haut niveau
src/
  TDGame/             Boucle de jeu, état de partie, menus, réseau
  TDMap/              Parsing des cartes, cellules, pathfinding A*
  TDUnits/            Classe de base des ennemis et les 19 types
  TDTowers/           Classe de base des tours, les 7 types, missiles
  TDGraphics/         Chargement des textures, sprites, HUD
  TDSounds/           Musiques et effets sonores
  TDPlayer/           Données joueur et sauvegarde
ressources/
  Planet_1..3/        Cartes (*_map.txt) et vagues (*.txt) des niveaux
  Sprites/ Fonts/ Music/ Sounds/
include/ lib/         SFML 2.5.1 et GLEW fournis
```

### Format des niveaux

Chaque niveau tient en deux fichiers dans `ressources/Planet_N/` :

- `level_X_planet_N_map.txt` — la carte, un caractère par case :

  | Caractère | Signification |
  |---|---|
  | `X` | Chemin praticable |
  | `T` | Terrain constructible (tours) |
  | `S` | Point d'apparition des ennemis |
  | `B` | Base à défendre |
  | `F` | Décor de relief |

- `level_X_planet_N.txt` — les vagues, une par ligne, décrivant les types d'ennemis
  et leur nombre.

### Architecture

Le jeu est fortement multi-threadé : **un thread par entité** (chaque ennemi, chaque
tour, chaque missile, chaque animation de pièce), tous manipulant des sprites SFML que
le thread principal dessine en parallèle.

Deux mutex partagés, déclarés dans `src/TDTowers/Tower.hpp`, protègent les données
communes :

- `mtx` — la liste des ennemis de la vague en cours ;
- `towerListMtx` — la liste des tours posées.