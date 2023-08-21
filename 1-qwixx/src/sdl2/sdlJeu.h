#ifndef _SDLJEU
#define _SDLJEU

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "image.h"

#include "../jeu.h"

/**
 * @brief Classe permettant de gérer l'affichage du jeu en mode graphique
 * 
 */
class sdlJeu {

private :
	Jeu jeu;

    SDL_Window * window;
    SDL_Renderer * renderer;

    Image fiche;
    Image croix;
    Image bande;
    Image fond;

    Image * tabDeBlanc;
    Image * tabDeRouge;
    Image * tabDeJaune;
    Image * tabDeVert;
    Image * tabDeBleu;

    
    SDL_Color couleurPolice;
    SDL_Color couleurTour;

    TTF_Font * fontPseudo;
    TTF_Font * fontstandard;
    
    Image * tabFontPseudo; 
    Image * tabFontPseudoRouge; 
    Image * tabFontNbJoueur;
    Image police_score;  
    Image titre_im;
    Image tourBlanc;
    Image tourCouleur;
    Image deroulement;
    Image choixJoueur;
    Image joueurActif; 
    Image classement;  
    Image txtbtnFin; 

    SDL_Rect * posBouton;


    /**
     * @brief Détermine le nombre de joueur sur la partie en fonction du clique
     * 
     * @param mouseX int : Coordonnée x de la souris
     * @param mouseY int : Coordonnée y de la souris
     * @return bool : true si clique sur un bouton, false sinon
     */
    bool determineNbJoueur(int mouseX, int mouseY);

    /**
     * @brief Change la couleur d'affichage des textes de déroulement     * 
     * 
     * @param blanc bool : true si on joue avec dés blancs uniquement, false sinon
     */
    void changerCouleurTexteDeroulement(bool blanc);

    /**
     * @brief Determine si la souris est dans un rectangle (x,y,w,h)
     * 
     * @param mouseX int : Coordonnée x de la souris
     * @param mouseY int : Coordonnée y de la souris
     * @param x int : Coordonnée en x (coin supérieur gauche)
     * @param y int : Coordonnée en y (coin supérieur gauche)
     * @param w int : largeur du rectangle
     * @param h int : hauteur du rectangle
     * @return bool : true si souris dans rectangle, faux sinon
     */
    bool cliqueDansRect(int mouseX, int mouseY, int x, int y, int w, int h) const;

    /**
     * @brief Determine si la souris est dans un rectangle (x,y,w,h)
     * 
     * @param mouseX int : Coordonnée x de la souris
     * @param mouseY int : Coordonnée y de la souris
     * @param r SDL_Rect : Position du rectangle cliquable
     * @return bool : true si souris dans rectangle, faux sinon
     */
    bool cliqueDansRect(int mouseX, int mouseY, const SDL_Rect &r) const;


    /**
     * @brief Coche une case du jeu en fonction de la position de la souris
     * 
     * @param mouseX int : Coordonnée x de la souris
     * @param mouseY int : Coordonnée y de la souris
     * @param posFiche SDL_Rect : position et dimension d'une fiche
     * @param numJoueur int : indice du joueur en cours
     * @param blanc bool : true si on joue avec dés blancs uniquement, false sinon
     * @return bool : true si une case a été cochée, false sinon
     */
    bool trouverCase(int mouseX, int mouseY, const SDL_Rect &posFiche,int numJoueur, bool blanc);


    /**
     * @brief Affichage des dés à l'écran
     * 
     * @param x int : Coordonnée en x (coin supérieur gauche)
     * @param y int : Coordonnée en y (coin supérieur gauche)
     */
    void sdlDes(int x,int y) const;

    /**
     * @brief Affiche le score à l'écran
     * 
     * @param pos SDL_Rect : position et dimension d'une fiche
     * @param numJoueur int : Indice du joueur en cours (Début à 0 pour joueur 1)
     */
    void sdlScore(const SDL_Rect &pos, int numJoueur);

    /**
     * @brief Affiche les croix sur les cases cochées
     * 
     * @param pos SDL_Rect : position et dimension d'une fiche
     * @param numJoueur int : Indice du joueur en cours (Début à 0 pour joueur 1)
     */
    void sdlCroix(const SDL_Rect &pos, int numJoueur);

    /**
     * @brief Affiche les fiches des joueurs non actifs
     * 
     * @param pos SDL_Rect : position et dimension des petites fiches
     * @param numPriveJoueur int : Indice du joueur qui ne doit pas être affiché
     */
    void sdlFicheAutres(SDL_Rect &pos,int numPriveJoueur);

    /**
     * @brief Affiche la fiche du joueur actif
     * 
     * @param posFiche SDL_Rect : position et dimension de la fiche principale
     * @param numJoueur int : Indice du joueur en cours
     */
    void sdlFicheActive(const SDL_Rect &posFiche, int numJoueur);
    
    /**
     * @brief Affiche le jeu à l'écran
     * 
     * @param posFiche SDL_Rect : position et dimension de la fiche principale
     * @param boutonFin SDL_Rect : position et dimension du boutin fin
     * @param numJoueur int : Indice du joueur en cours
     * @param joueurPrincipal int : Indice du joueur principal
     * @param blanc bool : true si on joue avec dés blancs uniquement, false sinon
     */
    void sdlAff (const SDL_Rect &posFiche, const SDL_Rect &boutonFin, int numJoueur, int joueurPrincipal, bool blanc);

    /**
     * @brief Affiche le classement finale
     * 
     */
    void sdlAffFin();

    /**
     * @brief Affiche le début de partie avec le choix du nombre de joueur
     * 
     */
    void sdlAffDebut();

    /**
     * @brief Met à jour les textes à afficher pour le classement
     * 
     * @param tabResultat string : tableau contenant les pseudos des joueurs
     * @param tabScore int : tableau contenant le score des joueurs
     */
    void majPseudoFinJoueur(string tabResultat[4], int tabScore[4]);

    void initPartie();

public :   

    /**
     * @brief Constructeur de la classe sdlJeu
     * 
     */
    sdlJeu ();

    /**
     * @brief Destructeur de la classe sdlJeu
     * 
     */
    ~sdlJeu (); 

    /**
     * @brief Fonction gérant le déroulement du jeu
     * 
     */
    void sdlBoucle ();

};

#endif