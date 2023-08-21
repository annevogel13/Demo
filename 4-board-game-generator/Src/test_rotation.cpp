#include "draw.hpp"
#include "tuile.hpp"
#include <iostream>
#include "melangeur.hpp"
using namespace MMaze;
using namespace std; 

#include <assert.h>


int main() {

    MelangeurOptions::imprevisible(); 

    PadPlateau pad; 
    
    // initialisation du tuile de debut 
    pad.ajouter_tuile(0,0); 
    Tuile D(true, 0, 0,0);
    D.placement_elements(pad, 0,0); 
    cout<<pad<<endl; 

    cout<<endl<<"/*----------------------------------------------------------------------------*/"<<endl<<endl; 
    cout<<"On ajoute un tuile qui vais être place aux porte jaune de tuile ("<<0<<","<<0<<") "<<endl; 
    // ajouter une tuile sur la porte JAUNE  
    Tuile T1 = D.generation_tuile(Couleur::JAUNE, pad, 0, 0, 1); 
    
    cout<<pad<<endl; 


    cout<<endl<<"/*----------------------------------------------------------------------------*/"<<endl<<endl; 
    
    // ajouter une tuile sur la porte ORANGE
    cout<<"On ajoute un tuile qui vais être place aux porte orange de tuile  ("<<0<<","<<0<<")"<<endl; 
    D.generation_tuile(Couleur::ORANGE, pad, 0, 0, T1.acces()+1); 
    
    cout<<pad<<endl; 

    return -1; 
} 