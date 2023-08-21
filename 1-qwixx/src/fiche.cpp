#include <iostream>
#include <cassert>

#include "fiche.h"


Fiche::Fiche() :ligneVerte(true),ligneBleue(true){
    coupsManques = 0;
    ia = false;
    pseudo = "Anonyme";
}

Fiche::Fiche(string nom,bool _ia):ligneVerte(true),ligneBleue(true){
    coupsManques = 0;
    ia = _ia;
    pseudo = nom;
}

void Fiche::setIA(bool _ia){
    ia = _ia;
}


bool Fiche::getIA() const{
    return ia;
}


void Fiche::setPseudo(string nom){
    pseudo = nom;
}


string Fiche::getPseudo() const{
    return pseudo;
}


int Fiche::compterNbPointsTotal() const {
    int score = -5 *  coupsManques;

    score += ligneRouge.pointsSurLigne() + ligneJaune.pointsSurLigne() +
            ligneVerte.pointsSurLigne() + ligneBleue.pointsSurLigne();

    return score;
}


int minValeur(int tab[4], int &i){ 

    int m1, m2, r; 
    m1 = min(tab[0], tab[1]); 
    m2 = min(tab[2], tab[3]);
    r  = min(m1,m2);

    for(int j = 0 ; j<4 ; j++){
         
        if(tab[j] == r) i = j ; 
    }

    return i ;
}


int Fiche::calculerMeilleurPosIA(Des d){

    int r, j, b, v, b1,b2; 
    r = d.getRouge();
    j = d.getJaune();
    b = d.getBleu(); 
    v = d.getVert(); 
    b1 = d.getBlanc1(); 
    b2 = d.getBlanc2(); 

    int dif1, dif2, dif3, dif4; 
    int pos1, pos2, pos3, pos4;

    // calculer le meilleur options dans chaque ligne 
    pos1 = ligneRouge.calculerMeilleurCaseIA(b1,b2,r, dif1);
    pos2 = ligneJaune.calculerMeilleurCaseIA(b1,b2,j, dif2);
    pos3 = ligneBleue.calculerMeilleurCaseIA(b1,b2,b, dif3);
    pos4 = ligneVerte.calculerMeilleurCaseIA(b1,b2,v, dif4);
    

    // caclulerMeilleurCaseIA( ..) peut renvoie -1 --> veut dire que il a une error 
    // si cela est le cas on met:
    // le dif% correspondantes a 12 --> sur qu'il est jamais choisi
    // et on change le pos% pour ne pas provoquer une erreur a la suite 
    if(pos1 == -1) pos1 = dif1 = 12; 
    if(pos2 == -1) pos2 = dif2 = 12; 
    if(pos3 == -1){
        pos3 = 12 ; 
        dif3 = 12; 
    } 
    if(pos4 == -1){
        pos4 = 12 ; 
        dif4 = 12; 
    } 

    // calculerMeilleurCaseIA( ..) peut renoive 12 ou 2 tant que il n'y a pas 4 cases chochees 
    // si cela est la case on dois verifier si il y a 4 cases cochees 
    if(pos1 == 12){
        int nbCase;
        nbCase = ligneRouge.compterNbCase();
        if(nbCase < 4){
            pos1 = dif1 = 12 ; // on le peut pas choisir 
        }
    }

    if(pos2 == 12){
        int nbCase;
        nbCase = ligneJaune.compterNbCase();
        if(nbCase < 4){
            pos2 = dif2 = 12 ; // on le peut pas choisir 
        }
    }

    if(pos3 == 2){
        int nbCase;
        nbCase = ligneBleue.compterNbCase();
        if(nbCase < 4){
            pos3 = 2; 
            dif3 = 12 ; // on le peut pas choisir 
        }
    }

    if(pos4 == 2){
        int nbCase;
        nbCase = ligneVerte.compterNbCase();
        if(nbCase < 4){
            pos4 = 2; 
            dif4 = 12 ; // on le peut pas choisir 
        }
    }
    
    // verification que les possibilites sont bien entre 2 et 12; 
    assert( pos1 > 1); assert(pos1 < 13);
    assert( pos2 > 1); assert(pos2 < 13);
    assert( pos3 > 1); assert(pos3 < 13);
    assert( pos4 > 1); assert(pos3 < 13);

    assert(dif1 >= 0);
    assert(dif2 >= 0);
    assert(dif3 >= 0);
    assert(dif4 >= 0); 

    int tabDif[4];
    tabDif[0] = dif1; // represente rouge 
    tabDif[1] = dif2; // represente jaune 
    tabDif[2] = dif3; // represente bleue
    tabDif[3] = dif4; // represente verte 
    
    // determiner quelle "pos%" correspond avec le meilleurDif
    int meilleurDif, indiceCouleur;
    meilleurDif = minValeur(tabDif, indiceCouleur); 

    assert(indiceCouleur < 4); 
    assert(indiceCouleur >= 0);  

    int nbCase = -1; 

    if( meilleurDif < 4 ){
        switch(indiceCouleur){
            case 0 :
                if(pos1 == 12){
                    nbCase = ligneRouge.compterNbCase(); 
                    if(nbCase >= 4){
                        ligneRouge.cocherCase(pos1); 
                        return 0; 
                    }else return -1 ; // -1 veut dire qu'on vais faire 'p' 
                }else{
                    assert(pos1 > 1); 
                    assert(pos1 < 13); 
                    ligneRouge.cocherCase(pos1); 
                    return 0; // 0 veut dire que toute est bien passe 
                } 
            break; 
            case 1 :
                if(pos1 == 12){
                    nbCase = ligneJaune.compterNbCase(); 
                    if(nbCase >= 4){
                        ligneJaune.cocherCase(pos2); 
                        return 0; 
                    }else return -1 ; // -1 veut dire qu'on vais faire 'p' 
                }else{
                    assert(pos2 > 1); 
                    assert(pos2 < 12); 
                    ligneJaune.cocherCase(pos2); return 0; // 0 veut dire que toute est bien passe 
                } 
            break; 
            case 2 :
                if(pos1 == 2){
                    nbCase = ligneBleue.compterNbCase(); 
                    if(nbCase >= 6){
                        ligneBleue.cocherCase(pos3); 
                        return 0; 
                    }else return -1 ; // -1 veut dire qu'on vais faire 'p' 
                }else{
                    assert(pos3 > 2); 
                    assert(pos3 < 13); 
                    ligneBleue.cocherCase(pos3);  return 0; // 0 veut dire que toute est bien passe 
                } 
            break; 
            case 3 :
                if(pos1 == 2){
                    nbCase = ligneVerte.compterNbCase(); 
                    if(nbCase >= 6){
                        ligneVerte.cocherCase(pos4);  
                        return 0;  
                    }else return -1 ; // -1 veut dire qu'on vais faire 'p' 
                }else{
                    assert(pos4 > 2); 
                    assert(pos4 < 13); 
                    ligneVerte.cocherCase(pos4);  
                    return 0; // 0 veut dire que toute est bien passe 
                } 
            break; 
            default : return -2 ; // code erreur  
        }
    }else return -1 ; // -1 veut dire que on vais faire 'p' 

}
   

