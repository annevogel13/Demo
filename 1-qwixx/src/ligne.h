#ifndef _LIGNE
#define _LIGNE

/**
 * @brief Classe gérant la partie Ligne d'une Fiche
 * 
 */
class Ligne
{

public:
    bool tabCase[12]; // 12 cases (11 chiffres + cadenas)
    bool fermer;      // bool pour determiner si le ligne est fermer par un joueur
    bool decroissant;

    /**
     * @brief Constructeur de la classe Ligne
     * 
     * @param inverse bool indiquant si la ligne est décroissante (False par défaut)
     */
    Ligne(bool inverse = false);

    /**
     * @brief Convertit le numero de case en indice du tableau
     * 
     * @param numero int entre 2 et 12
     * @return int 
     */
    int conversionCase(int numero) const;

    /**
     * @brief Coche une case dans la ligne
     * 
     * @param numero int représentant la case à cocher
     */
    void cocherCase(int numero);

    /**
     * @brief Vérifie si une case peut être cochée
     * 
     * @param numero int : numéro de la case [2:12]
     * @return bool : true si la case est cochable (=respecte les règles), false sinon
     */
    bool verifierChoix(int numero) const;

    /**
     * @brief Compte le nombre de cases cochées
     * 
     * @return int
     */
    int compterNbCase() const;

    /**
     * @brief Permet de fermer une ligne
     * 
     */
    void fermerLigne();

    /**
     * @brief Compte le nombre de point sur une ligne
     * 
     * @return int 
     */
    int pointsSurLigne() const;

    /**
     * @brief fonction qui calcule le meilleur possibilite de cocher une sur un ligne 
     *
     * @param db1 entier : Valeur du dé blanc 1
     * @param db2 entier : Valeur du dé blanc 2 
     * @param dC entier  : Valeur d'un dé couleur
     * @param dif entier :  qui va stoquer le difference entre le dernier case coche et le valeur a cocher 
     * si dif = -1 ca veut dire que il y a une erreur 
     * @return entier : Indique le meilleur numero de case a cocher (si -1 veut dire qu'on a pas des possibilites)
     */
    int calculerMeilleurCaseIA(int db1, int db2, int dC, int &dif) const;

    /**
    *
    * @brief fonction qui permet d'affiche une ligne dans le console. Créer pour les raison du debuggage
    */ 
    void afficherLigne() const;

    /**
     * @brief Fonction permettant de tester le fonctionnement d'AI pour les lignes
     */
    void testRegressionAI();

    /**
     * @brief Fonction permettant de tester la classe Ligne
     * 
     */
    void testRegression();
};

#endif
