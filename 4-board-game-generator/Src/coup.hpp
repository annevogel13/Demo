#ifndef COUP_HPP
#define COUP_HPP

#include "case.hpp"
#include "tuile.hpp"
#include <vector>
using namespace MMaze; 

class Coup{
    public: 
        Case caseDebut;  
        Case caseFin;
        int tuile_de_case_fin; 
        int tuile_de_case_debut; 
        MMaze::Direction d ; 
        

        // constructeurs  
        Coup(); 
        ~Coup();
        
        Coup(Case Cdebut, Tuile T, MMaze::Direction dir);
        Coup(Case Cdebut, Case CFin, MMaze::Direction dir); 
        Coup(Case Cdebut, Case CFin, MMaze::Direction dir, int tuile_fin); 

        // reste des fonctions 
        Coup* creationCoup(Case Cdebut, Case CFin, MMaze::Direction dir);  
        vector<Case> calculerCoupDirection(MMaze::Direction dir, Tuile T); 
        

        MMaze::Direction direction(Case i, Case j ); 
        int longeurEntreDeuxCases(); 
        void afficherCoup(); 
        
};

#endif