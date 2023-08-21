#ifndef _JEU
#define _JEU 

#include <string>
#include "fiche.h"
#include "des.h"

/**
 * @brief Classe permettant de gérer le jeu à partir des autres modules.
 * 
 */
class Jeu{

  private: 
    int nbJoueurs; 
    int nbIA; 


  public: 
    Fiche ensembleFiches[4]; // maximum de 4 joueurs
    Des des;

    /**
     * @brief Constructeur de la classe Jeu
     * 
     */
    Jeu();


    /**
     * @brief Mutateur vers la donnée nbJoueurs
     * 
     * @param nbJoueurs int : Nombre de joueur dans le jeu
     */ 
    void setNbJoueurs(int nbJoueurs); 

    /**
     * @brief Accesseur vers la donnée nbJoueurs  
     * 
     * 
     * @return int : Nombre de joueur dans le jeu
     */ 
    int getNbJoueurs() const; 

   
    /**
     * @brief Fonction set le nombre de AI 
     * 
     */ 
    void setnbIA(int nbIA);
    
    
    /**
     * @brief Recherche le nombre de joueur controlé par une IA
     * 
     * 
     * @return int : Nombre de joueur étant une IA
     */ 
    int getNbIA() const; 

    /**
     * @brief Initialise un tour (lancée de dés)
     * 
     * @return int : Somme des dés blanc 
     */
    int initTour();

    /**
     * @brief Fonction qui gere les fermuteres dans tout les fichiers 
     * @param charDeCouleur : caractere qui indique le couleur du ligne 
     */ 
    void fermerToutesLignes(char charDeCouleur); 


    /**
     * @brief Fonction qui d'abord veriefie si une joueur peut cocher numeroCase et le coche apres
     * 
     * @param charDeCouleur char : 'r' rouge, 'j' jaune, 'v' vert, 'b' bleu 
     * @param numeroCase int : numero du case a cocher 
     * @param F fiche : le fiche du joueur 
     * @param reussit bool : est passer par parametre et definie si l'action est reussit 
     */
    void partieTour(char charDeCouleur, int numeroCase, Fiche &F, bool &reussi, bool blanc);

    /**
     * @brief Fonction qui va calculer le nombre de lignes qui sont ferme (et retourne une entier)
     * 
     * @return int : Nombre de ligne fermés
     */ 
    int nbLignesFermees() const; 


    /**
     * @brief fonction vérifiant si doit se terminer
     *  
     * @param numJoueur int : joueur
     * 
     * @return bool : true si les conditions de fin sont respectées, false sinon
     */ 
    bool finPartie(int numJoueur) const;


    /**
     * @brief procedure gérant les resultats de partie 
     * 
     * @param tabPseudo Tableau de string : Pseudo des joueurs
     * @param tabScore Tableau de int : Score des joueurs
     */ 
    void resultatpartie(string tabPseudo[4], int tabScore[4]); 

    /**
     * @brief Fonction permettant de tester la classe Jeu
     * 
     */
    void testRegression();
};

#endif 