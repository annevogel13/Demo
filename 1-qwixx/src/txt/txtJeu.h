#ifndef _TXTJEU_H
#define _TXTJEU_H

#include "winTxt.h"
#include "../jeu.h"

/**
 * @brief Classe gérant l'affichage textuelle du jeu
 * 
 */
class txtJeu{
    private:
        Jeu jeu;
        WinTXT win;

        /**
         * @brief Affiche une ligne avec les cases cochées
         * 
         * @param x int : Coordoonnée en x
         * @param y int : Coordoonnée en y
         * @param lg Ligne : Ligne du jeu à afficher
         */
        void affLigne(int x, int y, const Ligne & lg);

        /**
         * @brief Affiche une fiche en mode texte
         * 
         * @param x int : Coordoonnée en x (coin supérieur gauche)
         * @param y int : Coordoonnée en y (coin supérieur gauche)
         * @param fiche Fiche : Fiche d'un joueur à afficher
         */
        void affFiche(int x, int y, const Fiche & fiche);

        /**
         * @brief Affiche l'ensemble des fiches du jeu
         * 
         * @param x int : Coordoonnée en x (coin supérieur gauche)
         * @param y int : Coordoonnée en y (coin supérieur gauche)
         */
        void affPlateau(int x, int y);

        /**
         * @brief Affiche l'ensemble des dés à l'écran
         * 
         * @param x int : Coordoonnée en x (coin supérieur gauche)
         * @param y int : Coordoonnée en y (coin supérieur gauche)
         */
        void affDe(int x, int y);

        /**
         * @brief Vérifie que le caractère est bien dans ces possibilités : [r,j,v,b,p]
         * 
         * @param c char : Caractère saisi par l'utilisateur
         * @return bool : True si le cacactère est r,j,v,b,p. False sinon
         */
        bool verifInitiale(char &c) const;

        /**
         * @brief Gère le fonctionnement d'un tour de jeu.
         * 
         * @param numJoueur int : Indice du joueur en cours
         * @param fin bool : Devient true si le jeu se termine pendant le tour.
         */
        void tourDeJeu(int numJoueur, bool &fin);

        /**
         * @brief Affiche les scores finaux
         * 
         */
        void finDePartie();

        /**
         * @brief Initialise les pseudos des joueurs
         * 
         */
        void initPseudo();

        /**
         * @brief Initialise le nombre de joueur et fait appel à initPseudo()
         * 
         */
        void initPartietxt();

    public:
        /**
         * @brief Constructeur de la classe txtJeu
         * 
         */
        txtJeu();

        /**
         * @brief Gère le fonctionnement global du jeu
         * 
         */
        void txtBoucle();

};

#endif