void Fiche::testRegression(){
    cout<< "Test regression de Fiche.cpp" << endl;

    //1- Constructeur
    Fiche F1;
    assert(F1.ligneRouge.decroissant == false);
    assert(F1.ligneJaune.decroissant == false);
    assert(F1.ligneVerte.decroissant == true);
    assert(F1.ligneBleue.decroissant == true);
    assert(F1.coupsManques == 0);
    assert(!F1.ia);
    assert(F1.pseudo == "Anonyme");

    //2- Constructeur avec paramètre
    Fiche F2("AnLoVi",true);
    assert(F2.ligneRouge.decroissant == false);
    assert(F2.ligneJaune.decroissant == false);
    assert(F2.ligneVerte.decroissant == true);
    assert(F2.ligneBleue.decroissant == true);
    assert(F2.coupsManques == 0);
    assert(F2.ia);
    assert(F2.pseudo == "AnLoVi");

    //3- Accesseur/Mutateur
    F1.setIA(true);
    assert(F1.getIA());

    F1.setPseudo("Loris");
    assert(F1.getPseudo()=="Loris");

    F2.setIA(false);
    assert(!F2.getIA());

    F2.setPseudo("a&&*");
    assert(F2.getPseudo()=="a&&*");

    //4- Les points
    //3 cases = 6pts
    F1.ligneRouge.cocherCase(2);
    F1.ligneRouge.cocherCase(4);
    F1.ligneRouge.cocherCase(5);

    //2 cases = 3pts
    F1.ligneJaune.cocherCase(5);
    F1.ligneJaune.cocherCase(6);

    //6 cases = 21pts
    F1.ligneVerte.cocherCase(12);
    F1.ligneVerte.cocherCase(11);
    F1.ligneVerte.cocherCase(10);
    F1.ligneVerte.cocherCase(8);
    F1.ligneVerte.cocherCase(6);
    F1.ligneVerte.cocherCase(5);

    //6cases = 21pts
    //DERNIERE case cochée, donc +1 case : 7cases = 28pts
    F1.ligneBleue.cocherCase(11);
    F1.ligneBleue.cocherCase(9);
    F1.ligneBleue.cocherCase(7);
    F1.ligneBleue.cocherCase(5);
    F1.ligneBleue.cocherCase(4);
    F1.ligneBleue.cocherCase(2);
    //TOTAL = 58

    assert(F1.compterNbPointsTotal()==58);


}