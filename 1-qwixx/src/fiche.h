#ifndef _FICHE
#define _FICHE

#include <string>

#include "ligne.h"
#include "des.h"
 

using namespace std;

/**
 * @brief Classe Fiche contrôlant les actions des joueurs ou des IA
 * 
 */
class Fiche{
    private :   
        bool ia;
        string pseudo;
    
    public:
        Ligne ligneRouge;
        Ligne ligneJaune;
        Ligne ligneVerte;
        Ligne ligneBleue;
        int coupsManques;

        /**
         * @brief Constructeur de la classe Fiche
         * 
         */
        Fiche();

        /**
         * @brief Constructeur de la classe Fiche
         * 
         * @param nom string indiquant le pseudo du joueur
         * @param _ia bool siginifant si le joueur est une IA ou non
         */
        Fiche(string nom, bool _ia);

        /**
         * @brief Mutateur de la donnée ia
         * 
         * @param _ia bool indiquant si la fiche est controlée par un IA. 
         */
        void setIA(bool _ia);

        /**
         * @brief Accesseur vers la donnée ia
         * 
         * @return bool : valeur de la donnée ia
         */
        bool getIA() const;

        /**
         * @brief Mutateur de la donnée nom
         * 
         * @param nom string indiquant le pseudo du joueur
         */
        void setPseudo(string nom);

        /**
         * @brief Accesseur vers la donnée pseudo
         * 
         * @return string : pseudo sur la fiche
         */
        string getPseudo() const;

        /**
         * @brief Compte le nombre de points total de la fiche
         * 
         * @return int : nombre de points
         */
        int compterNbPointsTotal() const;

        /**
         * @brief Calcule la meilleure position en fonction des lignes et le coche 
         * @param d : des qui donne les valeurs des des  
         * @return entier : 0 si toute est bien passe, -1 si on vais faire une pass,-2 pour un erreur generale 
         * 
         */
        int calculerMeilleurPosIA(Des d);

        /**
         * @brief Fonction permettant de tester la classe Fiche
         * 
         */
        void testRegression();
};



#endif