#include <iostream>
#include <stdlib.h>
#include <vector>
#include <assert.h>

#include "direction.hpp" 
#include "tuile.hpp"
#include "noeud_case.hpp"
#include "coup.hpp"

using namespace std ; 
using namespace MMaze ; 

Coup::Coup(){
    caseDebut = Case(0);
    caseFin = Case(0); 
    d = MMaze::Direction::BAS; 
}

Coup::~Coup(){
    //cout<<"Destructor Coup "<<endl; 
} 

MMaze::Direction directionOppose(MMaze::Direction dir){
    if(dir == MMaze::Direction::HAUT) return MMaze::Direction::BAS; 
    if(dir == MMaze::Direction::BAS) return MMaze::Direction::HAUT; 
    if(dir == MMaze::Direction::GAUCHE) return MMaze::Direction::DROITE; 
    if(dir == MMaze::Direction::DROITE) return MMaze::Direction::GAUCHE; 

    // pour enlever l'erreur de compilation, ne serait jamais utilise 
    return MMaze::Direction::BAS; 
}

vector <Case> Coup::calculerCoupDirection(MMaze::Direction dir, Tuile T){ 
    Case c = caseDebut;  
    Case v ; // curseur pour parcourrir une direction   
    vector <Case> pos;
    pos.push_back(c);  
    try {
        for(int i = 0 ; i < 3 ; i++){ // on peut pas decaler plus que 3 d'une côte 

            v = c.voisine(dir);
            // -1 veut dire que il n'est pas une mur 
            int ind_mur = T.obtientMurEntreCases(v,c); 
            
            // if tabMurs is true --> il y a un mur donc on arrete la boucle 
            if(T.tab_murs[ind_mur]){
                // on a trouve le derniere case accessible    
                caseFin = v.voisine(directionOppose(dir)); 

                // retour le vector pos qui contient tous les indexs de case qu'on peut acceder dans ce direction
                return pos ;  
                break; // pour sortir de ce boucle for 
            }else{
                // ajoute case dans le vector pos 
                pos.push_back(v); 
                c = v ; 
            }
        }
    // recupere les error si une case n'a pas une voisine(dir)   
    }catch (std::exception& e) { } ; 
    // cela veut dire qu'on a decale le maximum
    //longeur = 3;  
    caseFin = v; 
    return pos;  

}

// retour le longeur absolut entre les deux cases stoque dans Coup 
int Coup::longeurEntreDeuxCases(){

    if(caseDebut.ligne() == caseFin.ligne()) return abs(int(caseDebut.colonne() - caseFin.colonne())); 
    if(caseDebut.colonne() == caseFin.colonne()) return abs(int(caseDebut.ligne() - caseFin.ligne())); 

    return -1; 
}


MMaze::Direction Coup::direction(Case i, Case j ){
    int dif_c = i.colonne() - j.colonne(); 
    int dif_l = i.ligne() - j.ligne(); 
    
    if(dif_l == 0){
        if(dif_c > 0){
            return MMaze::Direction::DROITE;
        }else return MMaze::Direction::GAUCHE;   
    }

    if((dif_c == 0)){
        if(dif_l > 0){
            return MMaze::Direction::HAUT;
        }else return MMaze::Direction::BAS; 
    } 
        
    assert(dif_c == 0 || dif_l == 0); 
}

// pour le moment on ne utilise pas 
Coup* Coup::creationCoup(Case Cdebut, Case CFin, MMaze::Direction dir){
    caseDebut = Cdebut; 
    caseFin = CFin; 
    d = dir;  
    return this; 
}

// une constructeur 
Coup::Coup(Case CDebut, Tuile T, MMaze::Direction dir){
    assert((T.tab_cases_contenue[CDebut.index()] == MMaze::Site::BOUTIQUE) == false); 
    caseDebut = CDebut;   
    d = dir ; 
    tuile_de_case_debut = T.acces(); 
    tuile_de_case_fin = T.acces(); 

    vector <Case> tab; 
    // cette fonction initialise les longeur et direction 
    tab = calculerCoupDirection(dir, T); 
} 

Coup::Coup(Case Cdebut, Case CFin, MMaze::Direction dir, int tuile_fin){
    caseDebut = Cdebut; 
    caseFin = CFin; 
    d = dir; 
    tuile_de_case_fin = tuile_fin ; 
}

Coup::Coup(Case Cdebut, Case CFin, MMaze::Direction dir){
    caseDebut = Cdebut; 
    caseFin = CFin; 
    d = dir; 
}



void Coup::afficherCoup(){
    // fonction seulement pour le debugage 
    cout<<"Entre tuile: "<<tuile_de_case_debut<<" -> "<<tuile_de_case_fin<<", "; 
    cout<<"debut : "<<caseDebut.index()<<" , ";
    cout<<"fin : "<<caseFin.index()<<" , "; 
    cout<<"direction : "<<nom(d)<<endl; 
}