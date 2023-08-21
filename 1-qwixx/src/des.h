#ifndef _DES
#define _DES

/**
 * @brief Classe gérant les dés du jeu
 * 
 */
class Des{
    private :

        int DeRouge;
        int DeJaune;
        int DeVert;
        int DeBleu;
        int DeBlanc1;
        int DeBlanc2;

            
    public:
        /**
         * @brief Constructeur de la classe Des
         * 
         */
        Des();

        /**
         * @brief Accesseur vers le dé rouge
         * 
         * @return int : valeur dé rouge
         */
        int getRouge() const;

        /**
         * @brief Accesseur vers le dé jaune
         * 
         * @return int : valeur dé jaune 
         */
        int getJaune() const;

        /**
         * @brief Accesseur vers le dé vert
         * 
         * @return int : valeur dé vert
         */
        int getVert() const;

        /**
         * @brief Accesseur vers le dé bleu
         * 
         * @return int : valeur dé bleu
         */
        int getBleu() const;

        /**
         * @brief Accesseur vers le dé blanc 1
         * 
         * @return int : valeur dé blanc 1
         */
        int getBlanc1() const;

        /**
         * @brief Accesseur vers le dé blanc 1
         * 
         * @return int : valeur dé blanc 2
         */
        int getBlanc2() const;

        /**
         * @brief Accesseur vers les dés blancs
         * 
         * @param de1 int : valeur du dé blanc 1
         * @param de2 int : valeur du dé blanc 2
         */
        void getBlanc(int &de1, int &de2) const;

        /**
         * @brief Calcule la somme des dés blancs
         * 
         * @return int : Somme dés blancs
         */
        int sommeBlancs() const;
        
        /**
         * @brief Mutateur vers les dés blancs (fonction pour debugage uniquement)
         * 
         * @param d1 int : valeur du dé blanc 1
         * @param d2 int : valeur du dé blanc 2
         */
        void setBlancs(int d1, int d2);

        /**
        * @brief fonction permettant de saisir des valeurs de dés. (Utile pour l'IA)
        * @param d1 int : valeur de dé blanc 1
        * @param d2 int : valeur de dé blanc 2
        * @param dr int : valeur de dé rouge
        * @param dj int : valeur de dé jaune
        * @param dv int : valeur de dé verte
        * @param db int : valeur de dé bleue
        */
        void setDes(int d1, int d2, int dr, int dj, int dv, int db); 

        /**
         * @brief Tire un nombre au sort entre 0 et 6 pour chaque dé.
         * 
         */
        void lanceLesDes();

        /**
         * @brief Vérifie si le nombre nb est réalisable avec le tirage
         * 
         * @param nb int : nombre que l'on veut faire
         * @param charDeCouleur char : lettre indiquant la couleur du dé [r,j,v,b] 
         * @param blanc booleen : true pour la tester la somme des blancs, false pour tester les couleurs
         * @return true si la combinaison est possible
         * @return false sinon
         */
        bool possibilites(int nb, char charDeCouleur, bool blanc) const; 


        /**
         * @brief afficher les des 
         * 
         * */
        void afficherDes() const; 

        /**
         * @brief Fonction permettant de tester la classe Des
         * 
         */
        void testRegression();
};

#endif
