#ifndef WINTXT_H
#define WINTXT_H

#include <string>

//! \brief une fenètre texte est un tableau 2D de caractères
class WinTXT
{
private:

    int dimx;       //!< \brief largeur
    int dimy;       //!< \brief hauteur
    char* win;      //!< \brief stocke le contenu de la fenètre dans un tableau 1D mais on y accede en 2D

    /**
     * @brief Déplace le curseur du terminal
     * 
     * @param x int : Déplacement sur l'axe x
     * @param y int : Déplacement sur l'axe y
     */
    void termMove(int x, int y);

    /**
     * @brief Configure la saisie : ne pas afficher les caracteres tapes
     * 
     */
    void termInit();

    /**
     * @brief Détecte si une touche est enfoncée
     * 
     * @return int : 1 en cas de succès, code erreur sinon
     */
    int kbhit();
public:

    /**
     * @brief Efface le terminal
     * 
     */
    void termClear ();

    /**
     * @brief Constructeur de la classe WinTXT
     * 
     * @param dx int : largeur de la fenêtre de dessin
     * @param dy int : hauteur de la fenêtre de dessin
     */
    WinTXT (int dx, int dy);

    /**
     * @brief Destructeur de la classe WinTXT
     * 
     */
    ~WinTXT();

    /**
     * @brief Efface la fenêtre en la remplissant par le caractère c
     * 
     * @param c char : caractère à afficher (' ' par défaut)
     */
    void clear (char c=' ');

    /**
     * @brief Efface la ligne lg en la remplissant par le caractère c
     * 
     * @param lg int : numéro de la ligne à effacer
     * @param c char : caractère à afficher (' ' par défaut)
     */
    void clearLigne(int lg, char c=' ');

    /**
     * @brief Affiche un caractère sur la fenêtre
     * 
     * @param x int : Coordonnée en x
     * @param y int : Coordonnée en y
     * @param c char : caractère à afficher
     */
    void print (int x, int y, char c);

    /**
     * @brief Affiche une chaine de caractère sur la fenêtre
     * 
     * @param x int : Coordonnée en x
     * @param y int : Coordonnée en y
     * @param ch string : Chaine de caractère à afficher
     */
    void printString (int x,int y,std::string ch);

    /**
     * @brief Dessine la fenêtre dans le terminal
     * 
     * @param x int : Coordonnée en x (O par défaut)
     * @param y int : Coordonnée en y (O par défaut)
     */
    void draw (int x=0, int y=0);

    /**
     * @brief Met en pause le programme
     * 
     */
    void pause();

    /**
     * @brief Obtention de la touche enfoncée par l'utilisateur
     * 
     * @return char : Touche enfoncée
     */
    char getCh();

    /**
     * @brief Accesseurs vers la donnée dimx 
     * 
     * @return int : Largeur de la fenêtre
     */
    int getlargeur() const ;

    /**
     * @brief Accesseurs vers la donnée dimy
     * 
     * @return int : Hauteur de la fenêtre
     */
    int gethauteur()const ;

    /**
     * @brief Mtateur vers la donnée dimy
     * 
     * @param h int : Hauteur de la fenêtre
     */
    void sethauteur(int h);


};



#endif
