#include <iostream>
#include <cassert>

#include "jeu.h"
#include "des.h" 
#include "fiche.h"
#include "string.h"

using namespace std;

Jeu::Jeu() : des(){
   
    nbJoueurs = 0 ; 
    nbIA = 0 ;
} 

void Jeu::setNbJoueurs(int nb){ 
    assert(nb < 5); // Maximum de 4 joueurs 
    assert(nb > 0); // Minimum de 1 joueur

    nbJoueurs = nb;
}

int Jeu::getNbJoueurs() const{
    return nbJoueurs; 
}

void Jeu::setnbIA(int _nbIA){
    assert(nbIA<=nbJoueurs);
    nbIA = _nbIA;
}

int Jeu::getNbIA() const{
    return nbIA; 
}

int Jeu::initTour(){
    
    des.lanceLesDes(); // lancement des dés   

    return des.sommeBlancs();  
}

void Jeu::fermerToutesLignes(char charDeCouleur){

    switch(charDeCouleur){  
        case 'r':
            for(int i=0 ; i<nbJoueurs ; i++){
                ensembleFiches[i].ligneRouge.fermerLigne(); 
            }
            break;
        case 'j':
            for(int i=0 ; i<nbJoueurs ; i++){
                ensembleFiches[i].ligneJaune.fermerLigne(); 
            }
            break;
        case 'v':
            for(int i=0 ; i<nbJoueurs ; i++){
            ensembleFiches[i].ligneVerte.fermerLigne(); 
            }
            break;
        case 'b':
            for(int i=0 ; i<nbJoueurs ; i++){
            ensembleFiches[i].ligneBleue.fermerLigne(); 
            }
            break;
    }

}

void Jeu::partieTour(char charDeCouleur, int numeroCase, Fiche &F, bool &reussi, bool blanc){
    assert(numeroCase<=12);
    assert(numeroCase>=2);

    if(charDeCouleur >= 'A' && charDeCouleur <= 'Z')
        charDeCouleur += 32;

    switch(charDeCouleur){
        case 'r':
            if(F.ligneRouge.verifierChoix(numeroCase) && des.possibilites(numeroCase, charDeCouleur,blanc)){ 
                F.ligneRouge.cocherCase(numeroCase); 
                reussi = true; 
                if(numeroCase==12) fermerToutesLignes('r');
            }else reussi = false; 
            break;
        case 'j':
            if(F.ligneJaune.verifierChoix(numeroCase) && des.possibilites(numeroCase, charDeCouleur,blanc)){ 
            F.ligneJaune.cocherCase(numeroCase); 
            reussi = true; 
            if(numeroCase==12) fermerToutesLignes('j');
            }else reussi = false;
            break;
        case 'v':
            if(F.ligneVerte.verifierChoix(numeroCase) && des.possibilites(numeroCase, charDeCouleur,blanc)){
                F.ligneVerte.cocherCase(numeroCase); 
                reussi = true; 
                if(numeroCase==2) fermerToutesLignes('v');
            }else reussi = false; 
            break;
        case 'b':
            if(F.ligneBleue.verifierChoix(numeroCase) && des.possibilites(numeroCase, charDeCouleur,blanc)){ 
                F.ligneBleue.cocherCase(numeroCase); 
                reussi = true;
                if(numeroCase==2) fermerToutesLignes('b');
            }else reussi = false;
            break;
        default:
            reussi = false;            
    }
}

int Jeu::nbLignesFermees() const{
    //Une ligne fermée est fermée pour TOUS les joueurs, donc on test uniquement sur le 1er
    return  ensembleFiches[0].ligneRouge.fermer + 
            ensembleFiches[0].ligneJaune.fermer +
            ensembleFiches[0].ligneVerte.fermer + 
            ensembleFiches[0].ligneBleue.fermer; 
} 
    



bool Jeu::finPartie(int numJoueur) const{
    if(ensembleFiches[numJoueur].coupsManques == 4){ 
        return true;
    }else {
        if(nbLignesFermees() >= 2){
            return true;
            }else return false; 
        }
}


void Jeu::resultatpartie(string tabPseudo[4], int tabScore[4]){

    for(int i = 0 ; i < getNbJoueurs() ; i++) {
        tabScore[i]  = ensembleFiches[i].compterNbPointsTotal(); 
        tabPseudo[i] = ensembleFiches[i].getPseudo();
    }

    // Tri par selection (décroissant)
    int temp; 
    int max;
    string tmp;
    for(int i = 0 ; i < getNbJoueurs() - 1 ; i++){
        max = i;
        for(int j=i+1 ; j<getNbJoueurs() ; j++){
            if(tabScore[j] > tabScore[max]){
                max = j;
            }            
        }
        if(max!=i){
            temp = tabScore[i];
            tabScore[i] = tabScore[max];
            tabScore[max] = temp; 

            tmp = tabPseudo[i];
            tabPseudo[i] = tabPseudo[max];
            tabPseudo[max] = tmp;
        }        
    }
}



