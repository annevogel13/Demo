#include <iostream>
#include <stdlib.h>
#include <vector>
#include <assert.h>

#include "direction.hpp" 
#include "tuile.hpp"
#include "noeud_case.hpp"

using namespace std ; 
using namespace MMaze ; 

Noeud_case::Noeud_case(){
    // tres importante --> apres on teste si un predecesseur existe --> on teste si nbCoupsPossible != 0 
    nbCoupsPossible = 0 ; 
    tuile = -1; 
}

Noeud_case::Noeud_case(Case C1){
    C = C1; 
}  

Noeud_case::Noeud_case(Case C1, Tuile T){
    C = C1; 
    tuile = T.acces(); 
    // initialise le possibleCoups et nbCoupsPossible
    init(C1,T); 
} 



Noeud_case* Noeud_case::getAdress(){
    return this; 
}


void Noeud_case::init(Case C1, Tuile T){
    
    for(int i = 0 ; i < 4 ; i++){
        // on recupere une direction 
        MMaze::Direction tmp_d = directions[i];  
        // on crée une coup initial 
        Coup coup1(C, T, tmp_d); 
        
        // on cree un vector qui va stoque tous les coup possible dans ce direction 
        vector <Case> resultat; 
        resultat =coup1.calculerCoupDirection(tmp_d, T);
        int l = resultat.size(); 
        for(int j = 0 ; j < l ; j++){
            
            // si le caseDebut et CaseFin ne sont pas le meme 
            if (!(C == resultat[j])){
                Coup tmp = Coup(C, resultat[j], tmp_d); 
                // on ajoute ce coup dans le vector possibleCoups
                possibleCoups.push_back(tmp);
            }
        }
    }
    
    nbCoupsPossible = possibleCoups.size(); 

} 

void Noeud_case::pred(){
    
    // affichage des predecesseurs 
    int s = predecesseur.size(); 
    for(int j =0 ; j < s ; j++){
        cout<<"pred : "<<predecesseur[j]->C.index()<<" "; 
    } 
    cout<<endl;   
}


int Noeud_case::index(){
    return C.index(); 
}


Noeud_case* Noeud_case::operator=(Noeud_case NC){
    this->C = NC.C; 
    this->nbCoupsPossible = NC.nbCoupsPossible; 
    this->possibleCoups = NC.possibleCoups; 
    
    this->predecesseur = NC.predecesseur; 
    //this->voisins= NC.voisins; 
    this->tuile = NC.tuile; 

    return this ;

}


void Noeud_case::afficher(){
    cout<<"voici les coups possible a partir de "<<C.index()<<" : "; 
    
    cout<<endl<<"   coups        : "; 
    for(int j = 0 ; j< nbCoupsPossible ; j++){
        
        cout<<"( "<<C.index()<<" , "<<possibleCoups[j].caseFin.index()<<" ) ";
    } 
    cout<<endl<<"   predecesseur : "; 
    int s_pred = predecesseur.size();
    for(int i = 0 ; i < s_pred ; i++){
        cout<<predecesseur[i]->C.index()<<" ";
    }
    cout<<endl<<"   voisins      : "; 
    int s_vois = voisins.size();
    for(int i = 0 ; i < s_vois ; i++){
        cout<<voisins[i]->C.index()<<" ";
    }

    cout<<endl<<endl; 
}

Noeud_case::~Noeud_case(){
    //cout<<"Destructor Noeud_case : "<<C.index()<<endl; 
    possibleCoups.clear(); 
    predecesseur.clear(); 
    voisins.clear(); 
    
}