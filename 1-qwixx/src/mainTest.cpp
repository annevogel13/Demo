#include <iostream>
#include <stdlib.h> //Pour srand();
#include <string.h>
#include <assert.h>

#include "jeu.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (argc == 2)
    {
        if (strcmp(argv[1], "ligne") == 0)
        {
            Ligne L;
            L.testRegression();
        }
        if (strcmp(argv[1], "des") == 0)
        {
            Des D;
            D.testRegression();
        }
        if (strcmp(argv[1], "fiche") == 0)
        {
            Fiche F;
            F.testRegression();
        }
        if (strcmp(argv[1], "jeu") == 0)
        {
            Jeu J;
            J.testRegression();
        }
        if (strcmp(argv[1], "AI-regressionJeu") == 0)
        {
            Des d;
            Fiche F;
               
            // initialiser le fiche 
            d.setDes(2,2,1,2,2,2);
            int indicateurError1; 
            indicateurError1 = F.calculerMeilleurPosIA(d);
            assert(indicateurError1 == 0); 
            assert(F.ligneRouge.tabCase[1]); // case a cocher est 2 
            
            d.setDes(2,2,2,1,2,2); 
            int indicateurError2; 
            indicateurError2 = F.calculerMeilleurPosIA(d);
            assert(indicateurError2 == 0); 
            assert(F.ligneJaune.tabCase[1]); // case a cocher est 2

            d.setDes(5,5,5,5,6,5); 
            int indicateurError3; 
            indicateurError3 = F.calculerMeilleurPosIA(d);
            assert(indicateurError3 == 0); 
            assert(F.ligneVerte.tabCase[1]); // case a cocher est 11
            
            d.setDes(5,5,1,1,1,6); // pas setDes(5,5,5,5,6) --> autrement on vais cocher verte 10
            int indicateurError4; 
            indicateurError4 = F.calculerMeilleurPosIA(d);
            assert(indicateurError4 == 0);
            assert(F.ligneBleue.tabCase[1]); // case a cocher est 11


            // verifier si on peut cocher une deuxieme case 
            d.setDes(3,2,3,6,2,2); 
            int indicateurError11; 
            indicateurError11 = F.calculerMeilleurPosIA(d);
            assert(indicateurError11 == 0);  
            assert(F.ligneRouge.tabCase[3]); // doit cocher rouge 5 

            d.setDes(3,2,6,4,2,2); 
            int indicateurError22; 
            indicateurError22 = F.calculerMeilleurPosIA(d);
            assert(indicateurError22 == 0); 
            assert(F.ligneJaune.tabCase[4]);

            cout<<"Test-regression AI Jeu"<<endl;
 

            
        }
        if (strcmp(argv[1], "AI-regression") == 0)
        {
            Ligne L; 
            L.testRegressionAI(); 
        }
    }
    else
    {
        Ligne L;
        L.testRegression();
        Fiche F;
        F.testRegression();
        Des D;
        D.testRegression();
        Jeu J;
        J.testRegression();
    }
    return 0;
}