void Jeu::testRegression(){
    cout<< "Test regression de Jeu.cpp" << endl;

    //1- Constructeur
    Jeu J;
    assert(J.nbJoueurs==0);
    assert(J.nbIA==0);
    assert(des.getBlanc1()==0);
    assert(des.getBlanc2()==0);
    assert(des.getRouge()==0);
    assert(des.getJaune()==0);
    assert(des.getVert()==0);
    assert(des.getBleu()==0);

    for(int i=0;i<4;i++){
        assert(J.ensembleFiches[i].getPseudo()=="Anonyme");
    }
    

    //2- Test Accesseur/Mutateur
    J.setNbJoueurs(2);
    J.setnbIA(1);
    assert(J.getNbJoueurs()==2);
    assert(J.getNbIA()==1);


    //3- Initialisation d'un tour
    int s;
    s = J.initTour();

    assert(s >= 2 && s <= 12);
    assert(J.des.getRouge()>0 && J.des.getRouge()<=6);
    assert(J.des.getJaune()>0 && J.des.getJaune()<=6);
    assert(J.des.getVert()>0 && J.des.getVert()<=6);
    assert(J.des.getBleu()>0 && J.des.getBleu()<=6);
    assert(J.des.getBlanc1()>0 && J.des.getBlanc1()<=6);
    assert(J.des.getBlanc2()>0 && J.des.getBlanc2()<=6);

    //4- partieTour()
    //4.1 Vérification du booleen
    bool booleen;
    
    J.des.setBlancs(1,1);
    J.partieTour('r',2,J.ensembleFiches[0],booleen,true);
    assert(booleen);

    J.des.setBlancs(2,2);
    J.partieTour('r',4,J.ensembleFiches[0],booleen,true);
    assert(booleen);

    J.des.setBlancs(2,3);
    J.partieTour('r',5,J.ensembleFiches[0],booleen,true);
    assert(booleen);

    J.des.setBlancs(4,4);
    J.partieTour('r',8,J.ensembleFiches[0],booleen,true);
    assert(booleen);

    J.des.setBlancs(2,1);
    J.partieTour('r',3,J.ensembleFiches[0],booleen,true);
    assert(!booleen); //Faux car 3 inférieur à la case 8 déjà cochée

    J.des.setBlancs(6,6);
    J.partieTour('r',12,J.ensembleFiches[0],booleen,true);
    assert(!booleen); //Faux car il faut 5 cases cochées avant la 12

    J.des.setBlancs(4,5);
    J.partieTour('r',9,J.ensembleFiches[0],booleen,true);
    assert(booleen);

    J.des.setBlancs(6,6);
    J.partieTour('r',12,J.ensembleFiches[0],booleen,true);
    assert(booleen); //5 cases déja cochées --> TRUE

    J.des.setBlancs(1,1);
    J.partieTour('v',3,J.ensembleFiches[0],booleen,true);
    assert(!booleen); //Faux car valeur imcompatible avec les dés blancs

    J.des.setBlancs(4,1);
    J.partieTour('v',7,J.ensembleFiches[0],booleen,true);
    assert(!booleen); //Faux car valeur imcompatible avec les dés blancs

    //4.2 Vérification de la ligne
    Jeu J2;    
    for(int i=2;i<=12;i++){
        for(int j=0;j<4;j++){
            //On se permet de donner une valeur improbable au dé
            J2.des.setBlancs(i,0);
            J2.partieTour('r',i,J2.ensembleFiches[j],booleen,true);
            J2.partieTour('j',i,J2.ensembleFiches[j],booleen,true);

            J2.des.setBlancs(14-i,0);
            J2.partieTour('v',14 - i,J2.ensembleFiches[j],booleen,true);
            J2.partieTour('b',14 - i,J2.ensembleFiches[j],booleen,true);

            assert(J2.ensembleFiches[j].ligneRouge.tabCase[i-2]);
            assert(J2.ensembleFiches[j].ligneJaune.tabCase[i-2]);
            assert(J2.ensembleFiches[j].ligneVerte.tabCase[i-2]);
            assert(J2.ensembleFiches[j].ligneBleue.tabCase[i-2]);

        }
        
    }
    
    //5- Nombre de ligne fermée
    assert(J.nbLignesFermees()==1);
    assert(J2.nbLignesFermees()==4);

    //6- Fin de partie
    assert(!J.finPartie(0)); //J pas fini
    assert(J2.finPartie(0)); //J2 fini car nbLigngesFermees > 2

    J.ensembleFiches[0].coupsManques = 4;
    assert(J.finPartie(0)); //J fini car coupsManques = 4

    //7- finirPartie()
    //TODO

    //8- Resultat de la partie
    //TODO
    
}
        
