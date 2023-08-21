# Le projet AnLoVi

Le projet AnLoVi est constitué de 3 développeurs, CELLIER Victoire p1804414, DE JONG Anne p1905532 et MERCIER Loris p1906860, étudiants 
en deuxième année de licence Informatique à l'Université Claude Bernard Lyon 1.

AnLoVi a pour but de recréer le jeu Qwixx (jeu dans l'esprit du Yam's, Yahtzee) en langage C++. 

Le projet est disponible ici : https://forge.univ-lyon1.fr/lifap4module/tp-projet


## Table des matières
1. [Règle et fonctionnement du Qwixx](#1-règle-et-fonctionnement-du-qwixx)
2. [Organisation des fichiers](#2-organisation-des-fichiers)
3. [Compilation et exécution](#3-compilation-et-exécution)
4. [Comment jouer ?](#4-comment-jouer-)

## 1-- Règle et fonctionnement du Qwixx
#### Principe générale
Qwixx est un jeu de dés (2 blancs, 4 de couleurs) dans lequel chaque joueur tente de cocher le plus grand nombre de chiffres dans 
quatre rangées de couleurs présentes sur sa fiche de score. Plus il y a des chiffres cochés dans une rangée, plus elle rapportera de 
points. Le joueur comptabilisant le plus de points à l’issue de la partie est désigné gagnant. 

#### Cocher une case
Au cours d’une partie, les chiffres de chaque rangée doivent être __cochés de gauche à droite__ . Toutefois, les joueurs ne sont pas 
obligés de commencer par le premier chiffre de la rangée et peuvent choisir de passer un ou plusieurs chiffres. Mais attention, __tout chiffre ignoré ne pourra plus être coché__ par la suite.

#### Déroulement d'un tour
Le premier joueur est tiré au sort puis on joue dans le sens horaire. A chaque tour, le joueur actif lance les dés puis
deux actions se succèdent : 

* 1. Tous les joueurs peuvent, s'ils le souhaitent, cocher une case correspondant à la somme des deux dés blancs sur une de leur quatre lignes. 
* 2. Le joueur actif peut ensuite additionner un dé blanc avec n’importe quel autre dé de couleur pour cocher la somme obtenue dans la rangée 
correspondant à la couleur du dé choisi.
*Exemple : Dé blanc 2, Dé Rouge 4 --> Le joueur peut cocher 6 sur la ligne rouge*  

Si le joueur actif (uniquement lui) ne coche aucune case, ni au cours de l’action 1, ni au cours de l’action 2, il marque un __coup manqué__. 
C’est ensuite au tour du joueur suivant de lancer les six dés et de réaliser les deux actions décrites précédemment.

#### Clôturer une rangée
Pour pouvoir cocher le dernier chiffre d'une rangée, il est nécessaire d'avoir 5 cases préalablement cochées sur cette même rangée.
Dans ce cas, le joueur coche la dernière case ainsi que le cadenas faisant office de case supplémentaire. La ligne est désormais __fermée__
pour tous les joueurs. Il n'est alors plus possible de cocher une case sur celle-ci.

#### Fin de partie
Le jeu se termine instantanément lorsqu’un joueur marque un 4ème « coup manqué » OU lorsque deux rangées de couleurs différentes 
sont clôturées.

#### Décompte des points
En-dessous des quatre rangées se trouve un tableau indiquant le nombre de point par rangée en fonction du nombre de cases cochées. Chaque
coup manqué effectué donne un malus de -5 points. Le joueur avec le plus grand total de points l'emporte.


## 2-- Organisation des fichiers

Ce code est construit de manière à avoir les fonctionnalités de base regroupées dans des classes dites "noyau"; 
puis d'avoir une surcouche pour l'affichage : texte/console et SDL2.

L'organistion des fichiers est la suivante :

- **/src**      : les classes de base du jeu Qwixx (il n'y a ici aucun appel aux couches du dessus, de l'affichage). 
                  Toutes les fonctions nécessaires au fonctionnement du jeu sont ici
- **/src/txt**  : les classes s'occupant de faire tourner le Qwixx de l'afficher sur la console en mode texte.
                  La classe winTxt facilite l'utilisation d'une fenêtre texte et des évènements claviers.
- **/src/sdl2** : les classes s'occupant de faire tourner le Qwixx de l'afficher avec SDL2
                  La classe Image facilite l'utilisation de surface/texture afin d'afficher des images.
- **/doc**      : le fichier doxygen qui permet de générer la documentation du code
- **/data**     : les assets (image et font)
- **/bin**      : répertoire où les exécutables seront compilés 
- **/obj**      : répertoire comportant les compilations intermédiaires (.o)
- **/**         : répertoire racine comportant un makefile pour compiler ainsi qu'un readme.


Pour la documentation du code, voir la rubrique "documentation du code" plus bas.


## 3-- Compilation et exécution

#### A. Compilation
La compilation de notre projet s'effectue via un makefile.  
/!\ Il est __nécessaire__ pour la version graphique d'avoir préalablement __installé la lib SDL2, SDL_image et SDL_ttf__
dans le répertoire par défaut.  

Pour compiler l'ensemble des versions en une fois, il faut lancer dans le répertoire racine la commande :  
**```make```**  
Il est toutefois possible de compiler la version texte séparément. On utilise pour cela dans le répertoire racine :  
- **```make qwixx_txt```**      : compilation de la version texte. Produit un exécutable nommé **`mainTexte`**
- **`make qwixx_sdl`**      : compilation de la version graphique (SDL2). Produit un exécutable nommé **`mainSdl`**
- **`make qwixx_debug`**    : compilation d'une version servant au débogage. Produit un exécutable nommé **`mainTest`**

#### B. Exécution
Pour exécuter un des trois programmes compilés (voir section ci-dessus), veuillez suivre ces commandes :
- **mainTexte** : utilisez la commande **```bin/mainTexte```**.
- **mainSdl** : utilisez la commande **```bin/mainSdl```**
- **mainSdl** : utilisez la commande **```bin/mainTest```**.


## 4-- Comment jouer ?

#### Version texte  
Une fois l'exécutable lancé, vous serez invité à rentrer le nombre de joueur puis à saisir les pseudos à l'aide
des touches du clavier. Le jeu est maintenant configuré : place à l'amusement !  

###### Les touches :
- Pour **cocher une case** avec la **somme des dés blancs**, tapez l'**initial de la couleur de ligne** souhaitée (**r, j, g, b**).
- Pour **cocher une case** avec un **dé blanc + un dé couleur**, tapez l'**initial de la couleur de ligne** souhaitée (**r, j, g, b)** 
puis le **numéro de case**.
- Pour **passer un tour**, tapez la lettre **p**
- Pour **arrêter le jeu** en cours de partie, tapez **Entrée**
- En fin de partie, appuyer sur **s** pour **afficher les scores**.

Les fiches de jeu seront affichées à l'écran et actualisées à chaque action des utilisateurs.  
Les dés sont automatiquement lancés à chaque nouveau tour.

/!\ Une mauvaise saisie comptera comme un coup passé.


#### Version graphique
Une fois l'exécutable lancé, vous serez invité à **rentrer le nombre de joueur**. **Cliquez** pour cela sur le bouton correspondant. Chaque joueur devra ensuite choisir son numéro de jeu (joueur 1, joueur 2, etc...).  
Les actions à effectuer sont rappelées à gauche de l'écran dans le menu **Déroulement**. 

###### Les touches :
- Pour **cocher une case**, **cliquez GAUCHE** sur la case souhaitée.
- Pour **passer un tour**, **cliquez DROIT** n'importe où sur le fenêtre de jeu.
- Pour **arrêter le jeu** en cours de partie, **clique GAUCHE** sur l'**icône de fermeture** (croix dans le coin supérieur droit de la fenêtre)

Contrairement à la version texte, une mauvaise saisie (Case cochée n'étant pas valide, clique en dehors de la fiche, etc..) n'a aucune
conséquence. Seul le clique droit permet de passer un tour.

