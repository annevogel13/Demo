#ifndef NOEUD_CASE_HPP
#define NOEUD_CASE_HPP

#include <iostream>
#include <stdlib.h>
#include <vector>

#include "direction.hpp" 
#include "tuile.hpp"
#include "noeud_case.hpp"
#include "coup.hpp"

struct Noeud_case{
    public : 
        Case C; 
        vector <Noeud_case*> predecesseur; // contients tous les predecesseur de cette noeud_case
        vector <Noeud_case*> voisins  ; // predecesseur == voisins 
        vector <Coup> possibleCoups; // contients tous les coups possibles 
        int nbCoupsPossible;  
        int tuile ; 


        // constructeur/deconstructeur 
        Noeud_case(); 
        ~Noeud_case();

        Noeud_case(Case C1); 
        Noeud_case(Case C1, Tuile T); 

        // autres fonctions 
        void init(Case C1, Tuile T); 
        int index();
        void pred(); 
        
        Noeud_case* getAdress(); 
        Noeud_case* operator =(Noeud_case NC); 
        void afficher(); 

};

#endif 