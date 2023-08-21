#include "draw.hpp"
#include "tuile.hpp"
#include <iostream>
#include "melangeur.hpp"
using namespace MMaze;
using namespace std; 

#include <assert.h>

int main() {
    
    MelangeurOptions::imprevisible(); 
    PadPlateau pad ; 
    pad.ajouter_tuile(0,0); 

    Tuile T(true, 0,0,0); 

    T.placement_elements(pad, 0,0); 

    cout<<endl<<"Ceci c'est un tuile de debut (pour afficher l'autre make test_tuileCL)"<<endl<<endl; 
    cout<<pad<<endl; 

    // tests pour verifier le fonctionnement du fonction qui calcule l'indice de mur entre deux cases 
    assert(T.obtientMurEntreCases(Case(1), Case(0)) == 12);
    assert(T.obtientMurEntreCases(Case(0), Case(1)) == 12);
    assert(T.obtientMurEntreCases(Case(0), Case(4)) == 0); 
    assert(T.obtientMurEntreCases(Case(4), Case(5)) == 13);
    assert(T.obtientMurEntreCases(Case(8), Case(9)) == 14);
    assert(T.obtientMurEntreCases(Case(12), Case(13)) == 15);

    return -1; 
    
}